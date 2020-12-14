#!/bin/bash
set -e
if [ -z "$1" ]; then
    echo "Usage: tuxy3_config <bench>"
    exit 1
fi
y=$1

# Restart network
/etc/init.d/networking restart
# Setup eth0
ifconfig eth0 up
ifconfig
ifconfig eth0 172.16.${y}0.1/24

# Add route to VLAN y1 through tuxy4
route add -net 172.16.${y}1.0/24 gw 172.16.${y}0.254

# Set default route to tuxy4
route add default gw 172.16.${y}0.254

# DNS configuration
echo -e "search netlab.fe.up.pt\nnameserver 172.16.1.1 *" > /etc/resolv.conf
