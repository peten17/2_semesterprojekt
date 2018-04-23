#include "opcuavariable.h"

opcUAVariable::opcUAVariable()
{

}

opcUAVariable::opcUAVariable(char* varName, char* vers, int index)
{
    variableName = varName;
    version = vers;
    nsIndex = index;

}

void opcUAVariable::addVariable32Int(UA_Server *server, UA_Int32 uaInt)
{
    UA_VariableAttributes attr = UA_VariableAttributes_default;

    UA_Variant_setScalar(&attr.value, &uaInt, &UA_TYPES[UA_TYPES_INT32]);

    attr.description = UA_LOCALIZEDTEXT(local, variableName);
    attr.displayName = UA_LOCALIZEDTEXT(local, variableName);
    attr.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(nsIndex, variableName);
    UA_QualifiedName myIntegerName = UA_QUALIFIEDNAME(nsIndex, variableName);
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC((nsIndex - 1), UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC((nsIndex - 1), UA_NS0ID_ORGANIZES);

    UA_Server_addVariableNode(server, myIntegerNodeId, parentNodeId, parentReferenceNodeId,
                              myIntegerName, UA_NODEID_NUMERIC((nsIndex - 1), UA_NS0ID_BASEDATAVARIABLETYPE),
                              attr, NULL, NULL);
}

void opcUAVariable::writeVariable(UA_Server *server, UA_Int32 uaInt)
{
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(nsIndex, variableName);
    /* Write a different integer value */
    UA_Variant_init(&myVar);
    UA_Variant_setScalar(&myVar, &uaInt, &UA_TYPES[UA_TYPES_INT32]);
    UA_Server_writeValue(server, myIntegerNodeId, myVar);

    UA_WriteValue wv;
    UA_WriteValue_init(&wv);
    wv.nodeId = myIntegerNodeId;
    wv.attributeId = /*UA_ATTRIBUTEID_VALUE*/ nsIndex;
    wv.value.status = UA_STATUSCODE_BADNOTCONNECTED;
    wv.value.hasStatus = true; UA_Server_write(server, &wv);

    wv.value.hasStatus = false;
    wv.value.value = myVar;
    wv.value.hasValue = true;
    UA_Server_write(server, &wv);
}

void opcUAVariable::writeWrongVariable(UA_Server *server)
{
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(nsIndex, variableName);
    /* Write a string */
    UA_String myString = UA_STRING(version);
    UA_Variant_init(&myVar);
    UA_Variant_setScalar(&myVar, &myString, &UA_TYPES[UA_TYPES_STRING]);
    UA_StatusCode retval = UA_Server_writeValue(server, myIntegerNodeId, myVar);
    std::cout << ("Writing a string returned statuscode \n", UA_StatusCode_name(retval));
}
