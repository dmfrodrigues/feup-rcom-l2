root
8nortel

# VLAN31 interface
conf t
interface gigabitethernet 0/0
ip address 172.16.31.254 255.255.255.0
no shutdown
ip nat inside
exit
show interface gigabitethernet 0/0

# Internet interface
interface gigabitethernet 0/1
ip address 172.16.1.39 255.255.255.0
no shutdown
ip nat outside
exit
show interface gigabitethernet 0/1

# Routes
ip nat pool ovrld 172.16.1.39 172.16.1.39 prefix 24
ip nat inside source list 1 pool ovrld overload

access-list 1 permit 172.16.30.0 0.0.0.7
access-list 1 permit 172.16.31.0 0.0.0.7

ip route 0.0.0.0 0.0.0.0 172.16.1.254
ip route 172.16.30.0 255.255.255.0 172.16.31.253
end
