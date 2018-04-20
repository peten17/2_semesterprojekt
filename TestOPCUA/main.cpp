#include <iostream>
#include <signal.h>
#include <open62541.h>

using namespace std;

UA_Boolean running = true;
static void stopHandler(int sig)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Received ctrl-c");
    running = false;
}

int main()
{

    signal(2, stopHandler);
    signal(2, stopHandler);

    UA_ServerConfig *config = UA_ServerConfig_new_default();
    UA_Server *server = UA_Server_new(config);

    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
    return retval;
}
