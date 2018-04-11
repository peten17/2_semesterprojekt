#include <iostream>
#include <wiringPi.h>
#include <server.h>

using namespace std;

int main()
{
    int input, inputMenu;
    double buf;

    wiringPiSetupGpio();
    pinMode(18, PWM_OUTPUT);
    pwmSetMode (PWM_MODE_MS);
    pwmSetRange (2000);
    pwmSetClock (192);

    if(wiringPiSetup() == -1)
    {
        cout << "Wiring Pi setup has failed." << endl;
        cout << stderr(errno);

    }

    cout << "____________________________" << endl
         << "   Modes:" << endl
         << "       1. Manual" << endl
         << "       2. Server Controlled" << endl
         << "____________________________" << endl
         << "Enter input: ";

    cin >> inputMenu;
    switch(inputMenu)
    {
    case 1:
    {
        while(input != 2001)
        {

            cout << "Waiting for new input: " << endl;
            cin >> input;
            buf = input;
            if(input > 2001 || input < 0)
            {
                cout << "Invalid input. Try again: ";
                cin >> input;
            }
            cout << "Current duty cycle: " << (buf/2000)*100 << "%" << endl;
            pwmWrite(18, input);
            delay(2000);
        }
    }
    case 2:
    {
        while()
        Server c;
        c.serverBind();
        string inputPoly(c.serverListen());

        if(inputPoly == "Open")
        {
            pwmWrite(18, 200);
            delay(2000);
            pwmWrite(18, 150);
        }
        else if(inputPoly == "Close")
        {
            pwmWrite(18, 100);
            delay(2000);
            pwmWrite(18, 150);
        }
        else
        {
            pwmWrite(18, 150);
        }
    }
    default:
        break;
    }

    return 0;
}
