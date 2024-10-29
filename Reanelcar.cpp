//
// Created by Francisco Jose on 30/09/2024.
//

#include <fstream>
#include <sstream>

#include "Reanelcar.h"

///Constructor por defecto + lectura de CSV
Reanelcar::Reanelcar(): usuarios(), coches(), sitiosPuntoRecarga(){

    ///Lectura de los Coches y lo insertamos en un map
    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;

    std::string id_matricula = "";
    std::string marca="";
    std::string modelo="";
    std::string nivelBateria="";    ///Lo ponemos como string, mas tarde lo convertimos a int


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
                getline(columnas,nivelBateria, ',');

                ///Convertimos el string por el cual obteniamos el nivel de bateria a entero
                int bateria = std::stoi(nivelBateria);


                fila="";
                columnas.clear();

                Coche coche(id_matricula, marca, modelo, bateria);

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

    ///Lectura de los Usuarios para insertarlos en la lista
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
                    ///Insertamos los usuarios en nuestra lista
                    usuarios.push_back(usuario);
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

    ///Lectura de los Puntos de recarga para insertarlos en el vector
    std::string id = "";
    ///Latitud y Longitud forma un objeto de la clase UTM
    std::string latitud="";
    std::string longitud="";
    std::string maxCoches="";   ///Vamos a tener que convertirlo en un entero mas adelante

    is.open("../puntos_recarga.csv"); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_matricula;marca;modelo;

                getline(columnas, id, ','); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, latitud,',');
                getline(columnas, longitud,',');
                getline(columnas, maxCoches,',');

                ///Convertimos el string en entero
                int maximoCoches = std::stoi(maxCoches);
                int idPunto = std::stoi(id);

                ///Convertimos la latitud y longitud en float
                float latitudUTM = std::stof(latitud);
                float longitudUTM = std::stof(longitud);

                fila="";
                columnas.clear();

                ///Creamos el UTM y lo insertamos al Punto de Recarga
                UTM utmDato(latitudUTM, longitudUTM);
                PuntoRecarga punto(idPunto, maximoCoches, utmDato);

                try{
                    ///Insertamos los puntos de recarga en nuestro vector
                    sitiosPuntoRecarga.push_back(punto);
                } catch(bad_alloc &e){
                    cout<<"Error al intentar insertar los puntos de recarga: " << e.what() << endl;
                }

            }
        }

        is.close();

        //std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error al abrir el fichero de puntos_recarga.csv" << std::endl;
    }
}

///Destructor
Reanelcar::~Reanelcar() {

}

///Busqueda de Usuario dado un NIF
Usuario *Reanelcar::buscarUsrNif(string nif) {
    ///Obtenemos el iterador
    list<Usuario>::iterator iterador= usuarios.begin();
    while (iterador != usuarios.end()){
        ///Guardamos el usuario para comprobar si es el del NIF pasado
        Usuario &usuario = *iterador;
        if (usuario.getNif() == nif){
            return &usuario;
        }
        iterador++; ///Avanzamos el iterador
    }
    ///En caso de no encontrar el Usuario devolvemos nullptr
    return nullptr;
}

///Busqueda de Usuarios dado un nombre
list<Usuario>* Reanelcar::buscarUsrNombre(string nombre) {
    list<Usuario> *listaUsuarios;  ///Lista que vamos a devolver
    list<Usuario>::iterator iterador = usuarios.begin();
    while (iterador != usuarios.end()){
        Usuario usuario = *iterador;
        ///Obtenemos el nombre del usuario para comprobar si empieza por la subcadena indicada por parametro
        string nombreUsuario = usuario.getNombre();
        if (nombreUsuario.find(nombre) == 0){   ///find() devuelve 0 si la subcadena se encuentra al inicio del nombre de este Usuario
            listaUsuarios->push_back(usuario);
        }
        iterador++;
    }
    return listaUsuarios;
}

///Busqueda de un Coche dada una matricula
Coche* Reanelcar::buscarCocheMatricula(string matricula) {
    map<string,Coche>::iterator itera = coches.find(matricula);
    if (itera == coches.end()){
        return nullptr;
    }else{
        return &(itera->second);
    }
}

///Busqueda de Coches dado un modelo
vector<Coche>* Reanelcar::buscarCocheModelo(string modelo) {
    vector<Coche> *cochesEncontrados;
    map<string,Coche>::iterator itera = coches.begin();
    while (itera != coches.end()){
        if (itera->second.getModelo() == modelo){
            ///Al encontrar un coche de ese modelo lo insertamos en el vector a devolver
            cochesEncontrados->push_back(itera->second);
        }
        itera++;
    }
    return cochesEncontrados;
}

///Metodo que relaciona un Usuario con un Coche
Coche* Reanelcar::alquilar(Usuario *u, int idPROrigen, int idPRDestino) {

}

///Metodo que busca el coche con maxima bateria
Coche *Reanelcar::alquila(Usuario *usr) {

}

///Metodo que coloca un coche en el punto de recarga
bool Reanelcar::colocarCochePR(Coche *c, PuntoRecarga *pr) {
    if (pr->addCoche(c)){
        ///En caso de que se pueda añadir el coche pasado al punto de recarga indicado se devuelve true
        c->aparcar(pr);
        return true;
    } else{
        return false;
    }
}

///Metodo que busca un PR dado un ID. METODO PRIVADO
PuntoRecarga *Reanelcar::buscarPuntoRecarga(int id) {

    ///Si no tenemos Puntos de Recarga se devuelve null
    if (sitiosPuntoRecarga.empty()){
        return nullptr;
    }

    ///En otro caso, buscamos a ver si esta el PR con el id pasado
    PuntoRecarga *puntoDevolver = nullptr;
    for (int i = 0; i < sitiosPuntoRecarga.size(); ++i) {
        if (sitiosPuntoRecarga.operator[](i).getId() == id){
            puntoDevolver = &sitiosPuntoRecarga.operator[](i);
        }
    }

    return puntoDevolver;
}

///Metodo que obtiene el PR con menos coches de todos los que se tienen
PuntoRecarga *Reanelcar::obtenerPRMenosCoches() {
    ///En caso de que no haya puntos de recarga devolver nullptr
    if (sitiosPuntoRecarga.empty()){
        return nullptr;
    }

    ///En otro caso, buscamos el PR con menor cantidad de coches
    PuntoRecarga *puntoDevolver = nullptr;
    int cantidadCoches = 50;
    for (int i = 0; i < sitiosPuntoRecarga.size(); ++i) {
        if (sitiosPuntoRecarga.operator[](i).getNumCoches() < cantidadCoches){
            cantidadCoches = sitiosPuntoRecarga.operator[](i).getNumCoches();
            puntoDevolver = &sitiosPuntoRecarga.operator[](i);
        }
    }

    return puntoDevolver;
}

//Metodo que nos devuelve el AVL
//VDinamico<Coche*> Reanelcar::primerasMatriculas() {
//    VDinamico<Coche*> milCoches = coches.recorreInorden();
//    return milCoches;
//}

//Metodo que devuelve la altura del AVL
//int Reanelcar::alturaAVL() {
//    int altura = coches.altura();
//    return altura;
//}


