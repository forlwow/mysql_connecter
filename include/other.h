#ifndef __OTHER_H_
#define __OTHER_H_
#include <string>
#include <iostream>

inline void print(const std::string &msg){
    std::cout << msg << std::endl;
}

inline void print(const char *msg){
    std::cout << msg << std::endl;
}

#endif