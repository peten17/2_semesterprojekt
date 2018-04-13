#include <wiringPi.h>
#include <server.h>
#include <open62541.h>
#include <iostream>

using namespace std;

int main()
{
    UA_Int16 hest;
    hest = 15;
    cout << hest << endl;

    int input = 0, inputMenu = 0;
    string *buf;
    double buf;

    wiringPiSetupGpio();
    pinMode(18, PWM_OUTPUT);
    pwmSetMode (PWM_MODE_MS);
    pwmSetRange (2000);
    pwmSetClock (192);

    if(wiringPiSetup() == -1)
    {
        cout << "Wiring Pi setup has failed." << endl;
        cout << strerror(errno);

    }

    do
    {
        input = 0;
        cout << "___________________________" << endl
             << "   Modes:                  " << endl
             << "       1. Manual           " << endl
             << "       2. Server Controlled" << endl
             << "       3. Close Application" << endl
             << "___________________________" << endl
             << "Enter input: ";
        cin >> inputMenu;

        if(inputMenu == 1)
        {
            while(input != 2001)
            {
                cout << "Waiting for new input: " << endl;
                cin >> input;
                buf = input;
                if(input > 2000 && input != 2001)
                {
                    cout << "Invalid input. Duty cycle set to maximum.";
                    pwmWrite(18, 2000);
                    cout << "Current duty cycle: " << "100" << "%" << endl;
                }
                else if(input < 0)
                {
                    cout << "Invalid input. Duty cycle set to minimum.";
                    pwmWrite(18, 0);
                    cout << "Current duty cycle: " << "0" << "%" << endl;
                }
                else if(input == 2001)
                {
                    break;
                }
                else
                {
                    cout << "Current duty cycle: " << (buf/2000)*100 << "%" << endl;

                    pwmWrite(18, input);
                    delay(2000);
                }

            }
        }
        else if(inputMenu == 2)
        {
            Server c;
            c.serverBind();
            do
            {
                string inputPoly(c.serverListen());
                buf = inputPoly;
                if(inputPoly == "Open")
                {
                    pwmWrite(18, 200);
                    delay(2000);
                    pwmWrite(18, 150);
                    inputPoly = "";
                }
                else if(inputPoly == "Close")
                {
                    pwmWrite(18, 100);
                    delay(2000);
                    pwmWrite(18, 150);
                    inputPoly = "";
                }
                else if(inputPoly == "Stop")
                {
                    cout << "The program has finished." << endl;
                    pwmWrite(18, 150);
                    break;
                }
                else
                {
                    break;
                }
            }while(buf != "Stop");
        }
    }
    while(input != 3);

    return 0;
}
