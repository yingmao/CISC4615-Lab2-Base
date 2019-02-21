#include <stdio.h>   
#include <string.h>   
#include <errno.h>   
#include <stdlib.h>   
#include <unistd.h>   
#include <sys/types.h>   
#include <sys/socket.h>   
#include <netinet/in.h>   
#include <arpa/inet.h>
#include <iostream>
using namespace std;
int main(int argc,char* argv[])
{
    if(argc != 3){
        printf("Useage ./client <server ip> <port>");
        exit(0);
    }
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr_serv;
    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = inet_addr(argv[1]);
    addr_serv.sin_port = htons(atoi(argv[2]));
    int len = sizeof(addr_serv);
    char input[1024];
    while(1)
    {
        cout<<"Input Text:";
        cin.getline(input,1024);
        int send_num = sendto(sock_fd, input, strlen(input), 0, (struct sockaddr *)&addr_serv, len);
        cout<<"send "<<send_num<<" bytes..."<<endl;
        if(strcmp(input,"bye") == 0)
        {
            break;
        }
    }
    close(sock_fd);
}
