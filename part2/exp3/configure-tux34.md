#### 1. Transform tuxy4 (linux machine) into a router
##### Configure also tuxy4.eth1
```sh
ifconfig eth1 up
ifconfig
ifconfig eth1 172.16.31.253/24
```
In GTKTerm:
```sh
enable
8nortel

# Add port 4
configure terminal
interface fastethernet 0/4
switchport mode access
switchport access vlan 31
end

show running-config interface fastethernet 0/4
show interfaces fastethernet 0/4 switchport
```

##### Enable IP forwarding
```sh
echo 1 > /proc/sys/net/ipv4/ip_forward
```
##### Disable ICMP echo-ignore-broadcast
```sh
echo 0 > /proc/sys/net/ipv4/icmp_echo_ignore_broadcasts
```

#### 2. Observe MAC addresses and IP addresses in tuxy4.eth0 and tuxy4.eth1
tux34.eth0:  
IP: 172.16.30.254  
MAC: 00:21:5a:5a:7d:74

tux34.eth1:  
IP: 172.16.31.253  
MAC: 00:c0:df:25:26:0a

#### 3. Reconfigure tuxy3 and tuxy2 so that each of them can  reach the other
In tux32:
```sh
route add -net 172.16.30.0/24 gw 172.16.31.253
```

In tux33:
```sh
route add -net 172.16.31.0/24 gw 172.16.30.254
```

#### 4. Observe the routes available at the 3 tuxes (route  -n)
In tux32:
```txt
Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
172.16.30.0     172.16.31.253   255.255.255.0   UG    0      0        0 eth0
172.16.31.0     0.0.0.0         255.255.255.0   U     0      0        0 eth0
```

In tux33:
```txt
Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
172.16.30.0     0.0.0.0         255.255.255.0   U     0      0        0 eth0
172.16.31.0     172.16.30.254   255.255.255.0   UG    0      0        0 eth0
```

In tux34:
```txt
Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
172.16.30.0     0.0.0.0         255.255.255.0   U     0      0        0 eth0
172.16.31.0     0.0.0.0         255.255.255.0   U     0      0        0 eth1
```

#### 5. Start capture at tuxy3
#### 6. From tuxy3, ping the other network interfaces (172.16.y0.254, 172.16.y1.253, 172.16.y1.1) and verify if there is connectivity
```sh
ping 172.16.30.254  # tux34.eth0
ping 172.16.31.253  # tux34.eth1
ping 172.16.31.1    # tux32.eth0
```

#### 7. Stop capture and save logs
[tux33-packets-capture-step7.pcapng](tux33-packets-capture-step7.pcapng)

#### 8. Start capture in tuxy4; use 2 instances of Wireshark, one per network interface
#### 9. Clean the ARP tables in the 3 tuxes
In tux32:
```sh
arp -d 172.16.31.253
```
In tux33:
```sh
arp -d 172.16.30.254
```
in tux34:
```sh
arp -d 172.16.30.1
arp -d 172.16.31.1
```
#### 10. In tuxy3, ping tuxy2 for a few seconds.


#### 11. Stop captures in tuxy4 and save logs

[tux34-packets-capture-step8-eth0.pcapng](tux34-packets-capture-step8-eth0.pcapng)  
[tux34-packets-capture-step8-eth1.pcapng](tux34-packets-capture-step8-eth1.pcapng)