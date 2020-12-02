ifconfig eth0 up
ifconfig
ifconfig eth0 192.168.0.0/24
route add -net 192.168.0.0/24 gw 172.16.30.0
