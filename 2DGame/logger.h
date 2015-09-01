#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <pthread.h>
#include <iostream>
#include <sstream>

extern pthread_mutex_t coutMutex;
struct Logger
{
    std::stringstream buffer;
    //Function for general types
    template <typename T>
    Logger& operator<<(const T& val)
    {
        //Push input to stringstream
        buffer << val;
        return *this;
    }

    //Function for special stream types, eg endl
    Logger& operator<<(std::ostream& (*val)(std::ostream &))
    {
        buffer << val;
        return *this;
    }

    //Print entire string buffer at end of << chain
    //when logger object is destroyed
    ~Logger()
    {
        //Mutex cout to prevent interleaving of output
        pthread_mutex_lock(&coutMutex);
        std::cout << buffer.str();
        pthread_mutex_unlock(&coutMutex);
    }
};

#endif // LOGGER_H_INCLUDED
