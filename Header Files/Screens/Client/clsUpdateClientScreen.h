/*
    UI - Update client screen
*/

#pragma once
#include <iostream>
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"
#include "../clsScreen.h"
#include "../../Lib/clsUtil.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
{
private:
    static void _readClientData(clsBankClient &client)
    {
        client.firstName = clsInputValidate::readString("Enter first name: ");
        client.lastName = clsInputValidate::readString("Enter last name: ");
        client.email = clsInputValidate::readString("Enter email: ");
        client.phoneNumber = clsInputValidate::readString("Enter phone number: ");
        client.pinCode = clsInputValidate::readString("Enter PIN code: ");
        cout << "Enter balance amount: ";
        client.balance = clsInputValidate::readDblNumber();
    };

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

    static void _runUpdateClientProccess()
    {
        string accountNumber = clsInputValidate::readString("Please enter an account number: ");
        while (!clsBankClient::isClientExists(accountNumber))
        {
            cout << "Account not found, please enter a different account number: ";
            accountNumber = clsInputValidate::readString();
        };

        clsBankClient client = clsBankClient::find(accountNumber);
        _printClient(client);

        cout << "\nUpdate client information\n";
        cout << "------------------------------\n";

        _readClientData(client);

        clsBankClient::enSaveResult saveResult;

        if (clsInputValidate::askYesOrNo("Are you sure you want to update client information (Y/N)? "))
        {
            saveResult = client.save();
        };

        switch (saveResult)
        {
        case clsBankClient::success:
            cout << "\nClinet data updated successfully" << endl;
            break;

        default:
            cout << "\nFiled to update client data!" << endl;
            break;
        };
    };

public:
    static void showUpdateClientScreen()
    {
        if (checkAccessRights(clsUser::enPermissions::eUpdateClients))
        {
            clsUtil::clearConsoleScreen();
            _drawScreenHeader("\tUpdate client screen");
            _runUpdateClientProccess();
        }
        else
        {
            displayAccessDeniedScreen();
        };
    }
};