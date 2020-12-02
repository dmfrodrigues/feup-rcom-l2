Restart communication subsystem
```sh
/etc/init.d/networking restart
```

#### 2. Configure tuxy3 and tuxy4 using ifconfig and route commands
```sh
ifconfig eth0 up
ifconfig
ifconfig eth0 172.16.30.1/24
```

#### 3. Register the IP and MAC addresses of network interfaces
IP: 172.16.30.1  
MAC: 00:21:5a:61:24:92

#### 4. Use ping  command to verify connectivity between these computers
```sh
ping 172.16.30.254
```

#### 5. Inspect forwarding (route -n) and ARP (arp -a) tables
```sh
route -n
```
```txt
Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
172.16.30.0     0.0.0.0         255.255.255.0   U     0      0        0 eth0
```
```sh
arp -a
```
```txt
? (172.16.30.254) at 00:21:5a:5a:7d:74 [ether] on eth0
```

#### 6. Delete ARP table entries in tuxy3 (arp -d ipaddress)
```sh
arp -d 172.16.30.254
```

#### 7. Start Wireshark in tuxy3.eth0 and start capturing packets
#### 8. In tuxy3, ping tuxy4 for a few seconds
#### 9. Stop capturing packets
#### 10. Save log study it at home
Check [tux33-packets-captured.pcapng](tux33-packets-captured.pcapng)
