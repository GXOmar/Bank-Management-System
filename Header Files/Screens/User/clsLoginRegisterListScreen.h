/*
    UI - Login register list screen
*/

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "../../Lib/clsString.h"
#include "../../Lib/clsUtil.h"
#include "../clsScreen.h"
#include "../../Core/clsUser.h"

using namespace std;

class clsLoginRegisterListScreen : protected clsScreen
{
private:
    struct _stLoginRecord
    {
        string date;
        string time;
        string username;
        string password;
        int permissions;
    };

    static void _printTableHeader()
    {
        cout << "_________________________________________________________________________________\n";
        cout << "| " << setw(30) << "Date - Time";
        cout << "| " << setw(15) << "Username";
        cout << "| " << setw(15) << "Password";
        cout << "| " << setw(8) << "Permissions";
        cout << "\n_________________________________________________________________________________\n";
    };

    static void _printLoginRecord(_stLoginRecord record)
    {
        cout << "| " << setw(30) << record.date + " - " + record.time;
        cout << "| " << setw(15) << record.username;
        cout << "| " << setw(15) << record.password;
        cout << "| " << setw(8) << to_string(record.permissions);
        cout << endl;
    };

    static _stLoginRecord _convertRecordLineToLoginStruct(string lineRecord)
    {
        vector<string> vEntry = clsString::split(lineRecord, "#//#");
        vector<string> vEntryDateTime = clsString::split(vEntry.at(0), " - ");
        _stLoginRecord stRecord;
        stRecord.date = vEntryDateTime.at(0);
        stRecord.time = vEntryDateTime.at(1);
        stRecord.username = vEntry.at(1);
        stRecord.password = clsUtil::decrypt(vEntry.at(2), 2);
        stRecord.permissions = stoi(vEntry.at(3));
        return stRecord;
    };

    static vector<_stLoginRecord> _loadLoginRegisterRecordsFromFile()
    {
        vector<_stLoginRecord> vLoginRecords;
        fstream registerFile;
        registerFile.open("Data/LoginRegister.txt", ios::in); // read mode
        if (registerFile.is_open())
        {
            string line;
            while (getline(registerFile, line))
            {
                vLoginRecords.push_back(_convertRecordLineToLoginStruct(line));
            }
            registerFile.close();
        }
        return vLoginRecords;
    };

    static void _listLoginRecordOnScreen()
    {
        vector<_stLoginRecord> vLogs = _loadLoginRegisterRecordsFromFile();
        string recordsNumber = "\t(" + to_string(vLogs.size()) + ")" + " Record(s).";
        _drawScreenHeader("\tLogin register list screen", recordsNumber);

        _printTableHeader();
        for (_stLoginRecord &l : vLogs)
        {
            _printLoginRecord(l);
        }
        cout << "\n_________________________________________________________________________________\n";
    }

public:
    static void showLoginRegisterListScreen()
    {
        if (clsScreen::checkAccessRights(clsUser::enPermissions::eShowLoginRegister))
        {
            clsUtil::clearConsoleScreen();
            _listLoginRecordOnScreen();
        }
        else
        {
            clsScreen::displayAccessDeniedScreen();
        }
    }
};
