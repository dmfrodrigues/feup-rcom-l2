// Copyright (C) 2020 Diogo Rodrigues, Breno Pimentel
// Distributed under the terms of the GNU General Public License, version 3

#ifndef _SERVER_CMDS_H_
#define _SERVER_CMDS_H_

void write_cmd(int sockfd, char *cmd, char *arg);

int write_pasv(int sockfd);

char read_reply(int sockfd);

void download_file(int fd, char *url_path);

#endif //_SERVER_CMDS_H_