/*
    Users class
*/

#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "../Lib/clsString.h"
#include "../Lib/clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{
private:
    // state management for clsUser objects
    enum _enUserState
    {
        eInvalidUser,
        eExistingUser,
        eNewUser,
        eMarkedForDelete
    };

    _enUserState _userState;
    string _username = "";
    string _password = "";
    int _permissions = 0;

    static clsUser _convertLineRecordToObject(string recordLine, string recordSeparator = "#//#")
    {
        vector<string> vRecord = clsString::split(recordLine, recordSeparator);
        return clsUser(
            _enUserState::eExistingUser,
            vRecord.at(0),
            vRecord.at(1),
            vRecord.at(2),
            vRecord.at(3),
            vRecord.at(4),                      // username
            clsUtil::decrypt(vRecord.at(5), 2), // password // decrypt password for internal use in the system
            stoi(vRecord.at(6)));
    };

    static string _convertObjectToLineRecord(clsUser user, string recordSeparator = "#//#")
    {
        string s = "";
        s += user.firstName + recordSeparator;
        s += user.lastName + recordSeparator;
        s += user.email + recordSeparator;
        s += user.phoneNumber + recordSeparator;
        s += user.username + recordSeparator;
        s += clsUtil::encrypt(user.password, 2) + recordSeparator; // encrypt passwords in record file
        s += to_string(user.permissions);
        return s;
    };

    static clsUser _getInvalidUserObject()
    {
        return clsUser(_enUserState::eInvalidUser, "", "", "", "", "", "", 0);
    };

    static clsUser _getNewUserObject()
    {
        return clsUser(_enUserState::eNewUser, "", "", "", "", "", "", 0);
    };

    static vector<clsUser> _loadUsersRecordFromFile()
    {
        vector<clsUser> vUsers;
        fstream file;
        file.open("Data/Users.txt", ios::in); // read mode
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                vUsers.push_back(_convertLineRecordToObject(line));
            };
            file.close();
        };
        return vUsers;
    };

    static void _saveUsersDataToFile(vector<clsUser> vUsers)
    {
        fstream file;
        file.open("Data/Users.txt", ios::out); // write/overwrite mode
        if (file.is_open())
        {
            for (clsUser &u : vUsers)
            {
                if (!u.isMarkedForDelete())
                    file << _convertObjectToLineRecord(u) << '\n';
            }
            file.close();
        }
    };

    static void _addNewRecordLineToFile(string recordLine)
    {
        fstream file;
        file.open("Data/Users.txt", ios::app); // append mode
        if (file.is_open())
        {
            file << recordLine << '\n';
            file.close();
        }
    };

    void _update()
    {
        vector<clsUser> vUsers = _loadUsersRecordFromFile();
        for (clsUser &user : vUsers)
        {
            if (user.username == this->username)
            {
                // implementation error, if user changes his username, this if statement will always be false due to the user record doesn't match the current object
                // or if you have two users with the same username(which you shouldn't), the first one found in the for loop iteration will be changed, even if it's not the intended one to be changed.
                // possible fix with unique ID OR inforce unique username
                user = *this;
                break;
            }
        }
        // user data updated in memory, now we should update the file record
        _saveUsersDataToFile(vUsers);
    };

    void _addNew()
    {
        // Note:
        // user object is being added to file record
        // but the new user object is not added to the internal data structure like vector<clsUser>
        // and new object it is only kept in memory.
        _addNewRecordLineToFile(_convertObjectToLineRecord(*this));
    };

