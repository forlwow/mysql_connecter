#ifndef __OTHER_H_
#define __OTHER_H_
#include <string>
#include <iostream>
#include <stdio.h>

template <typename T>
inline FILE* print(FILE* os, const T &t)
{
    fprintf(os, "%s", t);
    return os;
}

template <typename T, typename... Args>
inline FILE* print(FILE* os, const T &t, const Args &...rest)
{
    fprintf(os, "%s", t);
    return print(os, rest...);
}

template <typename T>
inline std::ostream& print(std::ostream& os, const T &t)
{
    return os << t << std::endl;
}

template <typename T, typename... Args>
inline std::ostream& print(std::ostream& os, const T &t, const Args &...rest)
{
    os << t;
    return print(os, rest...);
}

inline void print(const std::string &msg)
{
    std::cout << msg << std::endl;
}

inline void print(const char *msg)
{
    std::cout << msg << std::endl;
}

#endif