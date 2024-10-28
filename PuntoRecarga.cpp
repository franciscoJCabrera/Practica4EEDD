//
// Created by Francisco Jose on 14/10/2024.
//

#include "PuntoRecarga.h"

///Constructor por defecto
PuntoRecarga::PuntoRecarga(unsigned int max) {

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
    multimap<float, Coche*>::iterator itera = cochesAparcados.begin();
    Coche *cocheMayorBateria = itera->second;

    while (itera != cochesAparcados.end()){
        if (itera->second->getNivelBateria() > cocheMayorBateria->getNivelBateria()){
            cocheMayorBateria = itera->second;
        }
        itera++;
    }

    return cocheMayorBateria;
}

///Metodo que nos indica si se puede añadir un nuevo coche al punto de recarga
bool PuntoRecarga::addCoche(Coche *c) {
    ///Comprobamos si hay hueco en el Punto de Recarga
    if (cochesAparcados.size() < max){
        cochesAparcados.insert(make_pair(c->getNivelBateria(), c));
        return true;
    }else{
        ///No caben coches, por lo que devolvemos false
        return false;
    }
}

///Metodo que quita el coche de la estacion de carga
bool PuntoRecarga::quitarCoche(Coche *c) {
    multimap<float, Coche*>::iterator itera = cochesAparcados.find(c->getNivelBateria());
    if (itera != cochesAparcados.end()){
        ///El coche ha sido encontrado
        ///Para borrar un objeto le pasamos la posicion indicada por el iterador
        cochesAparcados.erase(itera);
        return true;
    }else{
        ///El coche no ha sido encontrado
        return false;
    }
}

///Metodo que devuelve la cantidad de elementos del multimap
int PuntoRecarga::getNumCoches() {
    return cochesAparcados.size();
}

