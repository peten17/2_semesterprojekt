#include <iostream>
#include <signal.h>
#include <open62541.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

using namespace std;

char string1[1024] = "en-US";
char string2[1024] = "Din far er din mor";
char string3[1024] = "test";
UA_Int32 myInteger = 43;
UA_Variant myVar;

UA_Boolean running = true;
void stopHandler(int sig)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Received ctrl-c");
    running = false;
}

void addVariable(UA_Server *server)
{
    UA_VariableAttributes attr = UA_VariableAttributes_default;

    UA_Variant_setScalar(&attr.value, &myInteger, &UA_TYPES[UA_TYPES_INT32]);

    attr.description = UA_LOCALIZEDTEXT(string1, string2);
    attr.displayName = UA_LOCALIZEDTEXT(string1, string2);
    attr.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, string2);
    UA_QualifiedName myIntegerName = UA_QUALIFIEDNAME(1, string2);
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_Server_addVariableNode(server, myIntegerNodeId, parentNodeId, parentReferenceNodeId,
                              myIntegerName, UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                              attr, NULL, NULL);
}

void writeVariable(UA_Server *server)
{
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, string2);
    /* Write a different integer value */
    UA_Variant_init(&myVar);
    UA_Variant_setScalar(&myVar, &myInteger, &UA_TYPES[UA_TYPES_INT32]);
    UA_Server_writeValue(server, myIntegerNodeId, myVar);

    UA_WriteValue wv;
    UA_WriteValue_init(&wv);
    wv.nodeId = myIntegerNodeId;
    wv.attributeId = UA_ATTRIBUTEID_VALUE;
    wv.value.status = UA_STATUSCODE_BADNOTCONNECTED;
    wv.value.hasStatus = true; UA_Server_write(server, &wv);

    wv.value.hasStatus = false;
    wv.value.value = myVar;
    wv.value.hasValue = true;
    UA_Server_write(server, &wv);
}

void writeWrongVariable(UA_Server *server)
{
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, string2);
    /* Write a string */
    UA_String myString = UA_STRING(string3);
    UA_Variant_init(&myVar);
    UA_Variant_setScalar(&myVar, &myString, &UA_TYPES[UA_TYPES_STRING]);
    UA_StatusCode retval = UA_Server_writeValue(server, myIntegerNodeId, myVar);
    cout << ("Writing a string returned statuscode \n", UA_StatusCode_name(retval));
}

int main()
{

    signal(2, stopHandler);
    signal(2, stopHandler);

    UA_ServerConfig *config = UA_ServerConfig_new_default();
    UA_Server *server = UA_Server_new(config);

    addVariable(server);
    writeVariable(server);
    writeWrongVariable(server);

    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
    return retval;
}
