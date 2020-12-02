#### 4. Start capture at tuxy3.eth0
#### 5. In tuxy3, ping tuxy4 and then ping tuxy2
```sh
ping 172.16.30.254  # Succeeds
ping 172.16.31.1    # Fails, because there is no router between the virtual networks
```
#### 6. Stop capture and save log
[tux33-packets-captured-step5.pcapng](tux33-packets-captured-step5.pcapng)

#### 7. Start new captures in tuxy3.eth0, tuxy4.eth0, and tuxy2.eth0
#### 8. In tuxy3, do ping broadcast (ping -b 172.16.y0.255) for a few seconds
```sh
ping -b 172.16.30.255
```
#### 9. Observe results, stop captures and save logs
[tux32-packets-captured-step7.pcapng](tux32-packets-captured-step7.pcapng)
[tux33-packets-captured-step7.pcapng](tux33-packets-captured-step7.pcapng)
[tux34-packets-captured-step7.pcapng](tux34-packets-captured-step7.pcapng)