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

    static void addVariable32Int(UA_Server *server, UA_Int32 uaInt);
    static void writeVariable(UA_Server *server, UA_Int32 uaInt);
    static void writeWrongVariable(UA_Server *server);

private:
    static char local[1024] = "en-US", *variableName, *version;
    static UA_Variant myVar;
    static int nsIndex;
};

#endif // OPCUAVARIABLE_H
