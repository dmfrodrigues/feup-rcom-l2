#### 1. Configure commercial router RC and connect it (no NAT) to the lab network (172.16.1.39/24)*

interface gigabitethernet 0/0
ip address 172.16.1.39 255.255.255.0
no shutdown 
exit
show interface gigabitethernet 0/0

#### 2. Verify routes
ip route 
##### tuxy4 as default router of tuxy3; Rc as default router for tuxy2 and tuxy4

##### Routes for 172.16.y0.0/24 in tuxy2 and Rc

#### 3. Using ping commands and wireshark, verify if tuxy3 can ping all the network interfaces of tuxy4, tuxy2 and Rc

ping 172.16.31.0

ping 172.16.30.253

ping 172.16.30.254

#### 4.

##### Do: echo 0 > /proc/sys/net/ipv4/conf/eth0/accept_redirects and echo 0 > /proc/sys/net/ipv4/conf/all/accept_redirects

##### remove the route to 172.16.y0.0/24 via tuxy4

route del -net 172.16.30.0 netmask 255.255.255.0

##### In tuxy2, ping tuxy3

ping 

##### Using capture at tuxy2, try to understand the path followed by ICMP ECHO and ECHO-REPLY packets (look at MAC addresses)



##### In tuxy2, do traceroute tuxy3

traceroute 172.16.30.0

##### In tuxy2, add again the route to 172.16.y0.0/24 via tuxy4 and do traceroute tuxy3

route add -net 172.16.31.0/24 gw 172.16.31.253

##### Activate the acceptance of ICMP redirect at tuxy2 when there is no route to 172.16.y0.0/24 via tuxy4 and try to understand what happens

?

#### 5. In tuxy3, ping the router of the lab I.321 (172.16.1.254)** and try to understand what happens

ping 172.16.1.254

#### 6. Add NAT functionality to router Rc

y = 3

conf t
interface gigabitethernet 0/0 *
ip address 172.16.y1.254 255.255.255.0
no shutdown
ip nat inside
exit
interface gigabitethernet 0/1*
ip address 172.16.1.y9 255.255.255.0
no shutdown
ip nat outside
exit
ip nat pool ovrld 172.16.1.y9 172.16.1.y9 prefix 24
ip nat inside source list 1 pool ovrld overload
access-list 1 permit 172.16.y0.0 0.0.0.7
access-list 1 permit 172.16.y1.0 0.0.0.7
ip route 0.0.0.0 0.0.0.0 172.16.1.254
ip route 172.16.y0.0 255.255.255.0 172.16.y1.253
end

#### 7. In tuxy3 ping 172.16.1.254**, verify if there is connectivity, and try to understand what happens
