Restart communication subsystem
```sh
/etc/init.d/networking restart
```

#### 1. Configure tuxy2 and register its IP and MAC addresses
```sh
ifconfig eth0 up
ifconfig
ifconfig eth0 172.16.31.1/24
```
IP: 172.16.31.1  
MAC: 00:21:5a:61:30:63

#### 2. Create vlany0 in the switch and add corresponding ports
In GTKTerm:
```sh
enable
8nortel

# Create VLAN 30
configure terminal
vlan 30
end
show vlan id 30
```

In GTKTerm:
```sh
enable
8nortel

# Add port 1
configure terminal
interface fastethernet 0/1
switchport mode access
switchport access vlan 30
end

show running-config interface fastethernet 0/1
show interfaces fastethernet 0/1 switchport

# Add port 2
configure terminal
interface fastethernet 0/2
switchport mode access
switchport access vlan 30
end

show running-config interface fastethernet 0/2
show interfaces fastethernet 0/2 switchport
```

#### 3. Create vlany1 and add corresponding port
In GTKTerm:
```sh
enable
8nortel

# Create VLAN 31
configure terminal
vlan 31
end
show vlan id 31
```

In GTKTerm:
```sh
enable
8nortel

# Add port 3
configure terminal
interface fastethernet 0/3
switchport mode access
switchport access vlan 31
end

show running-config interface fastethernet 0/3
show interfaces fastethernet 0/3 switchport
```

#### 10. Repeat steps 7, 8 and 9, but now do ping broadcast in tuxy2 (ping -b 172.16.y1.255)
```sh
ping -b 172.16.31.255
```
