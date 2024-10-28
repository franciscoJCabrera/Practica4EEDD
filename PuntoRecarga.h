//
// Created by Francisco Jose on 14/10/2024.
//

#ifndef PRACTICA3_PUNTORECARGA_H
#define PRACTICA3_PUNTORECARGA_H

#include "Coche.h"
#include "VDinamico.h"
#include <vector>

using namespace std;

class Coche;

class PuntoRecarga {
    private:

        int id;
        int max;
        ///Tenemos una relacion de Asociacion con la clase Coche
        Coche* cochesAparcados[50];  ///El limite de coches aparcados lo indica el atributo max


        /**
         * Metodo que cuenta la cantidad de coches que se tiene en el momento actual en el Punto de Recarga
         * @return
         */
        int cochesEnPunto(){
            int n = 0;
            for (int i = 0; i < this->max; ++i) {
                if (cochesAparcados[i] != nullptr){
                    n++;
                }
            }
            return n;
        }

public:

        /**
         * Constructor por defecto
         * Se le pasa la cantidad de coches que cabe en el punto de recarga
         */
        PuntoRecarga(unsigned int max);

        /**
         * Destructor
         */
        ~PuntoRecarga();

        /**
         * Devuelve el coche con mayor cantidad de bateria
         * En caso de empate entre varios coches, cualquiera es valido
         * @return
         */
        Coche* getMaxBateria();

        /**
         * Añade un coche a un punto de recarga siempre que no se haya llegado al limite indicado por el valor max
         * @param c
         * @return
         */
        bool addCoche(Coche *c);

        /**
         * Quita un coche de la estacion de carga
         * @param c
         * @return True si se encuentra y False en caso contrario
         */
        bool quitarCoche(Coche *c);


};


#endif //PRACTICA3_PUNTORECARGA_H
