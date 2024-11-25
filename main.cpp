#include "Reanelcar.h"
#include <iostream>
#include <chrono>

using namespace std;

/**
 * @Author Francisco José Cabrera Bermejo (fjcb0015)
 */

///TODO: He metido UTM posicion como atributo en coche ¿Revisar constructores o algo mas?
///TODO: Implementar metodos nuevos en Reanelcar (buscarCochesRadio, buscarCocheMasCercano)
///TODO: Revisar tamaño pasado a la malla regular en el constructor de reanelcar

using namespace std;

int main(int argc, const char * argv[]) {

    cout << "--PRACTICA 6--" << endl;
    cout << endl;

    Reanelcar reanelcar("../coches_v2.csv", "../puntos_recarga.csv", "../usuarios1.csv");
    reanelcar.distribuirCoches();




    cout << "FIN" << endl;

    return 0;
}
