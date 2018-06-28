#include <iostream>
using namespace std;

#include <netinet/in.h> //for sockaddr
#include <string.h> //for memset
#include <arpa/inet.h> //for inet_ntoa
#include <unistd.h> //for fork
#include <stdlib.h> // for exit
#include <sys/wait.h>

#include "./NetworkApplication.h"

static void sigchld_handler(int signo)
{
    pid_t pid;
    int stat;
    while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
        // loop terminate for all child process
        printf("child %d terminated\n", pid);
    }
}

static void sigint_handler(int signo)
{
    cout<<endl;
    cout<<"quit "<<endl;
    exit(0);
}

int main()
{  
    // recieve signal from child
    signal(SIGCHLD, sigchld_handler);
    signal(SIGINT, sigint_handler);
    int socketfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    sockaddr_in cliaddr, servaddr;

    // create socket
    if((socketfd = socket(AF_INET, SOCK_STREAM, 0))==-1)
    {
        cerr<<"socket fail"<<endl;
        exit(1);
    }

    cout<<"socket: "<<socketfd<<endl;

    // set server addr
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERVERPORT);
    // bind
    if(bind(socketfd, (sockaddr*)(&servaddr), sizeof(sockaddr)) == -1)
    {
        cerr<<"bind error"<<endl;
        exit(1);
    }
    // listen
    if(listen(socketfd, BACKLOG) == -1)
    {
        cerr<<"listen error"<<endl;
        exit(1);
    }

    while(true)
    {
        clilen = sizeof(cliaddr);
        if((connfd = accept(socketfd, (sockaddr*)(&cliaddr), &clilen)) < 0)
        {
            cerr<<"accept error"<<endl;
            continue;
        }

        if((childpid = fork()) == 0)
        {
            close(socketfd);
            // application function
            str_echo(connfd);
            exit(0);
        }
        close(connfd);
    }
}