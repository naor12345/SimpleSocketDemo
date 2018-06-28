#include "./NetworkApplication.h"

void str_cli(int sockfd)
{
    int recvBytes;
    char inputChar[MAXSIZE];
    printf("input string: \n");
    cin>>inputChar;
    char buf[MAXSIZE]; 

    write(sockfd, const_cast<char*>(inputChar), strlen(inputChar));
    if((recvBytes = recv(sockfd, buf, MAXSIZE, 0)) == -1)
    {
        cerr<<"recv error"<<endl;
        exit(1);
    }
    buf[recvBytes] = '\0';
    printf("recieved string from server: \n");
    cout<<buf<<endl;
}

void str_echo(int client_fd)
{
    int rval;
    char buf[MAXSIZE];
    cout<<flush;
    if((rval = read(client_fd, buf, MAXSIZE)) < 0)
    {
        cout<<"Reading stream error"<<endl;
    }
    cout<<"from client: "<<buf<<endl;
    if(send(client_fd, const_cast<char*>(buf), strlen(buf), 0) == -1)
    {
        cerr<<"send error"<<endl;
        close(client_fd);
    }
}