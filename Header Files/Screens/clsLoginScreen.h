/*
    Login screen
*/
#pragma once
#include <iostream>
#include "../Core/clsUser.h"
#include "../global.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "../Lib/clsLoggerRegister.h"
#include "../Lib/clsInputValidate.h"
#include "../Lib/clsUtil.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
    // Implementation to login the user into the system.
    static bool _login()
    {
        string username, password;
        bool loginFailed = false;
        short loginAttempt = 3;

        do
        {
            if (loginFailed)
            {
                cout << "\nInvalid username or password\n";
                cout << "You have " << --loginAttempt << " attempt(s) to login.\n\n";
            };
            if (loginAttempt == 0)
            {
                cout << "\nYou're locked from using the system after 3 failed login attempts." << endl;
                return false;
            }

            username = clsInputValidate::readString("Enter username: ");
            password = clsInputValidate::readString("Enter password: ");

            // get the user in file record if it's exists.
            // fill the global system variable "currentUser"
            // if a user is found with a matching credentials to login the user
            currentUser = clsUser::find(username, password);
            loginFailed = currentUser.isInvalidUser();

        } while (loginFailed);

        // at this point, the user has a valid credentials and have logged in
        clsLoggerRegister::logLogin(currentUser.username, currentUser.password, currentUser.permissions); // register a login
        clsMainScreen::showMainMenu();
        return true;
    };

public:
    static bool showLoginScreen()
    {
        clsUtil::clearConsoleScreen();
        _drawScreenHeader("\t\tBank System", "\t\tLogin screen");
        return _login();
    };
};