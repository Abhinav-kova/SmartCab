// Location.cpp
#include "Location.h"

Location::Location() : latitude(0.0), longitude(0.0) {}
Location::Location(double lat, double lon) : latitude(lat), longitude(lon) {}

double Location::getLatitude() const {
    return latitude;
}

double Location::getLongitude() const {
    return longitude;
}

void Location::setLocation(double lat, double lon) {
    latitude = lat;
    longitude = lon;
}

void Location::updateLatitude(double lat) {
    latitude = lat;
}

void Location::updateLongitude(double lon) {
    longitude = lon;
}