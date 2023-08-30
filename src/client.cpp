//
// Created by sh135 on 2023/8/29.
//
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include "../include/util.h"


int main(){
    char write_buf[BUFSIZE], read_buf[BUFSIZE];
    int server_sockfd = socket(AF_INET,SOCK_STREAM,0);
    errIf(server_sockfd == -1, "sockfd init error");

    //init server_addr
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8088);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    printf("Client Trying to Connect!\n");
    //connect
    errIf(connect(server_sockfd,(sockaddr*)&server_addr,sizeof(server_addr)),"connect error");

    //Echo response
    while(true){
        bzero(&write_buf,sizeof(write_buf));
        scanf("%s",&write_buf);

        //Sending msg
        size_t write_sig = write(server_sockfd,&write_buf,sizeof (write_buf));
        if(write_sig==0) {
            printf("Cannot Send Msg to Server!\n");
            close(server_sockfd);
        }else if(write_sig==-1){
            printf("Server Disconnected!\n");
            close(server_sockfd);
            errIf(true,"write error");
        }

        //Receiving msg
        ssize_t read_sig = read(server_sockfd,&read_buf,sizeof(read_buf));
        if(read_sig>0) {
            printf("Msg echo from server %d: %s\n", server_sockfd, read_buf);
        }else if(read_sig == 0){
            printf("Server Disconnected!\n");
            close(server_sockfd);
            break;
        }else if(read_sig==-1){
            printf("Server Disconnected!\n");
            close(server_sockfd);
            errIf(true,"write error");
        }
    }
    return 0;
}