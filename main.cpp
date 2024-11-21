#include "Reanelcar.h"
#include <iostream>

using namespace std;

/**
 * @Author Francisco José Cabrera Bermejo (fjcb0015)
 */

///TODO: Arreglar busqueda en la lista
///TODO: ¿Como puede tardar mas con vector que con la lista?


using namespace std;

int main(int argc, const char * argv[]) {

    cout << "--PRACTICA 5. TABLA HASH--" << endl;
    cout << "--Programa de prueba 1. Ajuste de la tabla hash--" << endl;

    ///Precargamos los datos del fichero y mostramos el estado interno de la tabla
    Reanelcar reanelcar("../coches_v2.csv", "../puntos_recarga.csv", "../usuarios1.csv");

    cout << "Ficheros cargados" << endl;
    cout << endl;

    cout <<"--Estado interno de la tabla--" << endl;
    reanelcar.mostrarEstadoTablaHash();
    cout << endl;

    ///Se buscan todos los usuarios con nombre empezado por W y lo metemos en un vector
    cout << "--Busqueda de todos los usuarios que empiezan por W--" << endl;
    list<Usuario> *listaW = reanelcar.buscarUsrNombre("W");
    list<Usuario>::iterator iteraW = listaW->begin();

    vector<string> nifUsuariosW;

    int contador = 0;
    while (iteraW != listaW->end()){

        cout << "Usuario " << contador << ": " <<  iteraW->getNif() << ", " << iteraW->getNombre() << endl;
        nifUsuariosW.push_back(iteraW->getNif());
        cout << "NIF insertado" << endl;
        cout << endl;

        contador++;
        iteraW++;
    }
    cout << endl;

    ///Buscamos las claves gracias al vector
    cout << "--Busqueda de las claves gracias al vector de nifs--" << endl;
    clock_t inicioVector= clock();
    for (int i = 0; i < nifUsuariosW.size(); ++i) {
        Usuario *usuarioW = reanelcar.buscarUsuarioNIFTablaHash(nifUsuariosW.operator[](i));
        cout << "Usuario " << i << ": " << usuarioW->getNif() << " que concuerda con el nif que buscabamos que es: " << nifUsuariosW.operator[](i) << endl;
    }
    clock_t finVector = clock();
    double tiempoVector = static_cast<double>(finVector - inicioVector) / CLOCKS_PER_SEC;
    cout << "Tiempo que tarda en buscar con el vector: " << tiempoVector << endl;
    cout << endl;

    ///Buscamos las claves gracias a la lista
    cout << "--Busqueda mediante la lista--" << endl;
    clock_t inicioLista= clock();

    for (int i = 0; i < nifUsuariosW.size(); ++i) {
        ///Booleano para comprobar si se ha encontrado el usuario de dicho nif
        bool encontrado = false;
        iteraW = listaW->begin();

        ///Hacemos la busqueda de dicho nif en la lista
        while (!encontrado){
            if (iteraW->getNif() == nifUsuariosW.operator[](i)){
                encontrado = true;
                cout << "Usuario " << i << " encontrado en lista: " << iteraW->getNif() << ", " << iteraW->getNombre() << endl;
            }
            iteraW++;
        }
    }

    clock_t finLista = clock();
    double tiempoLista = static_cast<double>(finLista - inicioLista) / CLOCKS_PER_SEC;
    cout << "Tiempo que tarda en buscar con la lista: " << tiempoLista << endl;
    cout << endl;

    cout << "--Programa de prueba 2--" << endl;
    cout << endl;





    return 0;
}
