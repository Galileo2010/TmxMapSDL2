#ifndef _CC_LOGGER_H_
#define _CC_LOGGER_H_

#include <iostream>

namespace cc
{
class Logger
{
private:
    Logger()
    {
    }
    ~Logger()
    {
    }

public:
    static void log(const char* msg)
    {
        std::cout << msg << std::endl;
    }

    static void error(const char* msg, const char* detail = NULL)
    {
        if(detail != NULL)
            std::cerr << msg << detail << std::endl;
        else
            std::cerr << msg << std::endl;
    }
};
};

#endif