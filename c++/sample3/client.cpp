#include <stdio.h>   
#include <string.h>   
#include <errno.h>   
#include <stdlib.h>   
#include <unistd.h>   
#include <sys/types.h>   
#include <sys/socket.h>   
#include <netinet/in.h>   
#include <arpa/inet.h>
#include <errno.h>
#include "crc.cpp"
#include <iostream>
using namespace std;
extern int errno;
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

    while(1)
    {
        struct crc_sample sample;
        memset(sample.str,0,50);
        cout<<"Input Text:";
        cin.getline(sample.str,50);
        sample.crc = crc32(sample.str,strlen(sample.str));
        int send_num = sendto(sock_fd, &sample, sizeof(sample), 0, (struct sockaddr *)&addr_serv, sizeof(struct sockaddr_in));
        printf("Send %d bytes finished.\n",send_num);
        if(strcmp(sample.str,"bye") == 0)
        {
            break;
        }
    }
    close(sock_fd);
}

