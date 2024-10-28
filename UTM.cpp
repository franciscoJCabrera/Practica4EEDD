//
// Created by spoti on 17/11/2023.
//

#include "UTM.h"

UTM::UTM(float latitud, float longitud) : latitud(latitud), longitud(longitud) {}

UTM::~UTM() {

}

float UTM::getLatitud() const {
    return latitud;
}

bool UTM::operator==(const UTM &rhs) const {
    return latitud == rhs.latitud &&
           longitud == rhs.longitud;
}

bool UTM::operator!=(const UTM &rhs) const {
    return !(rhs == *this);
}

void UTM::setLatitud(float latitud) {
    UTM::latitud = latitud;
}


float UTM::getLongitud() const {
    return longitud;
}

void UTM::setLongitud(float longitud) {
    UTM::longitud = longitud;
}

bool UTM::operator<(const UTM &rhs) const {
    if (latitud < rhs.latitud)
        return true;
    if (rhs.latitud < latitud)
        return false;
    return longitud < rhs.longitud;
}

bool UTM::operator>(const UTM &rhs) const {
    return rhs < *this;
}

bool UTM::operator<=(const UTM &rhs) const {
    return !(rhs < *this);
}

bool UTM::operator>=(const UTM &rhs) const {
    return !(*this < rhs);
}

UTM::UTM() {}
