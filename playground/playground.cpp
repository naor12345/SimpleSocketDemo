#include <iostream>
#include <netinet/in.h>

using namespace std;

int main()
{
    cout<<"socketadd: "<<sizeof(sockaddr)<<endl;
    cout<<"socketadd_in: "<<sizeof(sockaddr_in)<<endl;
    return 0;
}