#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
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
    int n;
    char recvline[1024];
    cout<<"Wating...."<<endl;
    while(1)
    {
        memset(recvline,0,1024);
        recvfrom(sockfd, recvline, 1024, 0, NULL, NULL);
        cout<<recvline<<endl;
        if(strcmp(recvline,"bye") == 0)
        {
            break;
        }
    }
    close(sockfd);
}
