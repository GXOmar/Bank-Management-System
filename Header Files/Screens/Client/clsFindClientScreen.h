/*
    UI - Find clinet screen
*/
#pragma once
#include <iostream>
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"
#include "../clsScreen.h"
#include "../../Lib/clsUtil.h"

using namespace std;

class clsFindClientScreen : protected clsScreen
{
private:
    static void _printClient(clsBankClient client)
    {
        cout << "\nClient Info\n";
        cout << "-------------------------------\n";
        cout << "First name: " << client.firstName << '\n';
        cout << "Last name: " << client.lastName << '\n';
        cout << "Full Name: " << client.fullName() << '\n';
        cout << "Email: " << client.email << '\n';
        cout << "Phone number: " << client.phoneNumber << '\n';
        cout << "Account number: " << client.accountNumber << '\n';
        cout << "PIN code: " << client.pinCode << '\n';
        cout << "Balance: " << client.balance << '\n';
        cout << "-------------------------------\n";
    };

    static void _findClientProccess()
    {
        string accountNumber = clsInputValidate::readString("Please enter an account number: ");
        while (!clsBankClient::isClientExists(accountNumber))
        {
            accountNumber = clsInputValidate::readString("Account number not found, enter a different one: ");
        }

        clsBankClient client = clsBankClient::find(accountNumber);
        _printClient(client);
    };

public:
    static void showFindClientScreen()
    {
        if (checkAccessRights(clsUser::enPermissions::eFindClients))
        {
            clsUtil::clearConsoleScreen();
            _drawScreenHeader("Find client screen");
            _findClientProccess();
        }
        else
        {
            displayAccessDeniedScreen();
        };
    };
};
