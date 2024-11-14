//
// Created by Francisco Jose on 23/09/2024.
//

#ifndef PRACTICA5_COCHE_H
#define PRACTICA5_COCHE_H

#include <string>
#include "PuntoRecarga.h"

using namespace std;

class PuntoRecarga;

class Coche {

private:

    string matricula;
    string marca;
    string modelo;
    int nivelBateria;
    PuntoRecarga *cocheCargando;

public:

    /**
     * Constructor por defecto
     */
    Coche();

    /**
     * Constructor parametrizado, se le pasan todos los atributos para crear el objeto
     * @param matricula1
     * @param marca1
     * @param modelo1
     */
    Coche(string matricula1, string marca1, string modelo1, int nivelBateria1);

    /**
     * Constructor copia, se le pasa un objeto para tomar los atributos
     * @param origen
     */
    Coche(const Coche &origen);

    /**
     * Destructor
     */
    virtual ~Coche();

    ///Get y Set de los diferentes atributos
    const string &getMatricula() const ;
    void setMatricula(const string &matricula);

    const string &getMarca() const ;
    void setMarca(const string &marca);

    const string &getModelo() const ;
    void setModelo(const string &modelo);

    const int &getNivelBateria() const ;
    void setNivelBateria(const int &bateria);

    PuntoRecarga *getCocheCargando() const;
    void setCocheCargando(PuntoRecarga *cocheCargando);

    ///Operadores necesarios para poder comparar coches
    bool operator==(const Coche &c) const ;
    bool operator!=(const Coche &c) const ;
    bool operator<(const Coche &c) const ;
    bool operator>(const Coche &c) const ;
    bool operator<=(const Coche &c) const ;
    bool operator>=(const Coche &c) const ;

    /**
     * Metodo que pone a circular el coche alquilado, por lo que lo quita del punto de recarga
     */
    void circular();

    /**
     * Metodo que pone el coche a cargar
     * Se realiza la asociacion entre el coche y el punto de recarga
     * @param pr
     * @return
     */
    bool aparcar(PuntoRecarga *pr);



};


#endif //PRACTICA5_COCHE_H
