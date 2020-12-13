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

clean: 
	rm download download.o url_parser.o server_cmds.o