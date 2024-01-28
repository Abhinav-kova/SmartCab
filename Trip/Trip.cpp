// Trip.cpp
#include "Trip.h"

Trip::Trip() : startLocation(Location()), endLocation(Location()) {}
Trip::Trip(Location startLoc, Location endLoc) : startLocation(startLoc), endLocation(endLoc) {}

Location Trip::getPickupLocation() const
{
    return startLocation;
}

Location Trip::getDropoffLocation() const
{
    return endLocation;
}
