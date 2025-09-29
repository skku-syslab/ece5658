# Lab2 : blk-switch

Installing blk-switch requires compiling the kernel. However, it would take too long if we all did it during class, so we decided to compile the kernel at home.

## Commands

```
sudo -s
apt install sysstat python-pip3
pip install gdown
cd ~ubuntu/ece5658
gdown 1f8ltR17j_nx4GcVOZTGj6w_uyKILwO5B
tar -xvzf lab2.tar.gz
```

## Change path/to to your environment

```
cd path/to/linux-5.10
```

## Commands

```
cp -r ~ubuntu/ece5658/lab2/blk-switch/* .
```

## Menuconfig

```
make menuconfig
```

IO Schedulers -> blk-switch I/O scheduler  
Check if blk-switch is modularized  
Save & Exit  

**⚠️ [NOTE]**: Even if it has already been modularized, it must be saved

## Commands

```
make -j12 bzImage
make -j12 modules
make INSTALL_MOD_STRIP=1 modules_install
make install
reboot
```
