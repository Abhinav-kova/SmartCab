// Location.h
#ifndef LOCATION_H
#define LOCATION_H

class Location {
public:
    double latitude;
    double longitude;

    Location();
    Location(double lat, double lon);
    
    double getLatitude() const;
    double getLongitude() const;
    void setLocation(double lat, double lon);

    void updateLatitude(double lat);
    void updateLongitude(double lon);
};

#endif // LOCATION_H
