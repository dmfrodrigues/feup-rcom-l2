# Enable
enable
8nortel

# Reset switch
copy flash:tux3-clean startup-config
reload

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
# Add port 5 to VLAN31
configure terminal
interface fastethernet 0/5
switchport mode access
switchport access vlan 31
end
show running-config interface fastethernet 0/5  # Check if everything OK
show interfaces fastethernet 0/5 switchport     # Check if everything OK
