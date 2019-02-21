#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include "crc.cpp"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
    if(argc != 2){
        cout<<"Useage ./server <port>"<<endl;
        exit(0);
    }
    int sockfd;
    struct sockaddr_in servaddr;
    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    cout<<"Wating...."<<endl;
    while(1)
    {
        char buff[100] = {0};
        struct crc_sample sample;
        recvfrom(sockfd, buff, sizeof(sample), 0, NULL, NULL);
        memcpy(&sample,buff,sizeof(sample));
        char crc[50];
        sprintf(crc,"%X",sample.crc);
        cout<<"String:"<<sample.str<<endl<<"CRC:"<<crc<<endl;
        if(strcmp(sample.str,"bye") == 0)
        {
            break;
        }
    }
    close(sockfd);
}
