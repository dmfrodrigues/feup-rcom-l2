## Cabling

tux33-eth0 ↔ switch/1  
tux34-eth0 ↔ switch/2  
tux32-eth0 ↔ switch/3  
tux32-tty0 ↔ port23 (crossover RS232)  
post24 (crossover RS232) ↔ switch config port

## Reset switch

### tux32, GTKTerm (communicate with switch)
```sh
copy flash:tux3-clean startup-config
reload
```

## Configure

### tux33

```sh
/etc/init.d/networking restart

ifconfig eth0 up
ifconfig
ifconfig eth0 172.16.30.1/24
```

### tux34

```sh
/etc/init.d/networking restart

ifconfig eth0 up
ifconfig
ifconfig eth0 172.16.30.254/24

ifconfig eth1 up
ifconfig
ifconfig eth1 172.16.31.253/24
```

### tux32

```sh
/etc/init.d/networking restart

ifconfig eth0 up
ifconfig
ifconfig eth0 172.16.31.1/24
```

### switch

You'll have to write by hand.

`8nortel` is the password.

### tux32, GTKTerm (communicate with switch)
```sh
# Enable
enable
8nortel

# Create VLAN30
configure terminal
vlan 30
end
show vlan id 30                                 # Check if everything OK
# Add port 1 to VLAN30
configure terminal
interface fastethernet 0/1
switchport mode access
switchport access vlan 30
end
show running-config interface fastethernet 0/1  # Check if everything OK
show interfaces fastethernet 0/1 switchport     # Check if everything OK
# Add port 2 to VLAN30
configure terminal
interface fastethernet 0/2
switchport mode access
switchport access vlan 30
end
show running-config interface fastethernet 0/2  # Check if everything OK
show interfaces fastethernet 0/2 switchport     # Check if everything OK

# Create VLAN31
configure terminal
vlan 31
end
show vlan id 31                                 # Check if everything OK
# Add port 3 to VLAN31
configure terminal
interface fastethernet 0/3
switchport mode access
switchport access vlan 31
end
show running-config interface fastethernet 0/3  # Check if everything OK
show interfaces fastethernet 0/3 switchport     # Check if everything OK
# Add port 4 to VLAN31
configure terminal
interface fastethernet 0/4
switchport mode access
switchport access vlan 31
end
show running-config interface fastethernet 0/4  # Check if everything OK
show interfaces fastethernet 0/4 switchport     # Check if everything OK
```

## IP forwarding

### tux34
```sh
echo 1 > /proc/sys/net/ipv4/ip_forward
echo 0 > /proc/sys/net/ipv4/icmp_echo_ignore_broadcasts
```

### tux32
```sh
route add -net 172.16.30.0/24 gw 172.16.31.253
```

### tux33
```sh
route add -net 172.16.31.0/24 gw 172.16.30.254
```

## Tests

### tux32
```sh
ping 172.16.31.253  # ping tux34-eth1
ping 172.16.30.254  # ping tux34-eth0
ping 172.16.30.1    # ping tux33-eth0
```

### tux33
```sh
ping 172.16.30.254  # ping tux34-eth0
ping 172.16.31.253  # ping tux34-eth1
ping 172.16.31.1    # ping tux32-eth0
```

### tux34
```sh
ping 172.16.30.1    # ping tux33-eth0
ping 172.16.31.1    # ping tux32-eth0
```
