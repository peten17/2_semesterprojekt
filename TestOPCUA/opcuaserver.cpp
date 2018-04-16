#include "opcuaserver.h"

opcUAServer::opcUAServer()
{
    _running = true;
}
void opcUAServer::setRunningFalse()
{
    _running = false;
}
void opcUAServer::stopHandler(int sig)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    setRunningFalse();
}
