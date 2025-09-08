#!/bin/bash

TARGET_IP=$(ip -4 -o addr show dev ens3 | awk '{print $4}' | cut -d/ -f1)

modprobe nvme
modprobe nvme_core
modprobe nvme_fabrics
modprobe nvmet

sudo modprobe brd rd_nr=1 rd_size=4194304

cd /sys/kernel/config/nvmet/subsystems/
mkdir os
cd os
echo 1 > attr_allow_any_host
mkdir namespaces/1
cd namespaces/1
echo -n /dev/ram0 > device_path
echo 1 > enable
cd /sys/kernel/config/nvmet/ports/
mkdir 50000
cd 50000
echo "$TARGET_IP" > addr_traddr
echo tcp > addr_trtype
echo 4420 > addr_trsvcid
echo ipv4 > addr_adrfam
ln -s /sys/kernel/config/nvmet/subsystems/os /sys/kernel/config/nvmet/ports/50000/subsystems/os

nvme connect -a "$TARGET_IP" -t tcp -s 4420 -n os
