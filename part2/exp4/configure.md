#### 1. Configure commercial router RC and connect it (no NAT) to the lab network (172.16.1.39/24)*

Configure router:
```sh

configure terminal

# VLAN31 interface
interface gigabitethernet 0/0
ip address 172.16.31.254 255.255.255.0
no shutdown 

exit

# Internet interface
interface gigabitethernet 0/1
ip address 172.16.1.39 255.255.255.0
no shutdown 
end

show interface gigabitethernet 0/0
show interface gigabitethernet 0/1
```

Configure switch:
```sh
enable
8nortel

# Add port 5
configure terminal
interface fastethernet 0/5
switchport mode access
switchport access vlan 31
end

show running-config interface fastethernet 0/5
show interfaces fastethernet 0/5 switchport
```

#### 2. Verify routes
##### tuxy4 as default router of tuxy3; Rc as default router for tuxy2 and tuxy4

In tux33:
```sh
route add default gw 172.16.30.254
```

In tux32 and tux34:
```sh
route add default gw 172.16.31.254
```

##### Routes for 172.16.y0.0/24 in tuxy2 and Rc

In tux32:
```sh
# Route from tux32 to VLAN30 via tux34
route                                               # Check if there is a route to 172.16.30.0 already
route add -net 172.16.30.0/24 gw 172.16.31.253      # Add if not yet added
```

In Rc:
```sh
# Route from tux32 to VLAN30 via tux34
ip route 172.16.30.0 255.255.255.0 172.16.31.253
end
```

#### 3. Using ping commands and wireshark, verify if tuxy3 can ping all the network interfaces of tuxy4, tuxy2 and Rc

In tux33:
```sh
ping 172.16.30.254  # tux34-eth0
ping 172.16.31.253  # tux34-eth1
ping 172.16.31.1    # tux32-eth0
ping 172.16.31.254  # Rc-inside
ping 172.16.1.39    # Rc-outside
```

#### 4. In tuxy2

##### (a) Do: echo 0 > /proc/sys/net/ipv4/conf/eth0/accept_redirects and echo 0 > /proc/sys/net/ipv4/conf/all/accept_redirects

In tux32:
```sh
echo 0 > /proc/sys/net/ipv4/conf/eth0/accept_redirects
echo 0 > /proc/sys/net/ipv4/conf/all/accept_redirects
```

##### (b) remove the route to 172.16.y0.0/24 via tuxy4

```sh
route del -net 172.16.30.0/24
```

##### (c) In tuxy2, ping tuxy3

In tux32:
```
ping 172.16.30.1
```

##### (d) Using capture at tuxy2, try to understand the path followed by ICMP ECHO and ECHO-REPLY packets (look at MAC addresses)

##### (e) In tuxy2, do traceroute tuxy3

```sh
traceroute 172.16.30.1
```

##### (f) In tuxy2, add again the route to 172.16.y0.0/24 via tuxy4 and do traceroute tuxy3

```sh
route add -net 172.16.30.0/24 gw 172.16.31.253
traceroute tux33
```

##### (g) Activate the acceptance of ICMP redirect at tuxy2 when there is no route to 172.16.y0.0/24 via tuxy4 and try to understand what happens

In tux32:
```sh
# Accept ICMP redirects
echo 1 > /proc/sys/net/ipv4/conf/eth0/accept_redirects
echo 1 > /proc/sys/net/ipv4/conf/all/accept_redirects

# Delete route and test
route del -net 172.16.30.0/24
ping 172.16.30.1
traceroute 172.16.30.1

# Re-add route
route add -net 172.16.30.0/24 gw 172.16.31.253
```

#### 5. In tuxy3, ping the router of the lab I.321 (172.16.1.254)** and try to understand what happens

In tux33:
```sh
ping 172.16.1.254
```

#### 6. Add NAT functionality to router Rc

```sh
conf t
interface gigabitethernet 0/0
ip address 172.16.31.254 255.255.255.0
no shutdown
ip nat inside
exit

interface gigabitethernet 0/1
ip address 172.16.1.39 255.255.255.0
no shutdown
ip nat outside
exit

ip nat pool ovrld 172.16.1.39 172.16.1.39 prefix 24
ip nat inside source list 1 pool ovrld overload

access-list 1 permit 172.16.30.0 0.0.0.7
access-list 1 permit 172.16.31.0 0.0.0.7

ip route 0.0.0.0 0.0.0.0 172.16.1.254
ip route 172.16.30.0 255.255.255.0 172.16.31.253
end
```

#### 7. In tuxy3 ping 172.16.1.254**, verify if there is connectivity, and try to understand what happens

In tux33:

Run WireShark

```sh
ping 172.16.1.254   # Lab router
```
