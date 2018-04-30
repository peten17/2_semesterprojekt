#include <iostream>
#include <wiringPi.h>
#include <pthread.h>
#include <server.h>
#include <opcuavariable.cpp>
#include <signal.h>


#define NUMTHREADS 5
using namespace std;

void stopHandler(int sig)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Received ctrl-c");
    running = false;
    t = false;
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

    do
    {

        cout << "Currently lisetning..." << endl;
        string inputPoly(c.serverListen());
        if(inputPoly == "Open")
        {
            cout << "Received open node." << endl;
            pwmWrite(18, 50);
            delay(2000);

            openCloseBool = true;
            dutyCycle = 50;

            addValueCallbackOpenClose(td.server);
            addValueCallbackDuty(td.server);

            inputPoly = "";
        }

        else
        {
            cout << "Received close node." << endl;
            pwmWrite(18, 0);
            delay(2000);

            openCloseBool = false;
            gripsAmount++;
            /*int pos = inputPoly.find(';'); //stream
            force = atoi(inputPoly.substr(pos, 2));*/
            dutyCycle = 100;

            addValueCallbackGrips(td.server);
            addValueCallbackForce(td.server);
            addValueCallbackOpenClose(td.server);
            addValueCallbackDuty(td.server);

            inputPoly = "";
        }


    }while(t == true);

    UA_Server_delete(td.server);
    UA_ServerConfig_delete(config);
    pthread_exit(NULL);
    return retval;
}
