//
// Created by Francisco Jose on 14/10/2024.
//

#include "PuntoRecarga.h"
#include "Coche.h"

///Constructor parametrizado, pasandole solamente el id
PuntoRecarga::PuntoRecarga(int id) {
    this->id = id;
}

PuntoRecarga::PuntoRecarga(int id, int max) {
    this->id = id;
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

    Coche *coche;
    if (cochesAparcados.empty()){
        ///Si la estructura esta vacia entonces devuelve nullptr
        return nullptr;
    } else{
        ///En caso contrario, devuelve el coche con mayor bateria, el que esta arriba del todo
        coche = cochesAparcados.top();
    }

    return coche;
}

///Metodo que nos indica si se puede añadir un nuevo coche al punto de recarga
bool PuntoRecarga::addCoche(Coche *c) {
    ///Comprobamos si hay hueco en el Punto de Recarga
    if (cochesAparcados.size() < max){
        cochesAparcados.push(c);
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

    priority_queue<Coche*> colaTemporal;
    bool encontrado = false;

    ///Recorremos toda la EEDD hasta que este vacia
    while (!cochesAparcados.empty()){

        ///Sacamos el coche de la EEDD
        Coche *coche = cochesAparcados.top();
        cochesAparcados.pop();

        ///Comprobamos si el coche sacado coincide con el pasado como parametro
        if (coche == c){
            encontrado = true;
        }else{
            colaTemporal.push(coche);
        }
    }

    ///Restauramos la cola original
    cochesAparcados = std::move(colaTemporal);

    ///Devolvemos el resultado de la busqueda
    return encontrado;

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

