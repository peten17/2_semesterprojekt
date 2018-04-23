#ifndef OPCUAVARIABLE_H
#define OPCUAVARIABLE_H

#include <iostream>
#include <signal.h>
#include <open62541.h>
#include <stdio.h>

class opcUAVariable
{
public:
    opcUAVariable();
    opcUAVariable(char *varName, char *vers, int index);

    void addVariable32Int(UA_Server *server, UA_Int32 uaInt);
    void writeVariable(UA_Server *server, UA_Int32 uaInt);
    void writeWrongVariable(UA_Server *server);

private:
    char local[1024] = "en-US", *variableName, *version;
    UA_Variant myVar;
    int nsIndex;
};

#endif // OPCUAVARIABLE_H
