#include <iostream>
#include <wiringPi.h>
#include <pthread.h>
#include <server.h>
#include <opcuavariable.cpp>
#include <signal.h>

using namespace std;

void stopHandler(int sig)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Received ctrl-c");
    t = false;
    running = false;

}

static void *defineOPCUAServer(void *threadarg);

int main()
{
    signal(2, stopHandler);

    pthread_t threads;
    struct thread_data td;
    int i = 0, rc;

    UA_ServerConfig *config = UA_ServerConfig_new_default();
    cout << "Opc UA server running" << endl;
    td.server = UA_Server_new(config);
    cout << "Opc UA server configured" << endl;

    rc = pthread_create(&threads, NULL, defineOPCUAServer, (void *) &td);

    if(rc)
    {
        cout << "Unable to create thread" << i << endl;
    }
    else
    {
        cout << "Currently multithreading - continuing" << endl;
    }

    int range = 10;
    wiringPiSetupGpio();
    pinMode(18, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(range);
    pwmSetClock(1920);

    Server c;
    c.serverBind();
    cout << "TCP Server binded" << endl;

    do
    {
        cout << "Currently listening..." << endl;
        string inputPoly(c.serverListen());
        char* bufString[16] = inputPoly.substr(0, 1);
        int openCloseVal = atoi(bufString);
        /*bufString = inputPoly.substr(1, 3);
        char* forceVal[1024] = bufString;*/

        if(openCloseVal == 1)
        {
            cout << "Received open node." << endl;
            pwmWrite(18, 2);

            openCloseBool = true;
            dutyCycle = (2/range * 100);
            //force = atoi(forceVal);

            //forceVal = " ";
            openCloseVal = 2;

        }
        else if(openCloseVal == 0)
        {
            cout << "Received close node." << endl;
            pwmWrite(18, 10);

            openCloseBool = false;
            gripsAmount++;
            dutyCycle = (10/range * 100);
            //force = atoi(forceVal);

            //forceVal = " ";
            openCloseVal = 2;
        }


    }while(t == true);

    UA_Server_delete(td.server);
    UA_ServerConfig_delete(config);
    pthread_exit(NULL);
    return retval;
}
