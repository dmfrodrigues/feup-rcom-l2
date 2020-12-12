#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <netdb.h> 
#include <sys/types.h>
#include <netinet/in.h> 
#include <arpa/inet.h>

#include <string.h>

#define SERVER_PORT 21

/*
ex.: 
download ftp://netlab1.fe.up.pt/pub.txt
*/

struct hostent* get_ip(char *hostname){
	struct hostent *h;
	/*
	struct hostent {
		char    *h_name;	Official name of the host. 
    	char    **h_aliases;	A NULL-terminated array of alternate names for the host. 
		int     h_addrtype;	The type of address being returned; usually AF_INET.
    	int     h_length;	The length of the address in bytes.
		char    **h_addr_list;	A zero-terminated array of network addresses for the host. 
				Host addresses are in Network Byte Order. 
	};

	#define h_addr h_addr_list[0]	The first address in h_addr_list. 
	*/

    if ((h=gethostbyname(hostname)) == NULL) {  
            herror("gethostbyname");
            exit(1);
    }

    printf("Host name  : %s\n", h->h_name);
    printf("IP Address : %s\n",inet_ntoa(*((struct in_addr *)h->h_addr)));

	return h;
}

void parse_url(char *url, char *user, char *pwd, char *host, char *url_path){

	if(strncmp(url, "ftp://", 6) != 0){
		fprintf(stderr,"Error: url should start with ftp:// \n");
		exit(0);
	}
	
	// url without ftp://
	char *_url = (char*)malloc(strlen(url) - 5);
	memcpy(_url, url + 6, strlen(url) - 6);
	_url[strlen(_url)] = '\0';
	
	char *_url_cpy = malloc(strlen(url) - 6);
	
	// Get user and password if defined
	if(strchr(_url, '@') != NULL){
		strcpy(_url_cpy, _url);
		strtok(_url_cpy, "@");

		strcpy(user, strtok(_url_cpy, ":")); 
		strcpy(pwd, strtok(NULL, ":"));
		
		// Get host
		strcpy(_url_cpy, _url);
		strtok(_url_cpy, "@"); 
		_url_cpy = strtok(NULL, "@");
	
		strcpy(host, strtok(_url_cpy, "/"));
	
		// Get url_path
		memcpy(url_path, _url  + strlen(user) + strlen(pwd) + 2 + strlen(host), strlen(_url) - strlen(host));
	}
	else{
		strcpy(user, "anonymous");
		strcpy(pwd, "pwd");
		// Get host
		strcpy(_url_cpy, _url);
		strcpy(host, strtok(_url_cpy, "/"));
	
		// Get url_path
		memcpy(url_path, _url  + strlen(host) + 1, strlen(_url) - strlen(host) - 1);
	}
	
	printf("user: %s\n", user);
	printf("pwd: %s\n", pwd);
	printf("host: %s\n", host);
	printf("url-path: %s %d\n", url_path, strlen(url_path));
}

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

	strtok(res, "(");
	strcpy(res, strtok(NULL, "("));
	strcpy(res, strtok(res, ")"));
	strtok(res, ",");
	for(int i=0; i<4; i++) strcpy(first_byte, strtok(NULL, ","));
	strcpy(second_byte, strtok(NULL, ","));

	free(res);
	return atoi(first_byte)*256 + atoi(second_byte);
}

// reads a reply from server
void read_reply(int sockfd){
	char *r = malloc(100);
	read(sockfd, r, 100);
	printf("Reply: %s\n", r);
	free(r);
}

void download_file(int fd, char *url_path){
	FILE *f = fopen(url_path, "wb+");

	char buffer[1024];
	int bytes_read;
	while((bytes_read = read(fd, buffer, 1024)) > 0){
		fwrite(buffer, bytes_read, 1, f);
	}
	fclose(f);
}

int main(int argc, char *argv[])
{
	if (argc != 2) {  
        fprintf(stderr,"usage: download ftp://[<user>:<password>@]<host>/<url-path> \n");
        exit(1);
    }
	
    int sockfd;
	int sockfd_b;
	struct sockaddr_in server_addr_a;
	struct sockaddr_in server_addr_b;

	char *user     = (char*)malloc(256); // optional
	char *pwd      = (char*)malloc(256); // optional
	char *host     = (char*)malloc(256);
	char *url_path = (char*)malloc(256);

	parse_url(argv[1], user, pwd, host, url_path);

	struct hostent *h = get_ip(host);

	/*server address handling*/

	bzero((char *)&server_addr_a, sizeof(server_addr_a));
	server_addr_a.sin_family = AF_INET;
	server_addr_a.sin_addr.s_addr = inet_addr(inet_ntoa(*((struct in_addr *)h->h_addr))); /*32 bit Internet address network byte ordered*/
	server_addr_a.sin_port = htons(SERVER_PORT); /*server TCP port must be network byte ordered */

	/*open an TCP socket*/
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket()");
		exit(0);
	}

	/*connect to the server*/
	if (connect(sockfd,
				(struct sockaddr *)&server_addr_a,
				sizeof(server_addr_a)) < 0)
	{
		perror("connect()");
		exit(0);
	}

	// login host
	read_reply(sockfd);

	write_cmd(sockfd, "user ", user);
	read_reply(sockfd);

	write_cmd(sockfd, "pass ", pwd);
	read_reply(sockfd);

	// Enter passive mode
	int port = write_pasv(sockfd);
	printf("Port: %d\n", port);

	// Get file path

	/*server address handling*/
	bzero((char *)&server_addr_b, sizeof(server_addr_b));
	server_addr_b.sin_family = AF_INET;
	server_addr_b.sin_addr.s_addr = inet_addr(inet_ntoa(*((struct in_addr *)h->h_addr)));
	server_addr_b.sin_port = htons(port);

	/*open an TCP socket*/
	if ((sockfd_b = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket()");
		exit(0);
	}

	/*connect to the server*/
	if (connect(sockfd_b,
				(struct sockaddr *)&server_addr_b,
				sizeof(server_addr_b)) < 0)
	{
		perror("connect()");
		exit(0);
	}

	// Save file if successfull
	write_cmd(sockfd, "retr ", url_path);
	
	download_file(sockfd_b, url_path);

	write_cmd(sockfd, "quit", "");
	read_reply(sockfd);

	close(sockfd);
	close(sockfd_b);
	exit(0);
}
