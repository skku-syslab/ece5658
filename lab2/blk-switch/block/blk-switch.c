// SPDX-License-Identifier: GPL-2.0
/*
 * blk-switch I/O scheduler
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/blkdev.h>
#include <linux/blk-mq.h>
#include <linux/init.h>
#include <linux/topology.h>
#include <linux/jiffies.h>
#include <linux/cpumask.h>

#include <linux/elevator.h>
#include "blk.h"
#include "blk-mq.h"
#include "blk-mq-sched.h"

struct blk_switch_hctx_data {
	spinlock_t lock;
	struct list_head fifo_list;
};

static int blk_switch_init_sched(struct request_queue *q, struct elevator_type *e)
{
	struct elevator_queue *eq;

	eq = elevator_alloc(q, e);
	if (!eq)
		return -ENOMEM;

	q->elevator = eq;
	return 0;
}

static void blk_switch_exit_sched(struct elevator_queue *e)
{
}

static int blk_switch_init_hctx(struct blk_mq_hw_ctx *hctx, unsigned int hctx_idx)
{
	struct blk_switch_hctx_data *shd;

	shd = kmalloc_node(sizeof(*shd), GFP_KERNEL, hctx->numa_node);
	if (!shd)
		return -ENOMEM;
	spin_lock_init(&shd->lock);
	INIT_LIST_HEAD(&shd->fifo_list);
	hctx->sched_data = shd;
	return 0;
}

static void blk_switch_exit_hctx(struct blk_mq_hw_ctx *hctx, unsigned int hctx_idx)
{
	kfree(hctx->sched_data);
}

static void blk_switch_prepare_request(struct request *rq)
{
}

static void blk_switch_finish_request(struct request *rq)
{
}

/* request steering */
static void blk_switch_select_ctx(struct blk_mq_alloc_data *data)
{
}

static void blk_switch_insert_requests(struct blk_mq_hw_ctx *hctx,
				 struct list_head *list, bool at_head)
{
	struct blk_switch_hctx_data *shd = hctx->sched_data;
	bool was_empty;

	spin_lock(&shd->lock);
	was_empty = list_empty(&shd->fifo_list);

	while (!list_empty(list)) {
		struct request *rq = list_first_entry(list, struct request, queuelist);
		list_del_init(&rq->queuelist);

		if (at_head)
			list_add(&rq->queuelist, &shd->fifo_list);
		else
			list_add_tail(&rq->queuelist, &shd->fifo_list);
	}

	spin_unlock(&shd->lock);

	if (was_empty)
		blk_mq_run_hw_queue(hctx, true);
}

static struct request *blk_switch_dispatch_request(struct blk_mq_hw_ctx *hctx)
{
	struct blk_switch_hctx_data *cur = hctx->sched_data;
	struct request *rq;

	spin_lock(&cur->lock);
	if (list_empty(&cur->fifo_list)) {
		spin_unlock(&cur->lock);
		return NULL;
	}

	rq = list_first_entry(&cur->fifo_list, struct request, queuelist);
	list_del_init(&rq->queuelist);
	spin_unlock(&cur->lock);

	return rq;
}

static bool blk_switch_has_work(struct blk_mq_hw_ctx *hctx)
{
	struct blk_switch_hctx_data *shd = hctx->sched_data;
	return !list_empty_careful(&shd->fifo_list);
}

static struct elevator_type blk_switch_sched = {
	.ops = {
		.init_sched		= blk_switch_init_sched,
		.exit_sched		= blk_switch_exit_sched,
		.init_hctx		= blk_switch_init_hctx,
		.exit_hctx		= blk_switch_exit_hctx,
		.select_ctx		= blk_switch_select_ctx,
		.insert_requests	= blk_switch_insert_requests,
		.dispatch_request	= blk_switch_dispatch_request,
		.prepare_request	= blk_switch_prepare_request,
		.finish_request		= blk_switch_finish_request,
		.has_work		= blk_switch_has_work,
	},
	.elevator_name = "blk-switch",
	.elevator_owner = THIS_MODULE,
};

static int __init blk_switch_init(void)
{
	return elv_register(&blk_switch_sched);
}

static void __exit blk_switch_exit(void)
{
	elv_unregister(&blk_switch_sched);
}

module_init(blk_switch_init);
module_exit(blk_switch_exit);

MODULE_AUTHOR("Operation System Design");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("blk-switch I/O scheduler");
