//
// Created by spoti on 17/11/2023.
//

#ifndef EXPERIMENTS_UTM_H
#define EXPERIMENTS_UTM_H
using namespace std;

class UTM {

private:

    float latitud = 0;
    float longitud = 0;

public:
    ///Constructores
    UTM(float latitud, float longitud);
    UTM();

    ///Destructor
    virtual ~UTM();

    ///Setters y Getters
    float getLatitud() const;
    void setLatitud(float latitud);
    float getLongitud() const;
    void setLongitud(float longitud);

    bool operator==(const UTM &rhs) const;

    bool operator!=(const UTM &rhs) const;

    bool operator<(const UTM &rhs) const;

    bool operator>(const UTM &rhs) const;

    bool operator<=(const UTM &rhs) const;

    bool operator>=(const UTM &rhs) const;
};


#endif //EXPERIMENTS_UTM_H
