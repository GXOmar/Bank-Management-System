/*
    -*- Bank System — C++ Console application -*-
*/
#include <iostream>
#include "../Header Files/Screens/clsLoginScreen.h"
#include "../Header Files/global.h"

using namespace std;

int main()
{
    while (true)
    {
        if (!clsLoginScreen::showLoginScreen())
        {
            break;
        }
    };

    return 0;
}