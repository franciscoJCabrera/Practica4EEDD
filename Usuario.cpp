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
    this->puntos = 100;
}

///Constructor parametrizado
Usuario::Usuario(std::string nif2, std::string clave2, std::string nombre2, std::string direccion2, Coche *coche2) {
    this->nif = nif2;
    this->clave = clave2;
    this->nombre = nombre2;
    this->direccion = direccion2;
    this->cocheAlquilado = coche2;
    this->linkReanel = nullptr;
    this->puntos = 100;
}

///Constructor parametrizado sobrecargado
Usuario::Usuario(std::string nif2, std::string clave2, std::string nombre2, std::string direccion2) {
    this->nif = nif2;
    this->clave = clave2;
    this->nombre = nombre2;
    this->direccion = direccion2;
    this->cocheAlquilado = nullptr;
    this->linkReanel = nullptr;
    this->puntos = 100;
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
    this->puntos = origen.puntos;
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

Reanelcar *Usuario::getLinkReanel() const {
    return linkReanel;
}

void Usuario::setLinkReanel(Reanelcar *linkReanel) {
    Usuario::linkReanel = linkReanel;
}

int Usuario::getPuntos() const {
    return puntos;
}

void Usuario::setPuntos(int puntos) {
    Usuario::puntos = puntos;
}

///Metodo que solicita un coche
Coche *Usuario::cogeCoche() {
    Coche *cocheUtilizar = linkReanel->alquila(this);
    return cocheUtilizar;
}

///Metodo que crea un nuevo proyecto
void Usuario::crearTrayecto(PuntoRecarga *puntoOrigen, PuntoRecarga *puntoDestino, Fecha fIni, Fecha fFin) {
    ///Se crea el nuevo trayecto partiendo del punto de origen y del de destino
    Trayecto *trayecto = new Trayecto(this->trayectosRealizados(),puntoOrigen, puntoDestino, fIni, fFin);

    ///Tenemos que insertar la nueva ruta en la EEDD
    rutas.insert(make_pair(fIni, trayecto));
}

///Metodo que inicia un nuevo trayecto
Coche *Usuario::iniciaTrayecto(int idPuntoInicio,int idPuntoFinal, Fecha fIni, Fecha fFin) {
    ///Con alquilar estamos obteniendo el coche que mas bateria tiene y el PR del que se obtiene dicho coche
    ///Cuando llamamos a alquilar, se le esta asociado el coche con mayor bateria al usuario
    ///Por lo que no hace falta asociarle el coche al usuario en ningun otro momento
    Coche *c1 = linkReanel->alquilar(this, idPuntoInicio, idPuntoFinal, fIni, fFin);
    PuntoRecarga *p1 = c1->getCocheCargando();

    ///El PRDestino tiene el id proporcionado
    PuntoRecarga *destino = linkReanel->obtenerPuntoRecarga(idPuntoFinal);

    ///Creamos el proyecto
    crearTrayecto(p1, destino, fIni, fFin);

    multimap<Fecha,Trayecto*>::iterator iteraTrayecto = rutas.find(fIni);
    if (iteraTrayecto != rutas.end() && iteraTrayecto->first.mismoDia(fIni)){
        iteraTrayecto->second->setInTheCar(c1);
    }

    ///Devolvemos el coche que el usuario utilizara, sera el que mas bateria tenga
    return c1;
}

///Metodo que aparca el coche en un PR
void Usuario::aparcaCoche(Coche *c, PuntoRecarga *pr, int retraso) {
    if (cocheAlquilado != nullptr){
        ///Se le quitan los puntos al usuario por el retraso que haya tenido
        decrementarPuntos(retraso);
        ///Colocamos el coche en el punto de recarga
        linkReanel->colocarCochePR(c,pr);
        ///Al colocarlo en el PR se elimina la asociacion entre usuario y el coche alquilado
        cocheAlquilado = nullptr;
    }
}

///Metodo que obtiene todos los trayectos realizados en una fecha dada
vector<Trayecto*>* Usuario::getTrayectosFecha(const Fecha& f) {
    vector<Trayecto*> *vectorDevolver = new vector<Trayecto*>();

    ///Buscamos todos los trayectos hechos en esa fecha
    multimap<Fecha,Trayecto*>::iterator iteraTrayectos = rutas.find(f);

    while (iteraTrayectos->first == f && iteraTrayectos != rutas.end()){
        vectorDevolver->push_back(iteraTrayectos->second);
        iteraTrayectos++;
    }
    return vectorDevolver;
}

///Metodo para buscar y asociar un PRDestino
bool Usuario::buscarPRDestinoAsociar(const Fecha& f, const Fecha& fFin, int idOrigen, int idDestino, PuntoRecarga *pDestino) {
    multimap<Fecha,Trayecto*>::iterator iteraTrayectos = rutas.begin();
    while (iteraTrayectos != rutas.end()){
        if (iteraTrayectos->first.mismoDia(f)) {
            if (iteraTrayectos->second->getFechaFin().mismoDia(fFin)) {
                if (iteraTrayectos->second->getOrigen()->getId() == idOrigen && iteraTrayectos->second->getDestino()->getId() == idDestino) {
                    iteraTrayectos->second->setDestino(pDestino);
                    return true;
                }
            }
        }
        iteraTrayectos++;
    }
    return false;
}

///Metodo que muestra la cantidad de trayectos realizados por un usuario
int Usuario::trayectosRealizados() {
    return rutas.size();
}

///Metodo que quita puntos dependiendo del retraso que tenga el usuario en horas
void Usuario::decrementarPuntos(int retraso) {
    ///Comprobamos que realmente el usuario ha tenido un retraso
    if (retraso > 0){
        ///Cada hora de retraso son 2 puntos de penalizacion
        int penalizacionAplicar = retraso * 2;
        this->puntos = this->puntos - penalizacionAplicar;
    }
}

///Metodo que borra todos los trayectos que tenia el usuario
void Usuario::eliminarTrayectos() {
    multimap<Fecha,Trayecto*>::iterator iteraTrayectos;

    ///Mientras que no este la estructura vacia vamos a estar borrando trayectos
    while (!rutas.empty()){
        iteraTrayectos = rutas.begin();
        ///Liberamos la memoria del objeto Trayecto
        delete iteraTrayectos->second;
        ///Eliminamos el elementos del multimap
        rutas.erase(iteraTrayectos);
    }
}

bool Usuario::operator==(const Usuario &rhs) const {
    return nif == rhs.nif &&
           clave == rhs.clave &&
           nombre == rhs.nombre &&
           direccion == rhs.direccion &&
           puntos == rhs.puntos &&
           cocheAlquilado == rhs.cocheAlquilado &&
           linkReanel == rhs.linkReanel &&
           rutas == rhs.rutas;
}

bool Usuario::operator!=(const Usuario &rhs) const {
    return !(rhs == *this);
}



