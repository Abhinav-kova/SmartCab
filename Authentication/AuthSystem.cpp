#include "AuthSystem.h"

void AuthSystem::addUser(const User &user)
{
    users.push_back(user);
}

User AuthSystem::getUser(int userID) const
{
    for (const auto &user : users)
    {
        if (user.getUserID() == userID)
        {
            return user;
        }
    }
    return User();
}

int AuthSystem::authenticateUser(const std::string &username, const std::string &password) const
{
    for (const auto &user : users)
    {
        if (user.getUsername() == username && user.authenticate(password))
        {
            return user.getUserID();
        }
    }
    return -1;
}
