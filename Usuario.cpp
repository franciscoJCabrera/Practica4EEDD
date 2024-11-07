//
// Created by Francisco Jose on 30/09/2024.
//

#include "Usuario.h"

///Constructor por defecto
Usuario::Usuario() {
    this->nif = "";
    this->clave = "";
    this->nombre = "";
    this->direccion = "";
}

///Constructor parametrizado
Usuario::Usuario(std::string nif2, std::string clave2, std::string nombre2, std::string direccion2, Coche *coche2) {
    this->nif = nif2;
    this->clave = clave2;
    this->nombre = nombre2;
    this->direccion = direccion2;
    this->cocheAlquilado = coche2;
}

///Constructor parametrizado sobrecargado
Usuario::Usuario(std::string nif2, std::string clave2, std::string nombre2, std::string direccion2) {
    this->nif = nif2;
    this->clave = clave2;
    this->nombre = nombre2;
    this->direccion = direccion2;
}

///Constructor copia
Usuario::Usuario(const Usuario &origen) {
    this->nif = origen.nif;
    this->clave =origen.clave;
    this->nombre = origen.nombre;
    this->direccion = origen.direccion;
    this->cocheAlquilado = origen.cocheAlquilado;
}

///Destructor
Usuario::~Usuario() {

}

///Metodo para asignar un Coche a un Usuario
void Usuario::setCoche(Coche *c) {
    this->cocheAlquilado = c;
}

///Getter y Setter de los atributos
const string &Usuario::getNif() const {
    return nif;
}

void Usuario::setNif(const string &nif) {
    Usuario::nif = nif;
}

const string &Usuario::getClave() const {
    return clave;
}

void Usuario::setClave(const string &clave) {
    Usuario::clave = clave;
}

const string &Usuario::getNombre() const {
    return nombre;
}

void Usuario::setNombre(const string &nombre) {
    Usuario::nombre = nombre;
}

const string &Usuario::getDireccion() const {
    return direccion;
}

void Usuario::setDireccion(const string &direccion) {
    Usuario::direccion = direccion;
}

Coche *Usuario::getCocheAlquilado() const {
    return cocheAlquilado;
}

///Metodo que solicita un coche
Coche *Usuario::cogeCoche() {
    Coche *cocheUtilizar = linkReanel->alquila(this);
    return cocheUtilizar;
}

///Metodo que crea un nuevo proyecto
void Usuario::crearTrayecto(PuntoRecarga *puntoOrigen, PuntoRecarga *puntoDestino, Fecha fIni, Fecha fFin) {
    ///Se crea el nuevo trayecto partiendo del punto de origen y del de destino
    Trayecto trayecto(puntoOrigen, puntoDestino, fIni, fFin);
    Coche *cocheTrayecto = iniciaTrayecto(puntoOrigen->getId(), puntoDestino->getId(), fIni, fFin);
    trayecto.setInTheCar(cocheTrayecto);
}

///Metodo que inicia un nuevo trayecto
Coche *Usuario::iniciaTrayecto(int idPuntoInicio, int idPuntoFinal, Fecha fIni, Fecha fFin) {
    ///Con alquilar estamos obteniendo el coche que mas bateria tiene
    Coche *c1 = linkReanel->alquilar(this, idPuntoInicio, idPuntoFinal, fIni, fFin);
    PuntoRecarga *p1 = c1->getCocheCargando();

    ///El PROrigen es el dado por reanelarcar::alquila()
    Coche *c2 = linkReanel->alquila(this);
    PuntoRecarga *p2 = c2->getCocheCargando();

    ///Creamos el proyecto
    crearTrayecto(p2, p1, fIni, fFin);


    ///TODO: Me he quedado en esta parte, acabar funcionalidad
    multimap<Fecha,Trayecto>::iterator iterator1 = rutas.begin();
    while (iterator1 != rutas.end()){
        ///Buscar hasta que la FechaInicio == Fecha (clave)
        ///Llamamos a Trayecto::addCoche() pasandole el coche asociado
        iterator1->second.getDestino()->addCoche(c1);

    }

    ///Devolvemos el coche que el usuario utilizara, sera el que mas bateria tenga
    return c1;
}

///Metodo que aparca el coche en un PR
void Usuario::aparcaCoche(Coche *c, PuntoRecarga *pr) {
    if (cocheAlquilado != nullptr){
        ///Colocamos el coche en el punto de recarga
        linkReanel->colocarCochePR(c,pr);
        ///Al colocarlo en el PR se elimina la asociacion entre usuario y el coche alquilado
        cocheAlquilado = nullptr;
    }
}

///Metodo que obtiene todos los trayectos realizados en una fecha dada
vector<Trayecto>* Usuario::getTrayectosFecha(Fecha f) {
    vector<Trayecto>* vectorDevolver;
    ///Obtenemos un par de iteradores para el rango de la fecha indicada
    pair<multimap<Fecha,Trayecto>::iterator, multimap<Fecha,Trayecto>::iterator> rango = rutas.equal_range(f);

    ///Creamos un nuevo iterador, situandolo en el inicio del rango
    multimap<Fecha,Trayecto>::iterator iteraFor = rango.first;

    while (iteraFor != rango.second){
        ///Insertamos el trayecto en el vector
        vectorDevolver->push_back(iteraFor->second);
        iteraFor++;
    }

    return vectorDevolver;
}
