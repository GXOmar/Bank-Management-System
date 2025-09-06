#pragma once

#include <iostream>
#include "interfaceCommunication.h"

using namespace std;

class clsPerson : public clsInterfaceCommunication
{
private:
    string _firstName;
    string _lastName;
    string _email;
    string _phoneNumber;

public:
    clsPerson(string firstName, string lastName, string email, string phoneNumber)
    {
        _firstName = firstName;
        _lastName = lastName;
        _email = email;
        _phoneNumber = phoneNumber;
    }

    // properties set and get for each data member
    void setFirstName(string firstName)
    {
        _firstName = firstName;
    };

    string getFirstName()
    {
        return _firstName;
    };

    __declspec(property(get = getFirstName, put = setFirstName)) string firstName;

    void setLastName(string lastName)
    {
        _lastName = lastName;
    };

    string getLastName()
    {
        return _lastName;
    };

    __declspec(property(get = getLastName, put = setLastName)) string lastName;

    void setEmail(string email)
    {
        _email = email;
    };

    string getEmail()
    {
        return _email;
    };

    __declspec(property(get = getEmail, put = setEmail)) string email;

    void setPhoneNumber(string phoneNumber)
    {
        _phoneNumber = phoneNumber;
    };

    string getPhoneNumber()
    {
        return _phoneNumber;
    };

    __declspec(property(get = getPhoneNumber, put = setPhoneNumber)) string phoneNumber;

    string fullName()
    {
        return _firstName + " " + _lastName;
    };

    // Implementation of the pure virtual functions from abstract class
    void sendEmail(string title, string body)
    {
        cout << "Sending email..." << endl;
    };

    void sendFax(string title, string body)
    {
        cout << "Sending fax..." << endl;
    };

    void sendSMS(string title, string body)
    {
        cout << "Sending SMS..." << endl;
    };
};