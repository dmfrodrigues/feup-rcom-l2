#### 1. Configure DNS at tuxy3, tuxy4, tuxy2; use DNS server services.netlab.fe.up.pt (172.16.1.1*)

Configure DNS:

tuxy3$ nano /etc/resolv.conf
search netlab.fe.up.pt
nameserver 172.16.1.1*

#### 2. Verify if names can be used in these hosts (e.g ping hostname, use browser)

ping netlab.fe.up.pt

#### 3. Execute ping new-hostname-in-the-Internet; observe DNS related packets in Wireshark

ping 