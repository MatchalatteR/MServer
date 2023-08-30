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
#include <sys/epoll.h>
#include "../include/util.h"



void echo_client(int client_sockfd, char* read_buf, int epoll_fd){
    bzero(read_buf,BUFSIZE);
    printf("Server Waiting!\n");
    ssize_t read_bytes = read(client_sockfd,read_buf,BUFSIZE);
    if(read_bytes>0){
        printf("Message from client %u: %s\n",client_sockfd,read_buf);
        printf("Echo to Client: %u\n",client_sockfd);
        write(client_sockfd,read_buf,BUFSIZE);
    }else if(read_bytes==0){// Connection closed;
        printf("Connection from %d closed\n",client_sockfd);
        close(client_sockfd);
		epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_sockfd, NULL);
	}else if(read_bytes==-1){
        printf("Client Disconnected!\n");
        close(client_sockfd);
        errIf(true,"read error");
    }
}

int main(){
    char read_buf[BUFSIZE];

    //init server fd && addr;
    int server_sockfd = socket(AF_INET,SOCK_STREAM,0);
    errIf(server_sockfd == -1, "sockfd init error");
    struct sockaddr_in server_addr = {AF_INET, htons(SERVER_PORT),{.s_addr = inet_addr(SERVER_IPADDR)}};

    //init client_socket information
    struct sockaddr_in client_addr = {};
    socklen_t client_addr_len = sizeof (client_addr);
    bzero(&client_addr,client_addr_len);

    //bind & listen
    errIf(bind(server_sockfd,(sockaddr*)&server_addr,sizeof(server_addr)),"socket bind error");
    errIf(listen(server_sockfd,SOMAXCONN),"socket listen error");
    printf("After Listen\n");
    //using epoll
    //create ep_fd
    int epoll_fd = epoll_create1(0);
    errIf(epoll_fd==-1,"Cannot create epoll!\n");
    //create ep_event
    struct epoll_event ev{EPOLLIN,{.fd = server_sockfd}}, ep_events[MAX_EVENTS];
    errIf(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,server_sockfd,&ev) == -1,"Wrong When Epoll Adding Server_fd");
    while(true){
        int ep_wait_ret = epoll_wait(epoll_fd,ep_events,MAX_EVENTS,-1);
        errIf(ep_wait_ret==-1,"Epoll Waiting Wrong!\n");
        for(int i=0;i<ep_wait_ret;i++){
            if(ep_events[i].data.fd == server_sockfd){
                int new_cli_fd = accept(server_sockfd,(sockaddr*)&client_addr,&client_addr_len);
                errIf(new_cli_fd==-1,"client_socketfd accept error");
                ev.events = EPOLLIN;
                ev.data.fd = new_cli_fd;
                errIf(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,new_cli_fd,&ev)==-1,"Adding New Client's fd Wrong!\n");
                //print result
                printf("Client %d received! IP: %s , Port: %d\n",new_cli_fd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            }else{
                /*Msg from Connected Client*/
                echo_client(ep_events[i].data.fd,read_buf,epoll_fd);
            }
        }

    }

    return 0;
}