#include "logger.h"

//Mutex for cout
//Prevent interleaving of output
pthread_mutex_t coutMutex = PTHREAD_MUTEX_INITIALIZER;
