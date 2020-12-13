#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/types.h>

#include "download.h"
#include "server_cmds.h"

// writes a command
void write_cmd(int sockfd, char *cmd, char *arg){
	write(sockfd, cmd, strlen(cmd));
	write(sockfd, arg, strlen(arg));
	write(sockfd, "\n", 1);
	printf("Wrote: %s%s\n", cmd, arg);
}

// write pasv cmd and returns port from pasv
int write_pasv(int sockfd){
	char first_byte[4];
	char second_byte[4];
	
	write(sockfd, "pasv\n", strlen("pasv\n"));
	printf("Wrote: pasv\n");
	
	char *res = malloc(100);
	read(sockfd, res, 100);
	printf("Reply: %s", res);

	if(res[0] == '3' || res[0] == '4' || res[0] == '5') exit(1);

	strtok(res, "(");
	strcpy(res, strtok(NULL, "("));
	strcpy(res, strtok(res, ")"));
	strtok(res, ",");
	for(int i=0; i<4; i++) strcpy(first_byte, strtok(NULL, ","));
	strcpy(second_byte, strtok(NULL, ","));

	free(res);
	return atoi(first_byte)*256 + atoi(second_byte);
}

// reads a reply from server, returns first code number
char read_reply(int sockfd){
	char code;
	char *r = malloc(MAX_STR_LEN);
	
	size_t n = 0;
	ssize_t read;

	FILE* fp = fdopen(sockfd, "r");
	while((read = getline(&r, &n, fp)) != -1) {
		if(r[3] == ' ') break;
	}

	r[MAX_STR_LEN - 1] = '\0';
	code = r[0];
	printf("Reply: %s\n", r);
	free(r);
	return code;
}

void download_file(int fd, char *url_path){

	char* filename = basename(url_path);

	FILE *f = fopen(filename, "wb+");
	
	if(f == NULL){
		perror("fopen()");
		exit(1);
	}

	char buffer[BUFFER_SIZE];
	int bytes_read;
	while((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0){
		fwrite(buffer, bytes_read, 1, f);
	}

	fclose(f);
}
