#include <stdlib.h>
#include <regex.h>

#include "url_parser.h"
#include "download.h"

int is_valid_url(char *url){
	regex_t regex_exp;
	// https://stackoverflow.com/questions/34189307/ftp-url-regular-expression-in-c-posix
	// This may need changes
	if(regcomp(&regex_exp, "^ftp://([a-z0-9]+:[a-z0-9]+@)?([\\.a-z0-9-]+)/([\\./a-z0-9]+)$", REG_EXTENDED|REG_ICASE)){
		exit(1);
	}
	if(regexec(&regex_exp, url , 0, NULL, 0) == 0) {
		regfree(&regex_exp);
		return 0;
	}
	else {
		regfree(&regex_exp);
		return 1;
	}
}

void parse_url(char *url, char *user, char *pwd, char *host, char *url_path){

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
		memcpy(url_path, _url  + strlen(user) + strlen(pwd) + 3 + strlen(host), strlen(_url) - strlen(host));
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
	printf("url-path: %s\n", url_path);
}