#include <iostream>
using namespace std;

#include <netinet/in.h> //for sockaddr
#include <string.h> //for memset
#include <arpa/inet.h> //for inet_ntoa
#include <unistd.h> //for fork
#include <stdlib.h> // for exit
#include <sys/wait.h>

void sigchld_handler(int signo)
{
    pid_t pid;
    int stat;
    while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
        // loop terminate for all child process
        printf("child %d terminated\n", pid);
    }
}

void sigint_handler(int signo)
{
    cout<<endl;
    cout<<"quit "<<endl;
    exit(0);
}

void server()
{
    // recieve signal from child
    signal(SIGCHLD, sigchld_handler);
    signal(SIGINT, sigint_handler);

    const unsigned short SERVERPORT = 53556;
    const int BACKLOG = 10;
    const int MAXSIZE = 1024;
    int sock, client_fd;
    sockaddr_in myAddr;
    sockaddr_in remoteAddr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    // create socket
    if(sock == -1)
    {
        cerr<<"socket fail"<<endl;
        exit(1);
    }

    cout<<"sock: "<<sock << endl;

    //bind
    myAddr.sin_family = AF_INET;
    myAddr.sin_port = htons(SERVERPORT);
    myAddr.sin_addr.s_addr = INADDR_ANY;
    // bzero(&(myAddr.sin_zero), 8);
    memset(&(myAddr.sin_zero), 0, 8*sizeof(char));
    if(bind(sock, (sockaddr*)(&myAddr), sizeof(sockaddr)) == -1)
    {
        cerr<<"bind error"<<endl;
        exit(1);
    }

    //listen
    if(listen(sock, BACKLOG) == -1)
    {
        cerr<<"listen error"<<endl;
        exit(1);
    }

    int forkId;
    while(true)
    {
        unsigned int sin_size = sizeof(sockaddr_in);
        if((client_fd = accept(sock, (sockaddr*)(&remoteAddr), &sin_size)) < 0 )
        {
            if(errno == EINTR)
                continue;
            else
            {
                cerr<<"accept error" <<endl;
                // exit(1);
                continue;
            }
        }
        cout<<"Received a connection from "<<static_cast<char*>(inet_ntoa(remoteAddr.sin_addr))<<" , fd: "<<client_fd<<endl;
        

        if((forkId = fork()) == 0)
        {
            close(sock);
            int rval;
            char buf[MAXSIZE];
            
            // flush the buffer
            //cout<<endl;
            cout<<flush;
            if((rval = read(client_fd, buf, MAXSIZE)) < 0)
            {
                cout<<"Reading stream error"<<endl;
                continue;
            }
            cout<<"from client: "<<buf<<endl;

            //const char *msg = "Hello abc";
            if(send(client_fd, const_cast<char*>(buf), strlen(buf), 0) == -1)
            {
                cerr<<"send error"<<endl;
                close(client_fd);
                //exit(0);
            }
            exit(0);
        }
        close(client_fd);
    }
}

int main()
{
    server();
    return 0;
}
