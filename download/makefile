CFLAFG=-Wall -Wextra -g

all: download
 
download: download.o url_parser.o server_cmds.o
	gcc download.o url_parser.o server_cmds.o -o download $(CFLAGS) 

download.o: download.c download.h
	gcc -c download.c $(CFLAGS)
 
url_parser.o: url_parser.c url_parser.h
	gcc -c url_parser.c $(CFLAGS)

server_cmds.o: server_cmds.c server_cmds.h
	gcc -c server_cmds.c $(CFLAGS)

test: test_novpn

test_all: test_novpn test_vpn

test_vpn:
	./download ftp://netlab1.fe.up.pt/pub.txt 				 
	./download ftp://rcom:rcom@netlab1.fe.up.pt/pipe.txt       
	./download ftp://rcom:rcom@netlab1.fe.up.pt/files/pic1.jpg
	./download ftp://rcom:rcom@netlab1.fe.up.pt/files/pic2.png
	./download ftp://rcom:rcom@netlab1.fe.up.pt/files/crab.mp4

test_novpn:
	./download ftp://speedtest.tele2.net/1MB.zip
	./download ftp://ftp.up.pt/pub/debian/README
	./download ftp://ftp.up.pt/pub/apache/README.html

clean: 
	rm download download.o url_parser.o server_cmds.o