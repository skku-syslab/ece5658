# Lab2 : blk-switch

## Commands

```
sudo -s
apt install sysstat python3-pip
pip install gdown
cd ~ubuntu/ece5658
gdown 1f8ltR17j_nx4GcVOZTGj6w_uyKILwO5B
tar -xvzf lab2.tar.gz
cd ~ubuntu/linux-5.10
cp -r ~ubuntu/ece5658/lab2/blk-switch/* .
```

**⚠️ [NOTE]**: We assume linux-5.10 and ece5658 are in ~ubuntu. If not, adjust the path accordingly.

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
