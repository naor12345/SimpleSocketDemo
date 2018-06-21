#include "aSimpleSocketTest/ServerApplication.h"

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