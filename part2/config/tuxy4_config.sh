#!/bin/bash
set -e -x
if [ -z "$3" ]; then
    echo "Usage: tuxy4_config <bench> <ethX> <ethY>"
    exit 1
fi
y=$1
ethX=$2
ethY=$3

# Restart network
/etc/init.d/networking restart
# Setup ethX
ifconfig $ethX up
ifconfig
ifconfig $ethX 172.16.${y}0.254/24
# Setup ethY
ifconfig $ethY up
ifconfig
ifconfig $ethY 172.16.${y}1.253/24

# Enable IP forwarding
echo 1 > /proc/sys/net/ipv4/ip_forward
echo 0 > /proc/sys/net/ipv4/icmp_echo_ignore_broadcasts

# Set default route to Rc
route add default gw 172.16.${y}1.254

# DNS configuration
echo -e "search netlab.fe.up.pt\nnameserver 172.16.1.1 *" > /etc/resolv.conf
