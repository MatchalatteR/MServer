//
// Created by sh135 on 2023/8/29.
//
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>


int main(){
    std::cout<<"Hello World! from Client"<<std::endl;

    int server_sockfd = socket(AF_INET,SOCK_STREAM,0);
    std::cout<<server_sockfd<<std::endl;

    //init server_addr
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8088);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //connect
    connect(server_sockfd,(sockaddr*)&server_addr,sizeof(server_addr));

    if(connect(server_sockfd,(sockaddr*)&server_addr,sizeof(server_addr)) == -1){
        perror("Connect error");
        exit(-1);
    }
    connect(server_sockfd,(sockaddr*)&server_addr,sizeof(server_addr));


    return 0;
}
