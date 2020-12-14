#!/bin/bash
set -e -x
if [ -z "$2" ]; then
    echo "Usage: tuxy2_config <bench> <ethX>"
    exit 1
fi
y=$1
ethX=$2

# Restart network
/etc/init.d/networking restart
# Setup ethX
ifconfig $ethX up
ifconfig
ifconfig $ethX 172.16.${y}1.1/24

# Add route to VLAN y0 through tuxy4
route add -net 172.16.${y}0.0/24 gw 172.16.${y}1.253

# Set default route to Rc
route add default gw 172.16.${y}1.254

# DNS configuration
echo -e "search netlab.fe.up.pt\nnameserver 172.16.1.1" > /etc/resolv.conf
