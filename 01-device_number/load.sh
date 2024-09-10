#!/bin/sh
module="device_number"
device="draiver"
mode="664"

/sbin/rmmod $module || /sbin/insmod ./$module.ko $* || exit 1 

rm -f /dev/${device}*

major=$(awk "\$2==\"${device}\" {print \$1}" /proc/devices)

echo "found major ${major} for ${device}"

mknod /dev/${device}0 c $major 0

group="staff"
grep -q '^staff:' /etc/group || group="wheel"

chgrp $group /dev/${device}0
chmod $mode /dev/${device}0

echo "loaded device : /dev/${device}0"
