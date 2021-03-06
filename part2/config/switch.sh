## Check VLAN
# show vlan id 30   
## Check port
# show running-config interface fastethernet 0/1  # Check if everything OK
# show interfaces fastethernet 0/1 switchport     # Check if everything OK

# Enable
enable
8nortel

# Reset switch
copy flash:tux3-clean startup-config
reload

configure terminal

# Create VLAN30
vlan 30
# Add port 1 to VLAN30
interface fastethernet 0/1
switchport mode access
switchport access vlan 30
# Add port 2 to VLAN30
interface fastethernet 0/2
switchport mode access
switchport access vlan 30
end

# Create VLAN31
configure terminal
vlan 31
# Add port 3 to VLAN31
interface fastethernet 0/3
switchport mode access
switchport access vlan 31
# Add port 4 to VLAN31
interface fastethernet 0/4
switchport mode access
switchport access vlan 31
# Add port 5 to VLAN31
interface gigabitethernet 0/5
switchport mode access
switchport access vlan 31
end

show vlan                                       # Check if everything OK
