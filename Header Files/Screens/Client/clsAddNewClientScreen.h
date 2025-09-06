/*
    UI - Add new client screen
*/
#pragma once
#include <iostream>
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"
#include "../clsScreen.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
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

    static void printDetails(clsBankClient client)
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

    static void _addNewClient()
    {
        string accountNumber = clsInputValidate::readString("Please enter an account number: ");
        while (clsBankClient::isClientExists(accountNumber))
        {
            accountNumber = clsInputValidate::readString("Account already exists, enter a different one: ");
        };

        clsBankClient client = clsBankClient::getAddNewClientObject(accountNumber); // return a new instance with empty data to be filled from this proccess

        _readClientData(client);

        clsBankClient::enSaveResult savingResult;

        if (clsInputValidate::askYesOrNo("Are you sure you want to add this new client (Y/N)? "))
        {
            savingResult = client.save();
        };

        switch (savingResult)
        {
        case clsBankClient::success:
            cout << "\nClinet added successfully" << endl;
            break;

        case clsBankClient::failedAccountAlreadyExists:
            cout << "\nFailed to add new account, account already exists!" << endl;
            break;

        default:
            cout << "\nFiled to add new client!" << endl;
            break;
        };
    };

public:
    static void showAddNewClientScreen()
    {
        if (checkAccessRights(clsUser::enPermissions::eAddClients))
        {
            clsUtil::clearConsoleScreen();
            _drawScreenHeader("\tAdd new clinet");
            _addNewClient();
        }
        else
        {
            displayAccessDeniedScreen();
        };
    }
};