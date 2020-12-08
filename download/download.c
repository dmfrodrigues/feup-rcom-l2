#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <netdb.h> 
#include <sys/types.h>
#include <netinet/in.h> 
#include <arpa/inet.h>

#include <string.h>

#define SERVER_PORT 21

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
	char *_url = malloc(strlen(url) - 6);
	memcpy(_url, url + 6, strlen(url) - 6);
	
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
		user[0] = '\0';
		pwd[0] = '\0';
		// Get host
		strcpy(_url_cpy, _url);
		strcpy(host, strtok(_url_cpy, "/"));
	
		// Get url_path
		memcpy(url_path, _url  + strlen(host), strlen(_url) - strlen(host));
	}
	
	printf("user: %s\n", user);
	printf("pwd: %s\n", pwd);
	printf("host: %s\n", host);
	printf("url-path: %s\n", url_path);
}

int main(int argc, char *argv[])
{
	if (argc != 2) {  
        fprintf(stderr,"usage: download ftp://[<user>:<password>@]<host>/<url-path> \n");
        exit(1);
    }
	
    int sockfd;
	struct sockaddr_in server_addr;
	int bytes;

	char *user     = (char*)malloc(256); // optional
	char *pwd      = (char*)malloc(256); // optional
	char *host     = (char*)malloc(256);
	char *url_path = (char*)malloc(256);

	parse_url(argv[1], user, pwd, host, url_path);

	struct hostent *h = get_ip(host);

	/*server address handling*/

	bzero((char *)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(inet_ntoa(*((struct in_addr *)h->h_addr))); /*32 bit Internet address network byte ordered*/
	server_addr.sin_port = htons(SERVER_PORT); /*server TCP port must be network byte ordered */

	/*open an TCP socket*/
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket()");
		exit(0);
	}

	/*connect to the server*/
	if (connect(sockfd,
				(struct sockaddr *)&server_addr,
				sizeof(server_addr)) < 0)
	{
		perror("connect()");
		exit(0);
	}

	// TODO login host

	write(sockfd, "user ", 5);
	bytes = write(sockfd, "rcom", strlen("rcom"));
	printf("Bytes escritos %d\n", bytes);
	
	// TODO read server reply
	char r[100];
	read(sockfd, r, 100);
	printf("Reply: %s\n", r);

	close(sockfd);
	exit(0);
}