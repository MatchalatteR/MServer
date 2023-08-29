/**
  ******************************************************************************
  * @file           : util.cpp
  * @author         : Matchalatter
  * @brief          : None
  * @attention      : None
  * @date           : 2023/8/29
  ******************************************************************************
  */
#include <iostream>
#include <cstring>
#include "../include/util.h"
void errIf(bool condition, const char* msg){
    if(condition){
        perror(msg);
        exit(EXIT_FAILURE);
    }
}
