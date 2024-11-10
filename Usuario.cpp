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
    this->cocheAlquilado = nullptr;
    this->linkReanel = nullptr;
}

///Constructor parametrizado
Usuario::Usuario(std::string nif2, std::string clave2, std::string nombre2, std::string direccion2, Coche *coche2) {
    this->nif = nif2;
    this->clave = clave2;
    this->nombre = nombre2;
    this->direccion = direccion2;
    this->cocheAlquilado = coche2;
    this->linkReanel = nullptr;
}

///Constructor parametrizado sobrecargado
Usuario::Usuario(std::string nif2, std::string clave2, std::string nombre2, std::string direccion2) {
    this->nif = nif2;
    this->clave = clave2;
    this->nombre = nombre2;
    this->direccion = direccion2;
    this->cocheAlquilado = nullptr;
    this->linkReanel = nullptr;
}

///Constructor copia
Usuario::Usuario(const Usuario &origen) {
    this->nif = origen.nif;
    this->clave =origen.clave;
    this->nombre = origen.nombre;
    this->direccion = origen.direccion;
    this->cocheAlquilado = origen.cocheAlquilado;
    this->linkReanel = origen.linkReanel;
    this->rutas = origen.rutas;
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
    Trayecto trayecto(this->trayectosRealizados(),puntoOrigen, puntoDestino, fIni, fFin);
    Coche *cocheTrayecto = iniciaTrayecto(puntoOrigen->getId(), puntoDestino->getId(), fIni, fFin);
    trayecto.setInTheCar(cocheTrayecto);
    ///Tenemos que insertar la nueva ruta en la EEDD
    rutas.insert(make_pair(fIni, trayecto));
}

///Metodo que inicia un nuevo trayecto
Coche *Usuario::iniciaTrayecto(int idPuntoInicio, int idPuntoFinal, Fecha fIni, Fecha fFin) {
    ///Con alquilar estamos obteniendo el coche que mas bateria tiene y el PR del que se obtiene dicho coche
    ///Cuando llamamos a alquilar, se le esta asociado el coche con mayor bateria al usuario
    ///Por lo que no hace falta asociarle el coche al usuario en ningun otro momento
    Coche *c1 = linkReanel->alquilar(this, idPuntoInicio, idPuntoFinal, fIni, fFin);
    PuntoRecarga *p1 = c1->getCocheCargando();

    ///El PRDestino tiene el id proporcionado
    PuntoRecarga destino(idPuntoFinal);

    ///Creamos el proyecto
    crearTrayecto(p1, &destino, fIni, fFin);

    multimap<Fecha,Trayecto>::iterator iterator1 = rutas.begin();
    while (iterator1 != rutas.end()){
        if (iterator1->first.mismoDia(fIni)){
            ///Le asociamos el coche al trayecto
            iterator1->second.setInTheCar(c1);
        }else{
            iterator1++;
        }
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
vector<Trayecto>* Usuario::getTrayectosFecha(const Fecha& f) {
    vector<Trayecto>* vectorDevolver;

    ///Buscamos todos los trayectos hechos en esa fecha
    multimap<Fecha,Trayecto>::iterator iteraTrayectos = rutas.find(f);

    while (iteraTrayectos->first == f){
        vectorDevolver->push_back(iteraTrayectos->second);
        iteraTrayectos++;
    }

    return vectorDevolver;
}

///Metodo que muestra la cantidad de trayectos realizados por un usuario
int Usuario::trayectosRealizados() {
    return rutas.size();
}

///Metodo para obtener un trayecto dada unas fechas y PR
Trayecto *Usuario::obtenerTrayecto(Fecha &fIni, Fecha &fFin, PuntoRecarga &PROrigen, PuntoRecarga &PRDestino) {
    multimap<Fecha,Trayecto>::iterator iteraTrayectos = rutas.begin();
    while (iteraTrayectos != rutas.end()){
        Trayecto &t = iteraTrayectos->second;
        PuntoRecarga *pOrigen = t.getOrigen();
        PuntoRecarga *pDestino = t.getDestino();
        if (t.getFechaInicio() == fIni && t.getFechaFin() == fFin){
            if (&PROrigen == pOrigen && &PRDestino == pDestino){
                return &t;
            }
        }
        iteraTrayectos++;
    }
    return nullptr;
}

Reanelcar *Usuario::getLinkReanel() const {
    return linkReanel;
}

void Usuario::setLinkReanel(Reanelcar *linkReanel) {
    Usuario::linkReanel = linkReanel;
}
