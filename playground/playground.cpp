#include <iostream>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

int main()
{
    int fkid;
    for(int i = 0; i<2; i++)
    {
        if((fkid = fork()) == 0)
        {
            
        }
    }
    return 0;
}