// EmployeeCabSearch.h
#ifndef EMPLOYEE_CAB_SEARCH_H
#define EMPLOYEE_CAB_SEARCH_H

#include "./../Location/Location.h"
#include "./../Cab/Cab.h"
#include "./../Trip/Trip.h"
#include "./../CabAllocationSystem/CabAllocationSystem.h"

class EmployeeCabSearch {
private:
    Location employeeLocation;
    CabAllocationSystem& cabAllocationSystem;

public:
    EmployeeCabSearch(const Location& empLoc, CabAllocationSystem& cabAllocSys);

    // Method to suggest nearby cabs for the employee
    std::vector<Cab> suggestNearbyCabs();
    std::vector<Cab>& getAllCabs();
    double calculateDistance(const Location& loc1, const Location& loc2) const;

};

#endif // EMPLOYEE_CAB_SEARCH_H
