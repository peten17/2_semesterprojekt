#include <iostream>
#include <wiringPi.h>
#include <server.h>
#include <opcuavariable.h>
#include <pthread.h>

#define NUMTHREADS 5
using namespace std;

UA_Boolean running = true;
bool t = true;
UA_StatusCode retval;

void stopHandler(int sig)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Received ctrl-c");
    running = false;
    t = false;
}

char openClose[1024] = "Open";
char aog[1024] = "Amount Of Grips";
char aogBrowse[1024] = "Grips";
char deviceNameString[1024] = "UR5 (Universal Robot 5)";
char manufactorerNameString[1024] = "Dream Team";
char manufactorerNameChar[1024] = "Manufactorer Name";
char dutyCycleString[1024] = "Duty Cycle";
char forceString[1024] = "Force";
char local[1024] = "en-US";

UA_Boolean openCloseBool = true;
UA_Double gripsAmount = 0;
UA_Double dutyCycle = 0;
UA_Int16 force = 0;

struct thread_data
{
  UA_Server *server;
};

static void defineOPCUAServer(void *threadarg)
{
    struct thread_data *myData;
    myData = (struct thread_data *) threadarg;

    UA_NodeId robotId;
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
    UA_Variant_setScalar(&gripsAAttr.value, &gripsAmount, &UA_TYPES[UA_TYPES_DOUBLE]);
    gripsAAttr.displayName = UA_LOCALIZEDTEXT(local, aog);
    UA_Server_addVariableNode(myData->server, UA_NODEID_NULL, robotId,
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

    defineOPCUAServer(myData->server);
    retval = UA_Server_run(myData->server, &running);

    //retval = UA_Server_run_iterate(myData->server, &running);
}

int main(int *arg)
{
    signal(2, stopHandler);

    pthread_t threads;
    struct thread_data td;
    int i = 0, rc;

    UA_ServerConfig *config = UA_ServerConfig_new_default();
    cout << "Opc UA server running" << endl;
    UA_Server *server = UA_Server_new(config);
    cout << "Opc UA server running" << endl;

    rc = pthread_create(&threads, NULL, defineOPCUAServer(server), (void *)td);

    if(rc)
    {
        cout << "Unable to create thread, " << i << endl;
    }
    else
    {
        cout << "Currently multithreading - continueing" << endl;
    }

    int range = 100;
    wiringPiSetupGpio();
    pinMode(18, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(range);
    pwmSetClock(24);

    Server c;
    c.serverBind();

    cout << "TCP Server binded" << endl;

    //UA_Server_run_startup(server);
    do
    {

        cout << "Currently lisetning..." << endl;
        string inputPoly(c.serverListen());
        if(inputPoly == "Open")
        {
            cout << "Received open node" << endl;
            pwmWrite(18, 50);
            delay(2000);

            openCloseBool = true;
            dutyCycle = 50;

            inputPoly = "";
        }

        else
        {
            cout << "Received close node" << endl;
            pwmWrite(18, 0);
            delay(2000);

            openCloseBool = false;
            gripsAmount++;
            /*int pos = inputPoly.find(';'); //stream
            force = atoi(inputPoly.substr(pos, 2));*/
            dutyCycle = 0;

            inputPoly = "";
        }


    }while(t == true);
/*
    while(t == true)
    {

    }
*/
    //UA_Server_run_shutdown(server);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
    pthread_exit(NULL);
    return retval;
}
