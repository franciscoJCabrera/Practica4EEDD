//
// Created by Francisco Jose on 14/10/2024.
//

#include "PuntoRecarga.h"

///Constructor parametrizado, pasandole solamente el id
PuntoRecarga::PuntoRecarga(int id) {
    this->id = id;
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
    multimap<int, Coche*>::iterator itera = cochesAparcados.begin();
    Coche *cocheMayorBateria = itera->second;

    ///Recorremos toda la EEDD hasta que encontremos el de mayor bateria
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
        ///Al añadir un nuevo coche, la cantidad de coches maximos permitidos disminuye en 1
        ///Al añadir un coche en el PR, debemos de actualizar tambien la asociacion en la clase Coche
        c->aparcar(this);
        return true;
    }else{
        ///No caben coches, por lo que devolvemos false
        return false;
    }
}

///Metodo que quita el coche de la estacion de carga
bool PuntoRecarga::deleteCoche(Coche *c) {
    multimap<int, Coche*>::iterator itera = cochesAparcados.find(c->getNivelBateria());
    if (itera != cochesAparcados.end()){
        ///El coche ha sido encontrado
        ///Para borrar un objeto le pasamos la posicion indicada por el iterador
        cochesAparcados.erase(itera);
        ///Al quitar un coche del punto de recarga, el maximo aumenta en 1
        return true;
    }else{
        ///El coche no ha sido encontrado
        return false;
    }
}

///Metodo que devuelve la cantidad de elementos del multimap
int PuntoRecarga::getNumCoches() {
    int cantidadCoches = cochesAparcados.size();
    return cantidadCoches;
}

///Getter y Setter
int PuntoRecarga::getId() const {
    return id;
}

void PuntoRecarga::setId(int id) {
    PuntoRecarga::id = id;
}

int PuntoRecarga::getMax() const {
    return max;
}

void PuntoRecarga::setMax(int max) {
    PuntoRecarga::max = max;
}

const UTM &PuntoRecarga::getPosicion() const {
    return posicion;
}

void PuntoRecarga::setPosicion(const UTM &posicion) {
    PuntoRecarga::posicion = posicion;
}

