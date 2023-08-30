/**
  ******************************************************************************
  * @file           : util.h
  * @author         : Matchalatter
  * @brief          : None
  * @attention      : None
  * @date           : 2023/8/29
  ******************************************************************************
  */

#ifndef MSERVER_UTIL_H
#define MSERVER_UTIL_H

#define BUFSIZE 1024
#define MAX_EVENTS 100
#define SERVER_IPADDR "127.0.0.1"
#define SERVER_PORT 8088

void errIf(bool condition, const char* msg);
#endif //MSERVER_UTIL_H
