#include <opcuavariable.h>

using namespace std;

char descrip[1024] = "Device type";
char descrip1[1024] = "Manufacturer name";
char descrip2[1024] = "Model name";
char descrip3[1024] = "Pump type";
char descrip4[1024] = "Status";
char descrip5[1024] = "MotorRPM";
char descrip6[1024] = "MotorRPMS";


char local[1024] = "en-US";
char pump5[1024] = "pump1";
char pump2[1024] = "pump2";
char pump3[1024] = "pump3";
char pump4[1024] = "pump4";

UA_Boolean running = true;
void stopHandler(int sig)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Received ctrl-c");
    running = false;
}

UA_NodeId pumpTypeId = {1, UA_NODEIDTYPE_NUMERIC, {1001}};

void defineObjectTypes(UA_Server *server)
{
    UA_NodeId deviceTypeId;
    UA_ObjectTypeAttributes dtAttr = UA_ObjectTypeAttributes_default;
    dtAttr.displayName = UA_LOCALIZEDTEXT(local, descrip);
    UA_Server_addObjectTypeNode(server, UA_NODEID_NULL,
                                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                                UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(1, descrip), dtAttr,
                                NULL, &deviceTypeId);
    UA_VariableAttributes mnAttr = UA_VariableAttributes_default;
    mnAttr.displayName = UA_LOCALIZEDTEXT(local, descrip1);
    UA_NodeId manufacturerNameId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, deviceTypeId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, descrip1),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                              mnAttr, NULL, &manufacturerNameId);
    /* Make the manufacturer name mandatory */
    UA_Server_addReference(server, manufacturerNameId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);

    UA_VariableAttributes modelAttr = UA_VariableAttributes_default; modelAttr.displayName = UA_LOCALIZEDTEXT(local, descrip2);
    UA_Server_addVariableNode(server, UA_NODEID_NULL, deviceTypeId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, descrip2),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                              modelAttr, NULL, NULL);
    /* Define the object type for "Pump" */
    UA_ObjectTypeAttributes ptAttr = UA_ObjectTypeAttributes_default; ptAttr.displayName = UA_LOCALIZEDTEXT(local, descrip3);
    UA_Server_addObjectTypeNode(server, pumpTypeId, deviceTypeId,
                                UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(1, descrip3), ptAttr, NULL, NULL);

    UA_VariableAttributes statusAttr = UA_VariableAttributes_default;
    statusAttr.displayName = UA_LOCALIZEDTEXT(local, descrip4);
    statusAttr.valueRank = -1; UA_NodeId statusId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, pumpTypeId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, descrip4),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                              statusAttr, NULL, &statusId);
    /* Make the status variable mandatory */
    UA_Server_addReference(server, statusId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);

    UA_VariableAttributes rpmAttr = UA_VariableAttributes_default;
    rpmAttr.displayName = UA_LOCALIZEDTEXT(local, descrip5);
    rpmAttr.valueRank = -1;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, pumpTypeId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, descrip6),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                              rpmAttr, NULL, NULL);
}

static void addPumpObjectInstance(UA_Server *server, char *name)
{
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT(local, name);
    UA_Server_addObjectNode(server, UA_NODEID_NULL, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES), UA_QUALIFIEDNAME(1, name),
                            pumpTypeId,
                            /* this refers to the object type identifier */ oAttr, NULL, NULL);
}

char pump251[1024] = "New pump created";
static UA_StatusCode pumpTypeConstructor(UA_Server *server, const UA_NodeId *sessionId,
                                         void *sessionContext, const UA_NodeId *typeId,
                                         void *typeContext, const UA_NodeId *nodeId, void **nodeContext)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, pump251);

    /* Find the NodeId of the status child variable */
    UA_RelativePathElement rpe;
    UA_RelativePathElement_init(&rpe);
    rpe.referenceTypeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT);
    rpe.isInverse = false;
    rpe.includeSubtypes = false;
    rpe.targetName = UA_QUALIFIEDNAME(1, descrip4);

    UA_BrowsePath bp;
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;

    UA_BrowsePathResult bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD || bpr.targetsSize < 1) return bpr.statusCode;

    /* Set the status value */
    UA_Boolean status = true; UA_Variant value;
    UA_Variant_setScalar(&value, &status, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, value);
    UA_BrowsePathResult_deleteMembers(&bpr);

    /* At this point we could replace the node context .. */
    return UA_STATUSCODE_GOOD;
}
static void addPumpTypeConstructor(UA_Server *server)
{
    UA_NodeTypeLifecycle lifecycle;
    lifecycle.constructor = pumpTypeConstructor;
    lifecycle.destructor = NULL;
    UA_Server_setNodeTypeLifecycle(server, pumpTypeId, lifecycle);
}

int main(void)
{

    signal(2, stopHandler);
    signal(2, stopHandler);

    UA_ServerConfig *config = UA_ServerConfig_new_default();
    UA_Server *server = UA_Server_new(config);
/*
    opcUAVariable uaIntGrips(descrip, vers, 1);
    opcUAVariable uaIntGrips1(descrip1, vers1, 3);
    uaIntGrips.addVariable32Int(server, 42);
    uaIntGrips.writeVariable(server, 42);
    uaIntGrips.writeWrongVariable(server);

    uaIntGrips1.addVariable32Int(server, 50);
    uaIntGrips1.writeVariable(server, 50);
    uaIntGrips1.writeWrongVariable(server);
*/
    manuallyDefinePump(server);
    defineObjectTypes(server);
    addPumpObjectInstance(server, pump2);
    addPumpObjectInstance(server, pump3);
    addPumpTypeConstructor(server);
    addPumpObjectInstance(server, pump4);
    addPumpObjectInstance(server, pump5);

    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
    return retval;
}
