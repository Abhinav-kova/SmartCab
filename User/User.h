// User.h
#ifndef USER_H
#define USER_H

#include <string>
#include "./../Location/Location.h"

class User
{
public:
    User();
    User(const int &userID, const std::string &username, const std::string &password);

    bool authenticate(const std::string &password) const;
    const std::string &getUsername() const;
    int getUserID() const;
    int getCurrentTripID() const;
    void setCurrentTripID(int tripID);
    const Location &getCurrentLocation() const;
    void setCurrentLocation(const Location &location);

private:
    int userID;
    std::string username;
    std::string password;
    int currentTripID; // maps to cabID if engaged, else -1 by default.
    Location currentLocation;
};

#endif // USER_H
