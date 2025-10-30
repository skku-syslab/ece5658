#!/bin/bash

sudo bash -c "echo 3 > /proc/sys/vm/drop_caches"

sudo perf record -F 99 -C 0 -g --call-graph dwarf -- \
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
  --bs=4k \
  --iodepth=16 \
  --cpus_allowed=0 \
  --numjobs=1

sudo perf script > out.perf
../FlameGraph/stackcollapse-perf.pl out.perf > out.folded  
../FlameGraph/flamegraph.pl out.folded > ~ubuntu/dax_flamegraph.svg

rm -f out.perf out.folded perf.data
