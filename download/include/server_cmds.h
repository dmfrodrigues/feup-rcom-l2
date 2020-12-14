// Copyright (C) 2020 Diogo Rodrigues, Breno Pimentel
// Distributed under the terms of the GNU General Public License, version 3

#ifndef _SERVER_CMDS_H_
#define _SERVER_CMDS_H_

/*
 * @brief Writes a command to socket
 * 
 * @param sockfd   Socket file descriptor
 * @param cmd      Command
 * @param arg      Command argument
 */
void write_cmd(int sockfd, char *cmd, char *arg);

/*
 * @brief Writes a pasv command
 * 
 * @param sockfd   Socket file descriptor
 * @return int     Port the server is listening on  
 */
int write_pasv(int sockfd);


/*
 * @brief Reads server reply
 * 
 * @param sockfd   Socket file descriptor
 * @return char    Char with the reply code
 */
char read_reply(int sockfd);


/*
 * @brief Copies a file from url_path to CWD
 * 
 * @param fd         File descriptor
 * @param url_path   URL path
 * @return char      Char with the reply code
 */
void download_file(int fd, char *url_path);

#endif //_SERVER_CMDS_H_