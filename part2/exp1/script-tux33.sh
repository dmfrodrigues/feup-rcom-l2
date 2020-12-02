## 2. Configure tuxy3 and tuxy4 using ifconfig and route commands
ifconfig eth0 up
ifconfig
ifconfig eth0 172.16.30.1/24

## 3. Register the IP and MAC addresses of network interfaces
# IP: 172.16.30.1
# MAC: 00:21:5a:61:24:92

## 4. Use ping  command to verify connectivity between these computers
ping 172.16.30.254

## 5. Inspect forwarding (route -n) and ARP (arp -a) tables
route -n
# Kernel IP routing table
# Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
# 172.16.30.0     0.0.0.0         255.255.255.0   U     0      0        0 eth0
arp -a
# ? (172.16.30.254) at 00:21:5a:5a:7d:74 [ether] on eth0

## 6. Delete ARP table entries in tuxy3 (arp -d ipaddress)
arp -d 172.16.30.254

## 7. Start Wireshark in tuxy3.eth0 and start capturing packets