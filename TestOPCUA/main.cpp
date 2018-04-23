#include <opcuavariable.h>

using namespace std;

UA_Boolean running = true;
void stopHandler(int sig)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Received ctrl-c");
    running = false;
}

char openClose[1024] = "Open";
char aog[1024] = "Amount Of Grips";
char aogBrowse[1024] = "Grips";
char deviceNameString[1024] = "UR5 (Universal Robot 5)";
char manufactorerNameString[1024] = "Dream Team";
char manufactorerNameChar[1024] = "Manufactorer Name";
char local[1024] = "en-US";

UA_Boolean openCloseBool = true;
UA_Double gripsAmount = 0;

static void defineOPCUAServer(UA_Server *server)
{
    UA_NodeId robotId;
    /* get the nodeid assigned by the server*/
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT(local, deviceNameString);
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, deviceNameString),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE), oAttr, NULL, &robotId);

    UA_VariableAttributes mnAttr = UA_VariableAttributes_default;
    UA_String manufacturerName = UA_STRING(manufactorerNameChar);
    UA_Variant_setScalar(&mnAttr.value, &manufacturerName, &UA_TYPES[UA_TYPES_STRING]);
    mnAttr.displayName = UA_LOCALIZEDTEXT(local, manufactorerNameString);
    UA_Server_addVariableNode(server, UA_NODEID_NULL, robotId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, manufactorerNameString),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                              mnAttr, NULL, NULL);

    UA_VariableAttributes openCloseAttr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&openCloseAttr.value, &openCloseBool, &UA_TYPES[UA_TYPES_BOOLEAN]);
    openCloseAttr.displayName = UA_LOCALIZEDTEXT(local, openClose);
    UA_Server_addVariableNode(server, UA_NODEID_NULL, robotId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, openClose),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                              openCloseAttr, NULL, NULL);

    UA_VariableAttributes gripsAAttr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&gripsAAttr.value, &gripsAmount, &UA_TYPES[UA_TYPES_DOUBLE]);
    gripsAAttr.displayName = UA_LOCALIZEDTEXT(local, aog);
    UA_Server_addVariableNode(server, UA_NODEID_NULL, robotId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, aogBrowse),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), gripsAAttr, NULL, NULL);
}

int main(void)
{

    signal(2, stopHandler);
    signal(2, stopHandler);

    UA_ServerConfig *config = UA_ServerConfig_new_default();
    UA_Server *server = UA_Server_new(config);

    defineOPCUAServer(server);
    /*char name[1024] = "Var1";
    char vers[1024] = "Var1-Vers";
    char name1[1024] = "Var12";
    char vers1[1024] = "Var12-Vers";

    opcUAVariable var(name, vers);
    var.addVariable32Int(server, 40);
    var.writeVariable(server, 40);
    var.writeWrongVariable(server);

    opcUAVariable var1(name1, vers1);
    var1.addVariable32Int(server, 44);
    var1.writeVariable(server, 44);
    var1.writeWrongVariable(server);*/

    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
    return retval;
}
