// CabAllocationSystem.h
#ifndef CAB_ALLOCATION_SYSTEM_H
#define CAB_ALLOCATION_SYSTEM_H

#include <vector>
#include <cmath>
#include "./../Cab/Cab.h"
#include "./../Trip/Trip.h"

class CabAllocationSystem
{
private:
    std::vector<Cab> cabs;

public:
    void addCab(const Cab &newCab);
    Cab &findBestCab(const Trip &trip);
    double calculateDistance(const Location &loc1, const Location &loc2) const;
    void updateCabLocation(int cabId, const Location &newLocation);
    std::vector<Cab> &getAllCabs();
    Cab &getCabByID(int cabId);
    double calculateFareForBestCab(const Cab &bestCab, const Location &startLocation, const Location &endLocation) const;
};

#endif // CAB_ALLOCATION_SYSTEM_H