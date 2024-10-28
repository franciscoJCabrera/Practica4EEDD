//
// Created by Francisco Jose on 14/10/2024.
//

#include "PuntoRecarga.h"

///Constructor por defecto
PuntoRecarga::PuntoRecarga(unsigned int max) {
    ///Inicializamos el vector que almacena los coches aparcado a null
    for (int i = 0; i < max; ++i) {
        cochesAparcados[i] = nullptr;
    }
    this->max = max;
}

///Constructor parametrizado
PuntoRecarga::PuntoRecarga(int id2, int max2, UTM &posicion2) {
    this->id = id2;
    this->max = max2;
    this->posicion = posicion2;
}

///Destructor
PuntoRecarga::~PuntoRecarga() {

}

///Metodo que nos devuelve el coche con mayor bateria entre todos los que esta en el punto de recarga
Coche *PuntoRecarga::getMaxBateria() {
    Coche *cocheMayorBateria = nullptr;
    ///Buscamos el coche con mayor bateria
    for (int i = 0; i < max; ++i) {
        Coche *cocheActual = cochesAparcados[i];
        if (cocheActual != nullptr){
            if (cocheMayorBateria == nullptr || cocheMayorBateria->getNivelBateria() < cocheActual->getNivelBateria()){
                cocheMayorBateria = cocheActual;
            }
        }
    }
    return cocheMayorBateria;
}

///Metodo que nos indica si se puede añadir un nuevo coche al punto de recarga
bool PuntoRecarga::addCoche(Coche *c) {
    ///Si cabe, se inserta
    int cochesActuales = cochesEnPunto();
    if (cochesActuales < max){
        cochesAparcados[cochesActuales] = c;
        c->setCocheCargando(this);
        return true;
    }else{
        return false;
    }
}

///Metodo que quita el coche de la estacion de carga
bool PuntoRecarga::quitarCoche(Coche *c) {
    int n = cochesEnPunto();
    for (int i = 0; i < n; ++i) {
        if (cochesAparcados[i] == c){
            ///Encontramos el coche y lo quitamos de la estacion de carga
            c->setCocheCargando(nullptr);
            cochesAparcados[i] = nullptr;
            return true;
        }
    }
    return false;
}

