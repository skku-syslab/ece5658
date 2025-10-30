#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <block_size>"
    echo "Example: $0 4k"
    exit 1
fi

BLOCK_SIZE=$1

sudo bash -c "echo 3 > /proc/sys/vm/drop_caches"

fio \
  --name=random_read \
  --filename=/mnt/ext4-dax/test \
  --rw=randread \
  --direct=1	\
  --ioengine=libaio \
  --size=512M \
  --gtod_reduce=0 \
  --cpus_allowed_policy=split \
  --thread \
  --group_reporting \
  --time_based \
  --runtime=30 \
  --ramp_time=10 \
  --bs=$BLOCK_SIZE \
  --iodepth=16 \
  --cpus_allowed=0-11 \
  --numjobs=1
