### Experiment 1 - Configure an IP network
This experiment consisted in connecting two computers by configuring its IPs and creating routes to the forwarding tables.
We were able to check the connectivity using the ping command.

#### ARP packets
ARP converts an IP address to a MAC address.

#### ping command
Ping generates ICMP packets. The length of this packets are in the bytes 16 and 17 of the frame.

#### Loopback
The loopback interface is used by the computer to send and receive packets to itself. In the experiment, we could verify loopback packets when the source and destination addresses were equal. It is important for diagnostics.

» What are the ARP packets and what are they used for?

» What are the MAC and IP addresses of ARP packets and why?

» What packets does the ping command generate?

» What are the MAC and IP addresses of the ping packets?

» How to determine if a receiving Ethernet frame is ARP, IP, ICMP?

With the protocol identifier in the frame?

» How to determine the length of a receiving frame?

» What is the loopback interface and why is it important?
