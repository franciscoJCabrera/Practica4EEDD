#include "Reanelcar.h"
#include <iostream>

using namespace std;

/**
 * @Author Francisco José Cabrera Bermejo (fjcb0015)
 */

///TODO: Usuario::aparcaCoche() solamente se le tiene que quitar los puntos de retraso?


int main(int argc, const char * argv[]) {

    cout << "--PRACTICA 5. TABLA HASH--" << endl;

    ///Precargamos los datos del fichero y mostramos el estado interno de la tabla
    Reanelcar reanelcar("../coches_v2.csv", "../puntos_recarga.csv", "../usuarios1.csv");

    cout << "Ficheros cargados" << endl;
    cout << endl;

    cout <<"--Estado interno de la tabla--" << endl;
    reanelcar.mostrarEstadoTablaHash();
    cout << endl;

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

    cout << "--Busqueda de las claves gracias al vector de nifs--" << endl;
    clock_t inicio= clock();
    for (int i = 0; i < nifUsuariosW.size(); ++i) {
        Usuario *usuarioW = reanelcar.buscarUsuarioNIFTablaHash(nifUsuariosW.operator[](i));
        cout << "Usuario " << i << ": " << usuarioW->getNif() << " que concuerda con el nif que buscabamos que es: " << nifUsuariosW.operator[](i) << endl;
    }
    clock_t fin = clock();
    double tiempoVector = static_cast<double>(fin - inicio) / CLOCKS_PER_SEC;
    cout << "Tiempo que tarda en buscar con el vector: " << tiempoVector << endl;





    return 0;
}
