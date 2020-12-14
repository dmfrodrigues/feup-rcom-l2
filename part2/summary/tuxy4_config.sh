#!/bin/bash
set -e
if [ -z "$1" ]; then
    echo "Usage: tuxy4_config <bench>"
    exit 1
fi
y=$1

# Restart network
/etc/init.d/networking restart
# Setup eth0
ifconfig eth0 up
ifconfig
ifconfig eth0 172.16.${y}0.254/24
# Setup eth1
ifconfig eth2 up
ifconfig
ifconfig eth2 172.16.${y}1.253/24

# Enable IP forwarding
echo 1 > /proc/sys/net/ipv4/ip_forward
echo 0 > /proc/sys/net/ipv4/icmp_echo_ignore_broadcasts

# Set default route to Rc
route add default gw 172.16.${y}1.254

# DNS configuration
echo -e "search netlab.fe.up.pt\nnameserver 172.16.1.1 *" > /etc/resolv.conf
