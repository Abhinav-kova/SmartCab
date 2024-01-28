// AuthSystem.h
#ifndef AUTH_SYSTEM_H
#define AUTH_SYSTEM_H

#include <vector>
#include "./../User/User.h"

class AuthSystem
{
public:
    void addUser(const User &user);
    int authenticateUser(const std::string &username, const std::string &password) const;
    User getUser(int userID) const;

private:
    std::vector<User> users;
};

#endif // AUTH_SYSTEM_H
