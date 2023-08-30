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
#include <unistd.h>

#include "../include/util.h"



int main(){
    //init server_addr;
    int server_sockfd = socket(AF_INET,SOCK_STREAM,0);
    errIf(server_sockfd == -1, "sockfd init error");

    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof (server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8088);

    //bind & listen
    errIf(bind(server_sockfd,(sockaddr*)&server_addr,sizeof(server_addr)),"socket bind error");
    errIf(listen(server_sockfd,SOMAXCONN),"socket listen error");

    //init client_socket information
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof (client_addr);
    bzero(&client_addr,client_addr_len);

    //accept
    printf("Server Waiting for Connected!\n");
    int client_sockfd = accept(server_sockfd,(sockaddr*)&client_addr,&client_addr_len);
    errIf(client_sockfd==-1,"client_socketfd accept error");
    //print result
    printf("Client %d received! IP: %s , Port: %d\n",client_sockfd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    char read_buf[BUFSIZE];

    while (true){
        bzero(&read_buf,sizeof (read_buf));
        printf("Server Waiting!\n");
        ssize_t read_bytes = read(client_sockfd,&read_buf,sizeof (read_buf));
        if(read_bytes>0){
            printf("Message from client %d: %s\n",client_sockfd,read_buf);
            printf("Echo to Client: %d\n",client_sockfd);
            write(client_sockfd,read_buf,sizeof(read_buf));
        }else if(read_bytes==0){// Connection closed;
            printf("Connection from %d closed\n",client_sockfd);
            close(client_sockfd);
            break;
        }else if(read_bytes==-1){
            printf("Client Disconnected!\n");
            close(client_sockfd);
            errIf(true,"read error");
        }
    }

    // TODO 2 Add & Learn Epoll to suit high concurrency

    return 0;
}