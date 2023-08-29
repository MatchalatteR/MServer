//
// Created by sh135 on 2023/8/29.
//
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include "../include/util.h"


int main(){
    int server_sockfd = socket(AF_INET,SOCK_STREAM,0);
    errIf(server_sockfd == -1, "sockfd init error");

    //init server_addr
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8088);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //connect
    errIf(connect(server_sockfd,(sockaddr*)&server_addr,sizeof(server_addr)),"connect error");

    return 0;
}
