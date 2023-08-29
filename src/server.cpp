//
// Created by sh135 on 2023/8/29.
//

//创建server_sockfd
//listen
//
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include "../include/errIf.h"

int main(){
    std::cout<<"Hello World! from server.cpp"<<std::endl;

    int server_sockfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_addr;

    //init server_addr;
    bzero(&server_addr,sizeof (server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8088);

    //bind & listen
    bind(server_sockfd,(sockaddr*)&server_addr,sizeof(server_addr));
    std::cout<<server_sockfd<<std::endl;
    listen(server_sockfd,SOMAXCONN);

    //init client_socket information
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof (client_addr);
    bzero(&client_addr,client_addr_len);

    //accept
    int client_sockfd = accept(server_sockfd,(sockaddr*)&client_addr,&client_addr_len);

    //print result
    printf("Client %d received! IP: %s , Port: %d\n",client_sockfd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    return 0;
}