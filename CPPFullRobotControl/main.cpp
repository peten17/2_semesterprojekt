#include <iostream>
#include <wiringPi.h>
#include <pthread.h>
#include <server.h>
#include <opcuavariable.cpp>
#include <signal.h>

using namespace std;

//Stophandler which listens for ctrl-c command and turns off the boolean variables t and running.
void stopHandler(int sig)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Received ctrl-c");
    t = false;
    running = false;
}

//Makes the defineOPCUAServer callable from this file.
static void *defineOPCUAServer(void *threadarg);

int main()
{
    //Actiavtes the stophandler.
    signal(2, stopHandler);

    //Configuring the multithreading
    pthread_t threads;
    struct thread_data td;
    int i = 0, rc;

    //Configuring the OPC UA server
    UA_ServerConfig *config = UA_ServerConfig_new_default();
    cout << "Opc UA server running" << endl;
    td.server = UA_Server_new(config);
    cout << "Opc UA server configured" << endl;

    //Starts the server on a seperate thread than the rest of the main file.
    rc = pthread_create(&threads, NULL, defineOPCUAServer, (void *) &td);

    //Checks whether or not the startup of the OPC UA server is succesfull.
    if(rc)
    {
        cout << "Unable to create thread" << i << endl;
    }
    else
    {
        cout << "Currently multithreading - continuing" << endl;
    }

    //Innitializing the wiringPi library, while setting the pwmClock and pwmRange. Starts the gripper closed.
    int range = 10;
    wiringPiSetupGpio();
    pinMode(18, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(range);
    pwmSetClock(1920);
    pwmWrite(18, 10);

    //Makes a new server object with the no-arg constructor. Binds the server.
    Server c;
    c.serverBind();
    cout << "TCP Server binded" << endl;

    do
    {
        //Waits for the server to receive a message.
        cout << "Currently listening..." << endl;
        string inputPoly(c.serverListen());
        string bufString = inputPoly.substr(0, 1);

        //If the message is 1:
        if(bufString == "1")
        {
            cout << "Received open node." << endl;
            //pwmWrite open command.
            pwmWrite(18, 10);

            //Updating the variables for OPC UA
            openCloseBool = true;
            dutyCycle = (2/range * 100);

            //Updates the bufString so it will wait for a new message and updates the values for the OPCUA server.
            bufString = "2";
            addValueCallbackDuty(td.server);
            addValueCallbackGrips(td.server);
            addValueCallbackOpenClose(td.server);
        }
        //If the message is 0:
        else if(bufString == "0")
        {
            cout << "Received close node." << endl;
            pwmWrite(18, 2);

            openCloseBool = false;
            gripsAmount++;
            dutyCycle = (10/range * 100);

            bufString = "2";
            addValueCallbackDuty(td.server);
            addValueCallbackGrips(td.server);
            addValueCallbackOpenClose(td.server);
        }


    }while(t == true);
    //Deletes the OPC UA server and stops the multithreading.
    UA_Server_delete(td.server);
    UA_ServerConfig_delete(config);
    pthread_exit(NULL);
    return retval;
}
