#include <iostream>
using namespace std;

#include <netinet/in.h> //for sockaddr
#include <string.h> //for memset
#include <arpa/inet.h> //for inet_ntoa
#include <unistd.h> //for fork
#include <stdlib.h> // for exit

void sigchld_handler(int signo)
{
    pid_t pid;
    pid = waitpid(-1, NULL, WNOHANG);
}

void server()
{
    // recieve signal from child
    signal(SIGCHLD, sigchld_handler);

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
        if((client_fd = accept(sock, (sockaddr*)(&remoteAddr), &sin_size)) == -1 )
        {
            cerr<<"accept error" <<endl;
            continue;
        }
        cout<<"Received a connection from "<<static_cast<char*>(inet_ntoa(remoteAddr.sin_addr))<<endl;
        

        if((forkId = fork()) == 0)
        {
            int rval;
            char buf[MAXSIZE];
            if((rval = read(client_fd, buf, MAXSIZE)) < 0)
            {
                cout<<"Reading stream error"<<endl;
                continue;
            }
            cout<<buf<<endl;

            const char *msg = "Hello abc";
            if(send(client_fd, const_cast<char*>(msg), strlen(msg), 0) == -1)
            {
                cerr<<"send error"<<endl;
                close(client_fd);
                //exit(0);
            }
            exit(0);
        }
    }
}

int main()
{
    server();
    return 0;
}
