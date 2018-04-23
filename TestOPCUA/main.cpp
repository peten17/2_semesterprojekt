#include <opcuavariable.h>


using namespace std;

char descrip[1024] = "Test variable";
char vers[1024] = "test";
UA_Int32 myInteger = 43;
UA_Boolean myInteger2 = true;
UA_Variant myVar;

UA_Boolean running = true;
void stopHandler(int sig)
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

    opcUAVariable uaIntGrips(descrip, vers, 1);
    uaIntGrips.addVariable32Int(server, 42);
    uaIntGrips.writeVariable(server, 42);
    uaIntGrips.writeWrongVariable(server, 1);

    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
    return retval;
}
