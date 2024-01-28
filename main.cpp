#include <iostream>
#include "Location/Location.h"
#include "Cab/Cab.h"
#include "Trip/Trip.h"
#include "CabAllocationSystem/CabAllocationSystem.h"
#include "EmployeeCabSearch/EmployeeCabSearch.h"
#include "Authentication/AuthSystem.h"
#include "User/UserFactory.h"
#include "Authentication/AuthenticationHelper.h"
#include "User/User.h"
#include "ConsoleUI/ConsoleUI.h"

using namespace std;

int main()
{
    AuthSystem authSystem;

    User user1 = UserFactory::createUser(1, "Abhinav", "pass1");
    User user2 = UserFactory::createUser(2, "Jayanth", "pass2");
    authSystem.addUser(user1);
    authSystem.addUser(user2);

    int authenticationSuccessful = AuthenticationHelper::performAuthentication(authSystem);

    User currentUser = authSystem.getUser(authenticationSuccessful);
    int currentUserId = -1;

    if (authenticationSuccessful != -1)
    {
        currentUserId = authenticationSuccessful;
    }
    else
    {
        cerr << "Authentication failed. Exiting the program." << std::endl;
        exit(EXIT_FAILURE);
    }

    CabAllocationSystem cabAllocationSystem;

    Cab cab1(1, Location(37.7749, -122.4194));
    Cab cab2(2, Location(34.0522, -118.2437));
    Cab cab3(3, Location(31.0522, -129.2437));

    cabAllocationSystem.addCab(cab1);
    cabAllocationSystem.addCab(cab2);
    cabAllocationSystem.addCab(cab3);

    cout << "Initial Cab Locations:" << std::endl;
    cout << "Cab 1: (" << cab1.getCurrentLocation().getLatitude() << ", " << cab1.getCurrentLocation().getLongitude() << ")" << std::endl;
    cout << "Cab 2: (" << cab2.getCurrentLocation().getLatitude() << ", " << cab2.getCurrentLocation().getLongitude() << ")" << std::endl;
    cout << "Cab 3: (" << cab3.getCurrentLocation().getLatitude() << ", " << cab3.getCurrentLocation().getLongitude() << ")" << std::endl;

    ConsoleUI consoleUI(cabAllocationSystem, currentUser);

    cout << "\n==== Smart Cab Allocation System ====\n";
    consoleUI.processUserInput(cabAllocationSystem, currentUser);
    cout << "====================================\n";

    return 0;
}
