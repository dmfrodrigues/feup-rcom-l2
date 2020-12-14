// Copyright (C) 2020 Diogo Rodrigues, Breno Pimentel
// Distributed under the terms of the GNU General Public License, version 3

#ifndef _URL_PARSER_H_
#define _URL_PARSER_H_


/*
 * @brief Check if a URL is valid
 * 
 * @return int  0 on success, 1 otherwise
*/
int is_valid_url(char *url);


/*
 * @brief Parses a URL
 * 
 * @param url       URL
 * @param user      Username
 * @param pwd       Password
 * @param host      Hostname
 * @param url_path  File path in url
*/
void parse_url(char *url, char *user, char *pwd, char *host, char *url_path);

#endif //_URL_PARSER_H_