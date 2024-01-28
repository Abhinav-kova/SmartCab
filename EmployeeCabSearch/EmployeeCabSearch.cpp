#include "EmployeeCabSearch.h"
#include <cmath>
#include <algorithm>

using namespace std;

EmployeeCabSearch::EmployeeCabSearch(const Location &empLoc, CabAllocationSystem &cabAllocSys)
    : employeeLocation(empLoc), cabAllocationSystem(cabAllocSys) {}

double EmployeeCabSearch::calculateDistance(const Location &loc1, const Location &loc2) const
{
    double lat1 = loc1.getLatitude();
    double lon1 = loc1.getLongitude();
    double lat2 = loc2.getLatitude();
    double lon2 = loc2.getLongitude();

    double distance = sqrt((lat2 - lat1) * (lat2 - lat1) + (lon2 - lon1) * (lon2 - lon1));

    return distance;
}

std::vector<Cab>& EmployeeCabSearch::getAllCabs()
{
    std::vector<Cab> &allCabs = cabAllocationSystem.getAllCabs();
    return allCabs;
}

std::vector<Cab> EmployeeCabSearch::suggestNearbyCabs()
{
    std::vector<Cab> &allCabs = cabAllocationSystem.getAllCabs();

    std::vector<Cab> nearbyCabs;

    for (const auto &cab : allCabs)
    {
        if (cab.isCabFree() == false)
        {
            continue;
        }

        double distance = calculateDistance(employeeLocation, cab.getCurrentLocation());

        if (distance < 100.0)
        {
            nearbyCabs.push_back(cab);
        }
    }

    sort(nearbyCabs.begin(), nearbyCabs.end(), [this](const Cab &cab1, const Cab &cab2)
         { return calculateDistance(employeeLocation, cab1.getCurrentLocation()) < calculateDistance(employeeLocation, cab2.getCurrentLocation()); });

    return nearbyCabs;
}
