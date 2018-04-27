#include <open62541.h>

static bool t = true;

static char openClose[1024] = "Open";
static char aog[1024] = "Amount Of Grips";
static char aogBrowse[1024] = "Grips";
static char deviceNameString[1024] = "UR5 (Universal Robot 5)";
static char manufactorerNameString[1024] = "Dream Team";
static char manufactorerNameChar[1024] = "Manufactorer Name";
static char dutyCycleString[1024] = "Duty Cycle";
static char forceString[1024] = "Force";
static char local[1024] = "en-US";

static UA_StatusCode retval;
static UA_Boolean openCloseBool = true;
static UA_Int16 gripsAmount = 0;
static UA_Double dutyCycle = 0;
static UA_Int16 force = 0;
static UA_NodeId robotId;

static UA_Boolean running = true;
struct thread_data
{
    UA_Server *server;
};

static void *defineOPCUAServer(void *threadarg)
{
    struct thread_data *myData;
    myData = (struct thread_data *) threadarg;

    /* get the nodeid assigned by the server*/
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT(local, deviceNameString);
    UA_Server_addObjectNode(myData->server, UA_NODEID_NULL,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, deviceNameString),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE), oAttr, NULL, &robotId);

    UA_VariableAttributes mnAttr = UA_VariableAttributes_default;
    UA_String manufacturerName = UA_STRING(manufactorerNameString);
    UA_Variant_setScalar(&mnAttr.value, &manufacturerName, &UA_TYPES[UA_TYPES_STRING]);
    mnAttr.displayName = UA_LOCALIZEDTEXT(local, manufactorerNameChar);
    UA_Server_addVariableNode(myData->server, UA_NODEID_NULL, robotId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, manufactorerNameChar),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                              mnAttr, NULL, NULL);

    UA_VariableAttributes openCloseAttr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&openCloseAttr.value, &openCloseBool, &UA_TYPES[UA_TYPES_BOOLEAN]);
    openCloseAttr.displayName = UA_LOCALIZEDTEXT(local, openClose);
    UA_Server_addVariableNode(myData->server, UA_NODEID_NULL, robotId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, openClose),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                              openCloseAttr, NULL, NULL);

    UA_VariableAttributes gripsAAttr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&gripsAAttr.value, &gripsAmount, &UA_TYPES[UA_TYPES_INT16]);
    UA_NodeId gripsNodeId = UA_NODEID_STRING(1, aog);
    gripsAAttr.displayName = UA_LOCALIZEDTEXT(local, aog);
    gripsAAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_Server_addVariableNode(myData->server, gripsNodeId, robotId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, aogBrowse),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), gripsAAttr, NULL, NULL);

    UA_VariableAttributes cycleAttr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&cycleAttr.value, &dutyCycle, &UA_TYPES[UA_TYPES_DOUBLE]);
    cycleAttr.displayName = UA_LOCALIZEDTEXT(local, dutyCycleString);
    UA_Server_addVariableNode(myData->server, UA_NODEID_NULL, robotId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, dutyCycleString),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), cycleAttr, NULL, NULL);

    UA_VariableAttributes forceAttr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&forceAttr.value, &force, &UA_TYPES[UA_TYPES_INT16]);
    forceAttr.displayName = UA_LOCALIZEDTEXT(local, forceString);
    UA_Server_addVariableNode(myData->server, UA_NODEID_NULL, robotId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, forceString),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), forceAttr, NULL, NULL);

    retval = UA_Server_run(myData->server, &running);
}

static void updateGrips(UA_Server *server)
{
    UA_NodeId gripsNodeId = UA_NODEID_STRING(1, aog);
    UA_Variant value;
    UA_VariableAttributes gripsAAttr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&gripsAAttr.value, &gripsAmount, &UA_TYPES[UA_TYPES_INT16]);
    //UA_Variant_setScalar(&value, &gripsNodeId, &UA_TYPES[UA_TYPES_INT16]);
    UA_Server_writeValue(server, gripsNodeId, value);

}
