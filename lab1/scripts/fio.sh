#!/bin/bash

if [ $# -lt 1 ]; then
  echo "Usage: $0 <numjobs 1-12>" >&2
  exit 1
fi

if ! [[ "$1" =~ ^[0-9]+$ ]]; then
  echo "Error: numjobs must be an integer." >&2
  echo "Usage: $0 <numjobs 1-12>" >&2
  exit 1
fi

if [ "$1" -lt 1 ] || [ "$1" -gt 12 ]; then
  echo "Error: numjobs must be between 1 and 12." >&2
  echo "Usage: $0 <numjobs 1-12>" >&2
  exit 1
fi

NUMJOBS="$1"

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
  --cpus_allowed=0-11 \
  --numjobs=${NUMJOBS}
