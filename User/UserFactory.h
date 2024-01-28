// UserFactory.h
#pragma once

#include "User.h"

class UserFactory
{
public:
    static User createUser(const int &userID, const std::string &username, const std::string &password);
};
