/*
    Global header file

    this file serves as a global information across the entire system.
    it acts as a global variables for a file (which is outside of a function)
    but on a bigger scale for the entire system to access certain data
*/
#pragma once
#include <iostream>
#include "Core/clsUser.h"

clsUser currentUser = clsUser::find("", ""); // act as the currently logged in user in the system
