//
// Created by Francisco Jose on 30/09/2024.
//

#ifndef PRACTICA4_REANELCAR_H
#define PRACTICA4_REANELCAR_H


#include "Coche.h"
#include "PuntoRecarga.h"
#include "Usuario.h"
#include "fecha.h"
#include <iostream>

#include <vector>
#include <map>
#include <list>

#include <cstdlib>


class Usuario;

using namespace std;

class Reanelcar {

    private:
        map<string,Coche> coches;   ///La clave es la matricula
        list<Usuario> usuarios; ///Los usuarios son insertados en una lista
        vector<PuntoRecarga> sitiosPuntoRecarga;    ///En este caso es solo un punto de recarga

        /**
         * Metodo que busca un punto de recarga dado un id
         * @param id
         * @return
         */
        PuntoRecarga* buscarPuntoRecarga(int id);

    public:

        /**
         * Constructor por defecto
         * Se va a hacer la lectura de los CSV
         */
        Reanelcar(string nCoches, string nPR, string nUsuarios);

        /**
         * Constructor
         */
        ~Reanelcar();

        /**
         * Metodo que busca un usuario pasado un NIF
         * En caso de no existir devolver null
         * @param nif
         * @return
         */
        Usuario* buscarUsrNif(string nif);

        /**
         * Metodo que devuelve una lista doblemente enlazada con todos los usuarios dado un nombre
         * Si pasas "Man" devolvera todas las palabras que empiecen por esa subcadena como Manolo, Mandy ...
         * @param nombre
         * @return
         */
        list<Usuario>* buscarUsrNombre(string nombre);

        /**
         * Metodo que busca un Coche dada una matricula
         * En caso de no existir devuelve nulo
         * @param matricula
         * @return
         */
        Coche* buscarCocheMatricula(string matricula);

        /**
         * Metodo que devuelve un vector con todos los coches de un modelo indicado
         * @param modelo
         * @return
         */
        vector<Coche>* buscarCocheModelo(string modelo);

        /**
         * Metodo que enlaza un Usuario a un Coche que alquila
         * @param u
         * @param c
         * @return
         */
        Coche* alquilar(Usuario *u, int idPROrigen, int idPRDestino, Fecha fIni, Fecha fFin);

        /**
         * Busca el coche con mayor bateria disponible en el punto de recarga y lo devuelve
         * El coche con mayor bateria es indicado por puntoRecarga::getMaxBateria()
         * @param usr
         * @return
         */
        Coche* alquila(Usuario *usr);

        /**
         * Metodo que añade el coche indicado al Punto de Recarga
         * Es realizado mediante el metodo puntoRecarga::addCoche()
         * @param c
         */
        bool colocarCochePR(Coche *c, PuntoRecarga *pr);

        /**
         * Metodo que recorre el arbol con el metodo inorden y devuelve un VDinamico con las matriculas ordenadas
         * @return
         */
        //vector<Coche*> primerasMatriculas();

        /**
         * Metodo que te muestra la altura del AVL que almacena todos los Coches
         * @return
         */
        //int alturaAVL();



        /**
         * Metodo que busca el Punto de Recarga con menos coches
         * @return
         */
        PuntoRecarga* obtenerPRMenosCoches();

        void distribuirCoches();


};


#endif //PRACTICA4_REANELCAR_H
