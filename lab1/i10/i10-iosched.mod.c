#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xd4ac9cbc, "module_layout" },
	{ 0x97803f0f, "elv_unregister" },
	{ 0xd4f55b8d, "elv_register" },
	{ 0x3c5d543a, "hrtimer_start_range_ns" },
	{ 0x78f4b79d, "blk_mq_sched_request_inserted" },
	{ 0xda361f62, "blk_stat_enable_accounting" },
	{ 0x2d327533, "elevator_alloc" },
	{ 0x2d0684a9, "hrtimer_init" },
	{ 0xb311672, "kmem_cache_alloc_node_trace" },
	{ 0xbc1819f, "kmalloc_caches" },
	{ 0x37a0cba, "kfree" },
	{ 0x6635bf30, "pv_ops" },
	{ 0x1dc8017e, "blk_bio_list_merge" },
	{ 0xba8fbd64, "_raw_spin_lock" },
	{ 0x46a4b118, "hrtimer_cancel" },
	{ 0xef34bf3e, "hrtimer_active" },
	{ 0x597d7149, "seq_printf" },
	{ 0x8cf7eab0, "blk_mq_run_hw_queue" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "81DF66F2E20DABC07FFE5B8");