public:
    enum enPermissions
    {
        /*
            Permission system implementation:
            enum values represent a Bit value in the binary system as decimal values
            the value of each enum will be stored in the permission data member for future reference of user permissions
        */
        eFullAccess = -1,
        eNoAccess = 0,
        eListClients = 1,
        eAddClients = 2,
        eUpdateClients = 4,
        eDeleteClients = 8,
        eFindClients = 16,
        eTransactions = 32,
        eManageUsers = 64,
        eShowLoginRegister = 128
    };

    clsUser(_enUserState userState, string firstName, string lastName, string email, string phoneNumber, string username, string password, int permissions)
        : clsPerson(firstName, lastName, email, phoneNumber)
    {
        _userState = userState;
        _username = username;
        _password = password;
        _permissions = permissions;
    };

    _enUserState getUserState() // readonly property
    {
        return _userState;
    };

    void setUsername(string username)
    {
        _username = username;
    };

    string getUsername()
    {
        return _username;
    };

    __declspec(property(get = getUsername, put = setUsername)) string username;

    void setPassword(string password)
    {
        _password = password;
    };

    string getPassword()
    {
        return _password;
    };

    __declspec(property(get = getPassword, put = setPassword)) string password;

    void setPermissions(int permissions)
    {
        _permissions = permissions;
    };

    int getPermissions()
    {
        return _permissions;
    };

    __declspec(property(get = getPermissions, put = setPermissions)) string permissions;

    bool isMarkedForDelete()
    {
        return _userState == _enUserState::eMarkedForDelete;
    };

    bool isInvalidUser()
    {
        return _userState == _enUserState::eInvalidUser;
    };

    static clsUser find(string username)
    {
        vector<clsUser> vUsers = _loadUsersRecordFromFile();
        for (clsUser &user : vUsers)
        {
            if (user.username == username)
                return user;
        }
        return _getInvalidUserObject();
    };

    static clsUser find(string username, string password)
    {
        vector<clsUser> vUsers = _loadUsersRecordFromFile();
        for (clsUser &user : vUsers)
        {
            if (user.username == username && user.password == password)
                return user;
        }
        return _getInvalidUserObject();
    };

    static bool isUserExists(string username)
    {
        return !clsUser::find(username).isInvalidUser();
    };

    bool isUserExists()
    {
        return !this->isInvalidUser();
    }

    static bool isNewUser(string username)
    {
        return clsUser::find(username)._userState == _enUserState::eNewUser;
    };

    bool isNewUser()
    {
        return _userState == _enUserState::eNewUser;
    };

    bool isUserDeleted()
    {
        return this->isMarkedForDelete() && this->isInvalidUser();
    };

    enum enSaveResult
    {
        eFailed,
        eSuccess,
        eAdded
    };

    enSaveResult save()
    {
        /*
            The idea of a save method for an object
            is to make an entry point for object changes/new object data to be saved
            with a single entry point that's exposed publicly, but keep the actual implementation
            for code that does the work hidden.

            -----------------------------------

            void save() will work just find.
            but we need a way to communicate back to what happened when the save method is called
            did it run successfully, or did it failed?

            instead of returning a boolean value, we introduce a much easier and more readable
            way to communicate via enumerators

            -----------------------------------

            Delete operation should be on its own method, so that the developer
            know exactly that he is deleteing the object instead of saying something like user.save() when trying to delete.
            it is much clearer to say user.delete() than user.save() to delete.

        */

        switch (_userState)
        {
        case _enUserState::eExistingUser:
            _update(); // update user data changes
            return enSaveResult::eSuccess;
        case _enUserState::eNewUser:
            // add new user data
            if (!this->isNewUser())
                return enSaveResult::eFailed; // user already exists.
            _addNew();
            this->_userState = _enUserState::eExistingUser;
            return enSaveResult::eAdded;

        default:
            return enSaveResult::eFailed; // failed to do any operation
        };
    };

    void deleteUser()
    {
        vector<clsUser> vUsers = _loadUsersRecordFromFile();
        for (clsUser &user : vUsers)
        {
            if (user.username == this->username)
            {
                user._userState = _enUserState::eMarkedForDelete;
                break;
            }
        };
        _saveUsersDataToFile(vUsers);
        *this = _getInvalidUserObject();
    };

    static clsUser getNewUserObject()
    {
        return _getNewUserObject();
    };

    static vector<clsUser> getAllUsers()
    {
        return _loadUsersRecordFromFile();
    };

    bool hasPermission(enPermissions permission)
    {
        if (this->_permissions == enPermissions::eFullAccess)
            return true;

        return ((this->_permissions & permission) == permission);
    };

    void grantFullSystemAccessPermission()
    {
        // IMPORTANT: security check must be implemented
        this->_permissions = enPermissions::eFullAccess;
    };

    void revokeUserPermissions()
    {
        // IMPORTANT: security check must be implemented
        this->_permissions = enPermissions::eNoAccess;
    };

    void grantUserPermission(enPermissions permission)
    {
        // IMPORTANT: security check must be implemented
        this->_permissions += permission;
    };

    void removeUserPermission(enPermissions permission)
    {
        // IMPORTANT: security check must be implemented
        this->_permissions -= permission;
    };
};