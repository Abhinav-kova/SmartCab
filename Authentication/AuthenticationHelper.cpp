#include "AuthenticationHelper.h"

using namespace std;

int AuthenticationHelper::performAuthentication(AuthSystem &authSystem)
{
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    int userID = authSystem.authenticateUser(username, password);

    if (userID != -1)
    {
        cout << "Authentication successful. Access granted." << std::endl;
        return userID;
    }
    else
    {
        cout << "Authentication failed. Access denied." << std::endl;
        return -1;
    }
}
