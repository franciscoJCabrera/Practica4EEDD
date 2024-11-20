#include "Reanelcar.h"
#include <iostream>

using namespace std;

/**
 * @Author Francisco José Cabrera Bermejo (fjcb0015)
 */

///TODO: Implementar metodos nuevos en clase Reanelcar
///TODO: Implementar/Modificar metodos en clase Usuario (Modificar: aparcaCoche)
///TODO: En Reanelcar::borrarUsuarioTHash() borrar los trayectos tambien
///TODO: Revisar EEDD de la clase PuntoRecarga y errores que da
///TODO: Implementar lo necesario en clase Entrada en clase TablaHash.h


int main(int argc, const char * argv[]) {

    cout << "--PRACTICA 5. TABLA HASH--" << endl;

    ///Precargamos los datos del fichero y mostramos el estado interno de la tabla
    Reanelcar reanelcar("../coches_v2.csv", "../puntos_recarga.csv", "../usuarios1.csv");

    cout << "Ficheros cargados" << endl;
    cout << endl;

    cout <<"--Estado interno de la tabla--" << endl;
    reanelcar.getUsuariosTabla();




    return 0;
}
