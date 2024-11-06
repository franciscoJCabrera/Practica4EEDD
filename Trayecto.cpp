//
// Created by Francisco Jose on 28/10/2024.
//

#include "Trayecto.h"

///Constructor por defecto
Trayecto::Trayecto() {

}

///Constructor parametrizado
Trayecto::Trayecto(PuntoRecarga *PRO, PuntoRecarga *PRD, Fecha fIni, Fecha fFin) {
    this->fechaInicio = fIni;
    this->fechaFin = fFin;
    this->origen = PRO;
    this->destino = PRD;
}

///Destructor
Trayecto::~Trayecto() {

}


///Setter y Getter
int Trayecto::getIdTrayecto() const {
    return idTrayecto;
}

void Trayecto::setIdTrayecto(int idTrayecto) {
    Trayecto::idTrayecto = idTrayecto;
}

const Fecha &Trayecto::getFechaInicio() const {
    return fechaInicio;
}

void Trayecto::setFechaInicio(const Fecha &fechaInicio) {
    Trayecto::fechaInicio = fechaInicio;
}

const Fecha &Trayecto::getFechaFin() const {
    return fechaFin;
}

void Trayecto::setFechaFin(const Fecha &fechaFin) {
    Trayecto::fechaFin = fechaFin;
}

Coche *Trayecto::getInTheCar() const {
    return inTheCar;
}

void Trayecto::setInTheCar(Coche *inTheCar) {
    Trayecto::inTheCar = inTheCar;
}

PuntoRecarga *Trayecto::getOrigen() const {
    return origen;
}

void Trayecto::setOrigen(PuntoRecarga *origen) {
    Trayecto::origen = origen;
}

PuntoRecarga *Trayecto::getDestino() const {
    return destino;
}

void Trayecto::setDestino(PuntoRecarga *destino) {
    Trayecto::destino = destino;
}
