#!/bin/sh

module="draiver"
device="draiver"
mode="664"

sudo /sbin/insmod ./$module.ko $* || exit 1

sudo rm -f /dev/${device}[0-3]

major=$(awk "\$2==\"$module\" {print \$1}" /proc/devices)

printf "found major %d\n" $major

sudo mknod /dev/${device}0 c $major 0
sudo mknod /dev/${device}1 c $major 1
sudo mknod /dev/${device}2 c $major 2
sudo mknod /dev/${device}3 c $major 3

group="staff"
grep -q "^staff:" /etc/group || group="wheel"

sudo chgrp $group /dev/${device}[0-3]
sudo chmod $mode /dev/${device}[0-3]
