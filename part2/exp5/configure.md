#### 1. Configure DNS at tuxy3, tuxy4, tuxy2; use DNS server services.netlab.fe.up.pt (172.16.1.1*)

In tux32, tux33 and tux34:
```
echo -e "search netlab.fe.up.pt\nnameserver 172.16.1.1 *" > /etc/resolv.conf
```

#### 2. Verify if names can be used in these hosts (e.g ping hostname, use browser)

```sh
ping google.com
ping example.com
ping example.org
```

Go to browser and play around.

#### 3. Execute ping new-hostname-in-the-Internet; observe DNS related packets in Wireshark

In tux33:

Start WireShark

```sh
ping www.sapo.pt
```
