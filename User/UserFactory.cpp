// UserFactory.cpp
#include "UserFactory.h"

User UserFactory::createUser(const int &userID, const std::string &username, const std::string &password)
{
    return User(userID, username, password);
}