#include <opcuavariable.h>


using namespace std;

char descrip[1024] = "Test variable";
char vers[1024] = "test";
char descrip1[1024] = "Test variable1";
char vers1[1024] = "test1";

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
    opcUAVariable uaIntGrips1(descrip1, vers1, 3);
    uaIntGrips.addVariable32Int(server, 42);
    uaIntGrips.writeVariable(server, 42);
    uaIntGrips.writeWrongVariable(server);

    uaIntGrips1.addVariable32Int(server, 50);
    uaIntGrips1.writeVariable(server, 50);
    uaIntGrips1.writeWrongVariable(server);

    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
    return retval;
}
