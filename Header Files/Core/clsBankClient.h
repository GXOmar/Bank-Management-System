/*
    Bank clinet class
*/
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "clsPerson.h"
#include "../Lib/clsString.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:
    enum enMode
    {
        // The enMode enumeration is used to track the state of a clsBankClient object and control how it behaves when saved or modified. It helps distinguish between different lifecycle stages of a client object.
        emptyMode = 0,  // Represents an invalid/uninitialized client.
        updateMode = 1, // Object exists and is being modified.
        addNew = 2      // Object is new and needs to be added to storage.
    };

    enMode _mode;
    string _accountNumber;
    string _pinCode;
    double _balance;
    bool _markedForDelete = false; // this could be implemented as a delete mode!

    static clsBankClient _convertLineRecordToObject(string lineRecord)
    {
        vector<string> vRecord = clsString::split(lineRecord, "#//#");
        return clsBankClient(
            enMode::updateMode,
            vRecord.at(0),
            vRecord.at(1),
            vRecord.at(2),
            vRecord.at(3),
            vRecord.at(4),
            vRecord.at(5),
            stod(vRecord.at(6)));
    };

    static string _convertObjectToLineRecord(clsBankClient client, string separator = "#//#")
    {
        string s = "";
        s += client.firstName + separator;
        s += client.lastName + separator;
        s += client.email + separator;
        s += client.phoneNumber + separator;
        s += client.accountNumber + separator;
        s += client.pinCode + separator;
        s += to_string(client.balance);
        return s;
    };

    static clsBankClient _getEmptyClientObject()
    {
        return clsBankClient(enMode::emptyMode, "", "", "", "", "", "", 0); // represent an object with empty data
    };

    static vector<clsBankClient> _loadClientsDataFromFile()
    {
        vector<clsBankClient> vClients;
        fstream file;
        file.open("Data/Clients.txt", ios::in); // read mode
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                vClients.push_back(_convertLineRecordToObject(line));
            };
        }
        file.close();
        return vClients;
    };

    static void _saveClientsDataToFile(vector<clsBankClient> &vClients)
    {
        fstream file;
        file.open("Data/Clients.txt", ios::out); // write mode
        if (file.is_open())
        {
            for (clsBankClient &c : vClients)
            {
                if (c.isMarkedForDelete() == false)
                {
                    file << _convertObjectToLineRecord(c) << '\n';
                }
            }
        }
        file.close();
    };

    void _addDataLineToFile(string clientRecord)
    {
        fstream file;
        file.open("Data/Clients.txt", ios::out | ios::app); // write or append mode
        if (file.is_open())
        {
            file << clientRecord << '\n';
            file.close();
        }
    };

    void _addNewClient()
    {
        _addDataLineToFile(_convertObjectToLineRecord(*this));
    };

    void _update()
    {
        vector<clsBankClient> vClients = _loadClientsDataFromFile();
        for (clsBankClient &client : vClients)
        {
            if (client.accountNumber == this->accountNumber)
            {
                client = *this;
                break;
            }
        }
        _saveClientsDataToFile(vClients);
    };

public:
    clsBankClient(enMode mode, string firstName, string lastName, string email, string phoneNumber, string accountNumber, string pinCode, double balance)
        : clsPerson(firstName, lastName, email, phoneNumber)
    {
        _mode = mode;
        _accountNumber = accountNumber;
        _pinCode = pinCode;
        _balance = balance;
    };

    // readonly property
    string getAccountNumber()
    {
        return _accountNumber;
    };

    __declspec(property(get = getAccountNumber)) string accountNumber;

    void setPinCode(string pinCode)
    {
        _pinCode = pinCode;
    };

    string getPinCode()
    {
        return _pinCode;
    };

    __declspec(property(get = getPinCode, put = setPinCode)) string pinCode;

    void setBalance(double balance)
    {
        _balance = balance;
    };

    double getBalance()
    {
        return _balance;
    };

    __declspec(property(get = getBalance, put = setBalance)) string balance;

    bool isEmpty()
    {
        return _mode == enMode::emptyMode;
    };

    bool isMarkedForDelete()
    {
        return _markedForDelete;
    };

    static clsBankClient find(string accountNumber)
    {
        // find and return a clinet instance by searching via account number
        fstream clientsRecordfile;
        clientsRecordfile.open("Data/Clients.txt", ios::in); // read mode

        if (clientsRecordfile.is_open())
        {
            string line;
            while (getline(clientsRecordfile, line))
            {
                clsBankClient client = _convertLineRecordToObject(line);
                if (client.accountNumber == accountNumber)
                {
                    clientsRecordfile.close();
                    return client; // client found!
                };
            };
        };
        clientsRecordfile.close();
        return _getEmptyClientObject(); // client NOT found!
    };

    static clsBankClient find(string accountNumber, string pinCode)
    {
        clsBankClient client = clsBankClient::find(accountNumber);
        if (client.accountNumber == accountNumber && client.pinCode == pinCode)
            return client;
        return _getEmptyClientObject();
    }

    static bool isClientExists(string accountNumber)
    {
        clsBankClient client = clsBankClient::find(accountNumber);
        return (!client.isEmpty());
    };

    enum enSaveResult
    {
        failed,
        success,
        failedAccountAlreadyExists
    };

    enSaveResult save()
    {
        // entry point to save data for object
        switch (_mode)
        {
        case enMode::updateMode:
            _update();
            return enSaveResult::success;
        case enMode::addNew:
            // this will add a new record to file or database

            // this mechanism will protect the backend system and protect the data from being duplicated
            // if for example a fellow developer called the save() method with the same account number
            // of an account that already exists
            if (clsBankClient::isClientExists(accountNumber))
                return clsBankClient::enSaveResult::failedAccountAlreadyExists;

            _addNewClient();
            // set object's mode to update after adding a new object
            _mode = enMode::updateMode;
            return enSaveResult::success;
        default:
            return enSaveResult::failed;
        }
    };

    bool deposit(double amount)
    {
        if (canDepositAmount(amount))
        {
            this->_balance += amount;
            return true;
        }
        return false;
    };

    bool withdraw(double amount)
    {
        if (canWithdrawAmount(amount))
        {
            this->_balance -= amount;
            return true;
        }
        return false;
    };

    bool canDepositAmount(double amount)
    {
        return amount > 0;
    };

    bool canWithdrawAmount(double amount)
    {
        return amount <= _balance;
    };

    bool transfer(double amount, clsBankClient &recapinat)
    {
        if (canWithdrawAmount(amount) && recapinat.canDepositAmount(amount))
        {
            this->withdraw(amount);
            recapinat.deposit(amount);
            return true;
        }
        return false;
    };

    void deleteClient()
    {
        vector<clsBankClient> vClients = _loadClientsDataFromFile();
        for (clsBankClient &c : vClients)
        {
            if (c.accountNumber == this->_accountNumber)
            {
                c._markedForDelete = true;
                break;
            }
        }
        _saveClientsDataToFile(vClients);
        *this = _getEmptyClientObject();
    }

    static clsBankClient getAddNewClientObject(string accountNumber)
    {
        return clsBankClient(enMode::addNew, "", "", "", "", accountNumber, "", 0); // represent a new object with new account number
    };

    static vector<clsBankClient> getAllClients()
    {
        return _loadClientsDataFromFile();
    }

    static double getTotalClientsBalances()
    {
        vector<clsBankClient> vClient = _loadClientsDataFromFile();
        double totalBalances = 0;
        for (clsBankClient &c : vClient)
            totalBalances += c.balance;
        return totalBalances;
    }
};