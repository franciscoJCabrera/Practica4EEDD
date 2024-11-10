//
// Created by Francisco Jose on 28/10/2024.
//

#ifndef PRACTICA4_TRAYECTO_H
#define PRACTICA4_TRAYECTO_H

#include "fecha.h"
#include "Coche.h"

using namespace std;


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

    /**
     * Constructor por defecto
     */
    Trayecto();

    /**
     * Constructor parametrizado
     * @param PRO
     * @param PRD
     */
    Trayecto(int id,PuntoRecarga *PRO, PuntoRecarga *PRD, Fecha fIni, Fecha fFin);

    /**
     * Destructor
     */
    ~Trayecto();

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


#endif //PRACTICA4_TRAYECTO_H
