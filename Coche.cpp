//
// Created by Francisco Jose on 23/09/2024.
//

#include "Coche.h"
#include "PuntoRecarga.h"


///Constructor por defecto, lo inicializamos todos los atributos a vacio
Coche::Coche() {
    matricula = "";
    marca = "";
    modelo = "";
    nivelBateria = 100;
}

///Constructor parametrizado
Coche::Coche(string matricula1,string marca1,string modelo1, int bateria):
    matricula(matricula1),
    marca(marca1),
    modelo(modelo1),
    nivelBateria(bateria),
    cocheCargando(nullptr){
}

///Constructor copia
Coche::Coche(const Coche &origen) {
    this->matricula = origen.matricula;
    this->marca = origen.marca;
    this->modelo = origen.modelo;
    this->nivelBateria = origen.nivelBateria;
    this->cocheCargando = origen.cocheCargando;
}

///Destructor
Coche::~Coche() {

}


///Implementamos los Getter y Setter de los diferentes atributos de la clase
const string &Coche::getMatricula() const  {
    return matricula;
}

void Coche::setMatricula(const string &matricula) {
    Coche::matricula = matricula;
}

const string &Coche::getMarca() const  {
    return marca;
}

void Coche::setMarca(const string &marca) {
    Coche::marca = marca;
}

const string &Coche::getModelo() const  {
    return modelo;
}

void Coche::setModelo(const string &modelo) {
    Coche::modelo = modelo;
}

const int &Coche::getNivelBateria() const  {
    return nivelBateria;
}

void Coche::setNivelBateria(const int &bateria) {
    Coche::nivelBateria = bateria;
}

PuntoRecarga *Coche::getCocheCargando() const {
    return cocheCargando;
}

void Coche::setCocheCargando(PuntoRecarga *cocheCargando) {
    this->cocheCargando = cocheCargando;
}

///Implementamos los diferentes operadores para comparar coches
bool Coche::operator==(const Coche &c) const  {
    return matricula == c.matricula;
}

bool Coche::operator!=(const Coche &c) const  {
    if (c == *this){
        return false;
    }else {
        return true;
    }
}

bool Coche::operator<(const Coche &c) const  {
    //int matriculaA = stoi (matricula, nullptr,10);
    //int matriculaB = stoi (c.matricula,nullptr,10);
    return matricula < c.matricula;
}

bool Coche::operator>(const Coche &c) const  {
    return c < *this;
}

bool Coche::operator<=(const Coche &c) const  {
    return !(c < *this);
}

bool Coche::operator>=(const Coche &c) const  {
    return !(*this < c);
}

///Pone el coche en movimiento, por lo que lo quita del punto de carga
void Coche::circular() {
    ///Entender que cuando un coche empieza a circular abandona el PR en el que se encontraba
    ///al igual que cuando aparca, se guarda en un nuevo PR
    cocheCargando->deleteCoche(this);
    this->setCocheCargando(nullptr);
}

///Metodo que pone el coche a cargar, realizando la asociacion entre el coche y el PR
bool Coche::aparcar(PuntoRecarga *pr) {
    this->setCocheCargando(pr);
    return true;
}

const UTM &Coche::getPosicion() const {
    return posicion;
}

void Coche::setPosicion(const UTM &posicion) {
    Coche::posicion = posicion;
}

float Coche::getPosicionLong() {
    return posicion.getLongitud();
}

float Coche::getPosicionLat()  {
    return posicion.getLatitud();
}



