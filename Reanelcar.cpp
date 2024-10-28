//
// Created by Francisco Jose on 30/09/2024.
//

#include <fstream>
#include <sstream>

#include "Reanelcar.h"

///Constructor por defecto + lectura de CSV
Reanelcar::Reanelcar(): usuarios(), coches(), sitiosPuntoRecarga(){

    ///Lectura de los Coches y lo insertamos en un AVL
    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;

    std::string id_matricula = "";
    std::string marca="";
    std::string modelo="";


    is.open("../coches_v2.csv"); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_matricula;marca;modelo;

                getline(columnas, id_matricula, ','); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, marca,',');
                getline(columnas, modelo,',');


                fila="";
                columnas.clear();

                ///Inicializamos el coche con una bateria entre el 20% y el 100%
                int randNum = rand()%(100-20 + 1) + 20;
                Coche coche(id_matricula, marca, modelo, randNum);

                try{
                    ///Al insertar el nuevo dato se gestiona automaticamente
                    coches.insert(pair<string,Coche>(coche.getMatricula(),coche));
                } catch(bad_alloc &e){
                    cout<<"Error al intentar insertar los coches: " << e.what() << endl;
                }

            }
        }

        is.close();


        //std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error al abrir el fichero de coches.csv" << std::endl;
    }

    ///Lectura de los Usuarios para insertarlos en la lista doblemente enlazada
    std::string nif = "";
    std::string clave="";
    std::string nombre="";
    std::string direccion="";
    Coche *cocheAlquilado = nullptr;


    is.open("../usuarios1.csv"); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_matricula;marca;modelo;

                getline(columnas, nif, ','); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, clave,',');
                getline(columnas, nombre,',');
                getline(columnas, direccion,',');


                fila="";
                columnas.clear();

                Usuario usuario(nif, clave, nombre, direccion, cocheAlquilado);

                try{
                    usuarios.insertarFinal(usuario);
                } catch(bad_alloc &e){
                    cout<<"Error al intentar insertar los usuarios: " << e.what() << endl;
                }

            }
        }

        is.close();

        //cout << "Todos los coches han sido insertados, la altura del AVL es -> " << alturaAVL() << endl;

        //std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error al abrir el fichero de usuarios1.csv" << std::endl;
    }
}

///Destructor
Reanelcar::~Reanelcar() {

}

///Busqueda de Usuario dado un NIF
Usuario *Reanelcar::buscarUsrNif(string nif) {
    ///Obtenemos el iterador
    ListaDEnlazada<Usuario>::Iterador iterador = usuarios.iteradorInicio();
    while (iterador.haySiguiente()){
        ///Guardamos el usuario para comprobar si es el del NIF pasado
        Usuario &usuario = iterador.dato();
        if (usuario.getNif() == nif){
            return &usuario;
        }
        iterador.siguiente();
    }
    ///En caso de no encontrar el Usuario devolvemos nullptr
    return nullptr;
}

///Busqueda de Usuarios dado un nombre
ListaDEnlazada<Usuario>* Reanelcar::buscarUsrNombre(string nombre) {
    ListaDEnlazada<Usuario> *listaUsuarios = new ListaDEnlazada<Usuario>;  ///Lista que vamos a devolver
    ListaDEnlazada<Usuario>::Iterador iterador = usuarios.iteradorInicio();
    while (iterador.haySiguiente()){
        Usuario usuario = iterador.dato();
        ///Obtenemos el nombre del usuario para comprobar si empieza por la subcadena indicada por parametro
        string nombreUsuario = usuario.getNombre();
        if (nombreUsuario.find(nombre) == 0){   ///find() devuelve 0 si la subcadena se encuentra al inicio del nombre de este Usuario
            listaUsuarios->insertarFinal(usuario);
        }
        iterador.siguiente();
    }
    return listaUsuarios;
}

///Busqueda de un Coche dada una matricula
Coche* Reanelcar::buscarCocheMatricula(string matricula) {
    Coche coche;
    coche.setMatricula(matricula);
    Coche *cocheEncontrado = coches.buscaIt(coche);
    if (cocheEncontrado == nullptr){
        return nullptr;
    }else{
        return cocheEncontrado;
    }
}

///Busqueda de Coches dado un modelo
VDinamico<Coche>* Reanelcar::buscarCocheModelo(string modelo) {
    VDinamico<Coche> *cochesEncontrados = new VDinamico<Coche>;
    Coche coche;
    coche.setModelo(modelo);
//    for (int i = 0; i < coches.tamLog(); ++i) {
//        if (coches.operator[](i).getModelo() == coche.getModelo()){
//            vectorCoches->insertar(coches.operator[](i));
//        }
//    }
    VDinamico<Coche*> cochesAVL = coches.recorreInorden();
    for (int i = 0; i < cochesAVL.tamLog(); ++i) {
        if (cochesAVL.operator[](i)->getModelo() == coche.getModelo()){
            cochesEncontrados->insertar(*cochesAVL.operator[](i));
        }
    }


    return cochesEncontrados;
}

///Metodo que relaciona un Usuario con un Coche
bool Reanelcar::alquilar(Usuario *u, Coche *c) {
    if (u->getCocheAlquilado() == nullptr){
        ///Si el Usuario pasado no tiene ningun coche alquilado se lo asociamos
        u->setCoche(c);
        return true;
    } else{
        return false;
    }
}

///Metodo que busca el coche con maxima bateria
Coche *Reanelcar::alquila(Usuario *usr) {
    Coche *cocheAlquilar = sitiosPuntoRecarga.getMaxBateria();
    alquilar(usr, cocheAlquilar);
    return usr->getCocheAlquilado();
}

///Metodo que coloca un coche en el punto de recarga
void Reanelcar::colocarCochePR(Coche *c) {
    sitiosPuntoRecarga.addCoche(c);
}

///Metodo que nos devuelve el AVL
VDinamico<Coche*> Reanelcar::primerasMatriculas() {
    VDinamico<Coche*> milCoches = coches.recorreInorden();
    return milCoches;
}

///Metodo que devuelve la altura del AVL
int Reanelcar::alturaAVL() {
    int altura = coches.altura();
    return altura;
}


