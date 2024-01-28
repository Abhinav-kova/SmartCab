// User.cpp
#include "User.h"

User::User() : userID(-1), username(""), password(""), currentTripID(-1){};

User::User(const int &userID, const std::string &username, const std::string &password)
    : userID(userID), username(username), password(password), currentTripID(-1){};

bool User::authenticate(const std::string &inputPassword) const
{
    return password == inputPassword;
}

const std::string &User::getUsername() const
{
    return username;
}

int User::getUserID() const
{
    return userID;
}

int User::getCurrentTripID() const
{
    return currentTripID;
}

void User::setCurrentTripID(int tripID)
{
    currentTripID = tripID;
}

const Location &User::getCurrentLocation() const
{
    return currentLocation;
}

void User::setCurrentLocation(const Location &location)
{
    currentLocation = location;
}