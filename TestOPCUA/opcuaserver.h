#ifndef OPCUASERVER_H
#define OPCUASERVER_H
#include "open62541.h"
#include <signal.h>

class opcUAServer
{
public:

    opcUAServer();


    static void stopHandler(int sig);
    UA_Boolean _running;
    void setRunningFalse();

private:


};

#endif // OPCUASERVER_H
