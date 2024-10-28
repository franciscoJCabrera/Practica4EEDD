//
// Created by Francisco Jose on 28/10/2024.
//

#ifndef PRACTICA3_TRAYECTO_H
#define PRACTICA3_TRAYECTO_H

using namespace std;
#include "fecha.h"
#include "Coche.h"


class Trayecto {

private:
    int idTrayecto;
    Fecha fechaInicio;
    Fecha fechaFin;

    ///Relaciones con las demas clases
    Coche *inTheCar;
    PuntoRecarga *origen;
    PuntoRecarga *destino;

public:

    ///Setter y Getter
    int getIdTrayecto() const;
    void setIdTrayecto(int idTrayecto);

    const Fecha &getFechaInicio() const;
    void setFechaInicio(const Fecha &fechaInicio);

    const Fecha &getFechaFin() const;
    void setFechaFin(const Fecha &fechaFin);

    Coche *getInTheCar() const;
    void setInTheCar(Coche *inTheCar);

    PuntoRecarga *getOrigen() const;
    void setOrigen(PuntoRecarga *origen);

    PuntoRecarga *getDestino() const;
    void setDestino(PuntoRecarga *destino);

};


#endif //PRACTICA3_TRAYECTO_H
