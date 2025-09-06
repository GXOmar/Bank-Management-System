/*
    UI - Delete client screen
*/
#pragma once
#include <iostream>
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"
#include "../clsScreen.h"
#include "../../Lib/clsUtil.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
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

    static void _runClientDeletionProccess()
    {
        string accountNumber = clsInputValidate::readString("Please enter an account number: ");
        while (!clsBankClient::isClientExists(accountNumber))
        {
            accountNumber = clsInputValidate::readString("Account not found! please enter a different one: ");
        };

        clsBankClient client = clsBankClient::find(accountNumber);
        _printClient(client);

        if (clsInputValidate::askYesOrNo("Are you sure you want to delete this clinet (Y/N)? "))
        {
            client.deleteClient();
        }

        _printClient(client);

        if (client.isEmpty())
        {
            cout << "\nClient deleted successfully" << endl;
        }
        else
        {
            cout << "\nClient was not deleted!" << endl;
        }
    };

public:
    static void showDeleteClientScreen()
    {
        if (checkAccessRights(clsUser::enPermissions::eDeleteClients))
        {
            clsUtil::clearConsoleScreen();
            _drawScreenHeader("\tDelete user screen");
            _runClientDeletionProccess();
        }
        else
        {
            displayAccessDeniedScreen();
        };
    };
};