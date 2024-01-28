// Trip.h
#ifndef TRIP_H
#define TRIP_H

#include "./../Location/Location.h"

class Trip
{
public:
    Location startLocation;
    Location endLocation;

    Trip();
    Trip(Location startLoc, Location endLoc);

    Location getPickupLocation() const;

    Location getDropoffLocation() const;
};

#endif // TRIP_H
