// AuthenticationHelper.h
#pragma once

#include "AuthSystem.h"
#include <iostream>

class AuthenticationHelper
{
public:
    static int performAuthentication(AuthSystem &authSystem);
};
