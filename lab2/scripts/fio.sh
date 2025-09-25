#!/bin/bash

sudo bash -c "echo 3 > /proc/sys/vm/drop_caches"

fio \
  --name=random_read \
  --filename=/dev/nvme0n1 \
  --rw=randread \
  --direct=1 \
  --ioengine=libaio \
  --size=1G \
  --gtod_reduce=0 \
  --cpus_allowed_policy=split \
  --thread \
  --group_reporting \
  --time_based \
  --runtime=30 \
  --ramp_time=10 \
  --bs=4k \
  --iodepth=128 \
  --cpus_allowed=0 \
  --numjobs=1
