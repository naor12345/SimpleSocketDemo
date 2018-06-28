#include <iostream>
using namespace std;

#include <netinet/in.h> //for sockaddr
#include <string.h> //for memset
#include <arpa/inet.h> //for inet_ntoa
#include <unistd.h> //for fork
#include <stdlib.h> // for exit
#include <stdio.h>

#define SERVERPORT 53556
#define BACKLOG 10
#define MAXSIZE 1024
    

void str_echo(int sockfd);
void str_cli(int sockfd);