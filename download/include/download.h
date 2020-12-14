// Copyright (C) 2020 Diogo Rodrigues, Breno Pimentel
// Distributed under the terms of the GNU General Public License, version 3

#ifndef _DOWNLOAD_H_
#define _DOWNLOAD_H_

#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <netdb.h> 
#include <sys/types.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <libgen.h>
#include <unistd.h>
#include <string.h>

#include "url_parser.h"
#include "server_cmds.h"

#define SERVER_PORT 21
#define BUFFER_SIZE 1024
#define MAX_STR_LEN 1024



#endif // _DOWNLOAD_H_