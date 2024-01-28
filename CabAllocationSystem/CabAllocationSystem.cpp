#include "CabAllocationSystem.h"
#include <limits>
#include <iostream>
using namespace std;

void CabAllocationSystem::addCab(const Cab &newCab)
{
    cabs.push_back(newCab);
}

std::vector<Cab>& CabAllocationSystem::getAllCabs()
{
    return cabs;
}

Cab &CabAllocationSystem::getCabByID(int cabId)
{
    for (auto &cab : cabs)
    {
        if (cab.getCabId() == cabId)
        {
            return cab;
        }
    }

    throw std::runtime_error("Cab not found");
}

double CabAllocationSystem::calculateDistance(const Location &loc1, const Location &loc2) const
{
    double latDiff = loc1.latitude - loc2.latitude;
    double lonDiff = loc1.longitude - loc2.longitude;
    return sqrt(latDiff * latDiff + lonDiff * lonDiff);
}

Cab &CabAllocationSystem::findBestCab(const Trip &trip)
{
    int bestCabId = -1;
    double minDistance = std::numeric_limits<double>::max();

    cabs = getAllCabs();

    for (const auto &cab : cabs)
    {
        double distance = calculateDistance(cab.getCurrentLocation(), trip.getPickupLocation());
        if (distance < minDistance)
        {
            minDistance = distance;
            bestCabId = cab.getCabId();
        }
    }

    if (bestCabId == -1)
    {
        throw std::runtime_error("No cabs available");
    }

    return cabs[bestCabId - 1];
}

double CabAllocationSystem::calculateFareForBestCab(const Cab &bestCab, const Location &startLocation, const Location &endLocation) const
{
    double distance = calculateDistance(startLocation, endLocation);
    double basicFare = 5.0;
    double farePerKilometer = 2.0;
    double totalFare = basicFare + (farePerKilometer * distance);
    return totalFare;
}

void CabAllocationSystem::updateCabLocation(int cabId, const Location &newLocation)
{
    for (Cab &cab : cabs)
    {
        if (cab.getCabId() == cabId)
        {
            cab.setCurrentLocation(newLocation);
            break;
        }
    }
}
