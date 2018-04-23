#include <opcuavariable.h>

using namespace std;

UA_Boolean running = true;
void stopHandler(int sig)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Received ctrl-c");
    running = false;
}

char descrip[1024] = "Device type";
char descrip1[1024] = "Manufacturer name";
char descrip2[1024] = "Model name";
char descrip3[1024] = "Pump type";
char openClose[1024] = "Open";
char amountOfGrips[1024] = "Amount Of Grips";
char amountOfGrips2[1024] = "Grips";
char deviceNameString[1024] = "UR5 (Universal Robot 5)";
char manufactorerNameString[1024] = "Dream Team";
char manufactorerNameChar[1024] = "DreamTeam";
char local[1024] = "en-US";
char descrip10[1024] = "Mega pump 3000";
char descrip11[1024] = "ModelName";

static void manuallyDefinePump(UA_Server *server)
{
    UA_NodeId pumpId;
    /* get the nodeid assigned by the server */
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT(local, deviceNameString);

    UA_Server_addObjectNode(server, UA_NODEID_NULL, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, deviceNameString),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE), oAttr, NULL, &pumpId);

    UA_VariableAttributes mnAttr = UA_VariableAttributes_default;
    UA_String manufacturerName = UA_STRING(manufactorerNameString);
    UA_Variant_setScalar(&mnAttr.value, &manufacturerName, &UA_TYPES[UA_TYPES_STRING]);
    mnAttr.displayName = UA_LOCALIZEDTEXT(local, manufactorerNameChar);
    UA_Server_addVariableNode(server, UA_NODEID_NULL, pumpId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, manufactorerNameChar), UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                              mnAttr, NULL, NULL);
/*
    UA_VariableAttributes modelAttr = UA_VariableAttributes_default;
    UA_String modelName = UA_STRING(descrip10);
    UA_Variant_setScalar(&modelAttr.value, &modelName, &UA_TYPES[UA_TYPES_STRING]);
    modelAttr.displayName = UA_LOCALIZEDTEXT(local, descrip11);
    UA_Server_addVariableNode(server, UA_NODEID_NULL, pumpId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, descrip11), UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                              modelAttr, NULL, NULL);
*/
    UA_VariableAttributes statusAttr = UA_VariableAttributes_default;
    UA_Boolean status = true;
    UA_Variant_setScalar(&statusAttr.value, &status, &UA_TYPES[UA_TYPES_BOOLEAN]);
    statusAttr.displayName = UA_LOCALIZEDTEXT(local, openClose);
    UA_Server_addVariableNode(server, UA_NODEID_NULL, pumpId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, openClose), UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                              statusAttr, NULL, NULL);

    UA_VariableAttributes rpmAttr = UA_VariableAttributes_default;
    UA_Double rpm = 50.0; UA_Variant_setScalar(&rpmAttr.value, &rpm, &UA_TYPES[UA_TYPES_DOUBLE]);
    rpmAttr.displayName = UA_LOCALIZEDTEXT(local, amountOfGrips);
    UA_Server_addVariableNode(server, UA_NODEID_NULL, pumpId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, amountOfGrips2),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), rpmAttr, NULL, NULL);
}

int main(void)
{

    signal(2, stopHandler);
    signal(2, stopHandler);

    UA_ServerConfig *config = UA_ServerConfig_new_default();
    UA_Server *server = UA_Server_new(config);

    manuallyDefinePump(server);


    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
    return retval;
}
