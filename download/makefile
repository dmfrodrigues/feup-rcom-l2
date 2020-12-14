# Copyright (C) 2020 Diogo Rodrigues, Breno Pimentel
# Distributed under the terms of the GNU General Public License, version 3

SDIR    =./src
IDIR    =./include
ODIR    =./obj

CC      =gcc
CFLAGS  =-Wall -Wextra -g -I$(IDIR)

all: download
 
download: $(ODIR)/download.o $(ODIR)/url_parser.o $(ODIR)/server_cmds.o
	$(CC) $(ODIR)/download.o $(ODIR)/url_parser.o $(ODIR)/server_cmds.o $(CFLAGS) -o download

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	$(CC) -c $< $(CFLAGS) -o $@

$(ODIR):
	mkdir $(ODIR)

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
	rm -f download
	rm -rf obj
	rm -f 1MB.zip crab.mp4 pic1.jpg pic2.png pipe.txt pub.txt README README.html
