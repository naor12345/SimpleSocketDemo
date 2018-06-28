#include <iostream>
using namespace std;

#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h> // for exit

#include "./NetworkApplication.h"

static void sigint_handler(int signo)
{
    cout<<endl;
    cout<<"quit "<<endl;
    exit(0);
}

void client()
{
    const char *SERVER_IP = "127.0.0.1";
    int sock; 
    sockaddr_in serv_addr; 
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
    { 
        cerr<<"socket create fail"<<endl; exit(1); 
    } 

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVERPORT);
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if(connect(sock, (sockaddr*)&serv_addr, sizeof(sockaddr)) == -1)
    {
        cerr<<"connet error"<<endl;
        exit(1);
    }
    // network application
    str_cli(sock);


    
    close(sock);
}

int main()
{
    client();
    return 0;
}