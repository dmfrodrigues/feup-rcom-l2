## Cabling

tux33-eth0 ↔ switch/1  
tux34-eth0 ↔ switch/2  
tux32-eth0 ↔ switch/3  
tux32-tty0 ↔ port23 (crossover RS232)  
post24 (crossover RS232) ↔ switch config port

## Reset switch

Ask the teacher

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
```

