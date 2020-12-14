#!/bin/bash
set -e
if [ -z "$1" ]; then
    echo "Usage: tuxy_test <bench>"
    exit 1
fi
y=$1

ping -c 3 172.16.${y}0.1    # tuxy3 VLAN y0
ping -c 3 172.16.${y}0.254  # tuxy4 VLAN y0
ping -c 3 172.16.${y}1.253  # tuxy4 VLAN y1
ping -c 3 172.16.${y}1.1    # tuxy2 VLAN y1
ping -c 3 172.16.${y}1.254  # Rc inside
ping -c 3 172.16.1.${y}9    # Rc outside

ping -c 3 google.com
ping -c 3 example.com
ping -c 3 example.org
ping -c 3 www.sapo.pt

make -C download
make -C download test_all
