// Cab.h
#ifndef CAB_H
#define CAB_H

#include "./../Location/Location.h"
#include <vector>

class Cab
{
private:
    int cabId;
    Location currentLocation; // real-time location of the cab
    bool isFree = true;       // to indicate whether the cab is currently free
    char *driverName;

public:
    Cab(int id, const Location &currentLoc);

    int getCabId() const;
    bool isCabFree() const; // Getter for isFree
    char *getDriverName() const;
    void bookCab();     // Function to book a cab for the user
    void unbookCab();   // Function to unbook a cab for the user

    const Location &getCurrentLocation() const;
    void setCurrentLocation(const Location &loc);

    void updateLocation(const Location &newLocation);
};

#endif // CAB_H
