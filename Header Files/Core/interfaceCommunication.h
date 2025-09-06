/*
    Abstract/Interface/Contract class
*/

#pragma once
#include <iostream>

using namespace std;

class clsInterfaceCommunication
{
public:
    virtual void sendEmail(string subject, string body) = 0;
    virtual void sendFax(string title, string body) = 0;
    virtual void sendSMS(string title, string body) = 0;
};