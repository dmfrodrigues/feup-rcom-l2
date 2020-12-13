#ifndef _URL_PARSER_H_
#define _URL_PARSER_H_

int is_valid_url(char *url);

void parse_url(char *url, char *user, char *pwd, char *host, char *url_path);

#endif //_URL_PARSER_H_