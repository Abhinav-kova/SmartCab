#include "ConsoleUI.h"
#include <iostream>
#include <vector>
#include "./../CabAllocationSystem/CabAllocationSystem.h"
#include "./../EmployeeCabSearch/EmployeeCabSearch.h"
#include "./../Trip/Trip.h"

using namespace std;

ConsoleUI::ConsoleUI(CabAllocationSystem &cabAllocSys, User &currentUser) : cabAllocationSystem(cabAllocSys), currentUser(currentUser){};

void ConsoleUI::displayMenu()
{
    cout << "\n ================================== \n";
    cout << "|   Smart Cab Allocation System   |\n";
    cout << "|==================================| \n";
    cout << "| 1. Display Nearby Cab Locations  |\n";
    cout << "| 2. Request a Cab                 |\n";
    cout << "| 3. Trip completed                |\n";
    cout << "| 4. Get UserID and user location  |\n";
    cout << "| 5. Exit                          |\n";
    cout << "|==================================|\n";
}

void ConsoleUI::processUserInput(CabAllocationSystem &cabAllocSys, User &currentUser)
{
    int choice;
    double userLatitudeStart, userLongitudeStart, userLatitudeEnd, userLongitudeEnd;

    cout << "Enter your current latitude: ";
    cin >> userLatitudeStart;
    cout << "Enter your current longitude: ";
    cin >> userLongitudeStart;

    currentUser.setCurrentLocation(Location(userLatitudeStart, userLongitudeStart));

    Location tripStartLocation(userLatitudeStart, userLongitudeStart);

    vector<Cab> allCabs = cabAllocSys.getAllCabs();

    // Display initial cab locations
    cout << "Initial Cab Locations:" << endl;
    for (const auto &cab : allCabs)
    {
        cout << "Cab ID: " << cab.getCabId() << ", Location: (" << cab.getCurrentLocation().getLatitude() << ", " << cab.getCurrentLocation().getLongitude() << ")" << endl;
    }

    EmployeeCabSearch employeeCabSearch(tripStartLocation, cabAllocSys);

    vector<Cab> nearbyCabs;

    do
    {
        displayMenu();
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "Enter your current latitude: ";
            cin >> userLatitudeStart;
            cout << "Enter your current longitude: ";
            cin >> userLongitudeStart;

            currentUser.setCurrentLocation(Location(userLatitudeStart, userLongitudeStart));

            Location tripStartLocation(userLatitudeStart, userLongitudeStart);

            try
            {
                EmployeeCabSearch employeeCabSearch(tripStartLocation, cabAllocSys);

                nearbyCabs = employeeCabSearch.suggestNearbyCabs();

                cout << "|==========================================|" << endl;
                cout << "| Suggested Nearby Cabs:            |" << endl;
                cout << "|==========================================|" << endl;
                for (const auto &cab : nearbyCabs)
                {
                    cout << "| Cab ID: " << cab.getCabId() << ", Location: (" << cab.getCurrentLocation().getLatitude() << ", " << cab.getCurrentLocation().getLongitude() << ") |" << endl;
                }
                cout << "|==========================================|" << endl;
            }
            catch (const std::exception &e)
            {
                cerr << "Error: " << e.what() << endl;
            }

            break;
        }

        case 2:
        {
            if (currentUser.getCurrentTripID() != -1)
            {
                cout << "You already have a trip booked. Please complete the trip before booking another one." << endl;
                break;
            }

            cout << "Enter your current latitude: ";
            cin >> userLatitudeStart;
            cout << "Enter your current longitude: ";
            cin >> userLongitudeStart;

            currentUser.setCurrentLocation(Location(userLatitudeStart, userLongitudeStart));

            Location tripStartLocation(userLatitudeStart, userLongitudeStart);

            vector<Cab> allCabs = cabAllocSys.getAllCabs();

            EmployeeCabSearch employeeCabSearch(tripStartLocation, cabAllocSys);

            nearbyCabs = employeeCabSearch.suggestNearbyCabs();

            if (nearbyCabs.empty())
            {
                cout << "No cabs available." << endl;
                break;
            }

            cout << "Enter your destination latitude: ";
            cin >> userLatitudeEnd;
            cout << "Enter your destination longitude: ";
            cin >> userLongitudeEnd;

            Location tripEndLocation(userLatitudeEnd, userLongitudeEnd);

            Trip trip(tripStartLocation, tripEndLocation);

            Cab bestCab(-1, Location(0.0, 0.0));
            bool cabFound = false;

            try
            {
                bestCab = cabAllocSys.findBestCab(trip);
                cabFound = true;
                // Proceed with using bestCab
            }
            catch (const std::runtime_error &e)
            {
                cerr << "Error: " << e.what() << endl;
                cerr << "Exiting the program." << endl;
                // Perform cleanup or additional actions if needed
                exit(EXIT_FAILURE);
            }

            // Display the best cab information only if a cab was found
            if (cabFound)
            {
                // Find the best cab fare
                double fare = cabAllocSys.calculateFareForBestCab(bestCab, tripStartLocation, tripEndLocation);

                cout << "|==============================================|" << endl;
                cout << "| Best Cab for the Trip:                       |" << endl;
                cout << "| Cab ID: " << bestCab.getCabId() << endl;
                cout << "| Current Location of Cab: (" << bestCab.getCurrentLocation().getLatitude() << ", " << bestCab.getCurrentLocation().getLongitude() << ")" << endl;
                cout << "| Trip Start Location: (" << tripStartLocation.getLatitude() << ", " << tripStartLocation.getLongitude() << ")" << endl;
                cout << "| Trip End Location: (" << tripEndLocation.getLatitude() << ", " << tripEndLocation.getLongitude() << ")" << endl;
                cout << "| Fare for the trip: $" << fare << endl;
                cout << "|==============================================|" << endl;

                cout << "| Do you want to book the cab? (0/1)           |" << endl;
                int book;
                cin >> book;
                if (book == 0)
                {
                    cout << "| Cab not booked.                               |" << endl;
                    break;
                }
                cout << "| Booking the cab...                           |" << endl;
                bestCab.bookCab();
                currentUser.setCurrentTripID(bestCab.getCabId());
                cout << "| Cab booked!                                  |" << endl;
            }
            else
            {
                cout << "No cabs available." << endl;
            }

            break;
        }

        case 3:
        {
            if (currentUser.getCurrentTripID() == -1)
            {
                cout << "You do not have a trip booked. Please book a trip before completing one." << endl;
                break;
            }

            cout << "|==============================================|" << endl;
            cout << "| Trip completed!                               |" << endl;
            cout << "|==============================================|" << endl;

            Cab currentCab = cabAllocSys.getCabByID(currentUser.getCurrentTripID());
            Location tripEnd(userLatitudeEnd, userLongitudeEnd);
            currentCab.setCurrentLocation(tripEnd);
            
            currentCab.unbookCab();
            currentUser.setCurrentTripID(-1);

            auto &cabs = employeeCabSearch.getAllCabs();

            cabs[currentCab.getCabId() - 1] = currentCab;

            currentUser.setCurrentLocation(tripEnd);

            cout << "\n";

            cout << "|==============================================|" << endl;
            cout << "| User Location: (" << currentUser.getCurrentLocation().getLatitude() << ", " << currentUser.getCurrentLocation().getLongitude() << ")" << endl;

            cout << "Updated Cab Location:" << endl;
            cout << "Cab ID: " << currentCab.getCabId() << ", Location: (" << currentCab.getCurrentLocation().getLatitude() << ", " << currentCab.getCurrentLocation().getLongitude() << ")" << endl;

            break;
        }

        case 4:
        {
            try
            {
                int userID = currentUser.getUserID();
                Location userLocation = currentUser.getCurrentLocation();
                double userLatitude = userLocation.getLatitude();
                double userLongitude = userLocation.getLongitude();
                int currentCabID = currentUser.getCurrentTripID();

                cout << "+----------------------------------------+" << endl;
                cout << "| User ID: " << userID << endl;
                cout << "| User Location: (" << userLatitude << ", " << userLongitude << ")" << endl;
                cout << "| Currently Booked CabID: " << currentCabID << endl;
                cout << "+----------------------------------------+" << endl;
            }
            catch (const std::exception &e)
            {
                cerr << "Error: " << e.what() << endl;
            }
        }

        case 5:
            cout << "Exiting the program. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please enter a valid option.\n";
            break;
        }
    } while (choice != 5);
}
