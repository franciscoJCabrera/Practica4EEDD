//
// Created by Francisco Jose on 12/11/2024.
//

#include "TablaHash.h"

///djb2
unsigned long int djb2(const string &str){
    unsigned long hash = 5381;

    for(int i = 0; i < str.length(); i++){
        hash=((hash << 5) + hash ) + str[i];
    }

    return hash;
}

///Metodo que comprueba si un numero es primo
bool esPrimo(int num, int div){
    if ( num % div == 0 ){
        return false;
    }else{
        if (div > sqrt(num)){
            return true;
        } else {
            return esPrimo(num,++div);
        }
    }
}

///Metodo por el cual se sabe el siguiente primo dado un numero por parametro
int siguientePrimo(int num){
    while(!esPrimo(num,2)){
        num++;
    }
    return num;
}


///Constructores
TablaHash::TablaHash(int maxElementos, float lambda): _tablaDispersion(siguientePrimo(maxElementos)/lambda), _lambda(lambda) {
    _tamTabla = _tablaDispersion.size();
}

TablaHash::TablaHash(const TablaHash &thash): _tablaDispersion(thash._tamTabla) {
    this->_tamTabla = thash._tamTabla;
    this->_factorCarga = thash._factorCarga;
    this->_promedioColisiones = thash._promedioColisiones;
    this->_numMax10 = thash._numMax10;
    this->_numElementosContenidos = thash._numElementosContenidos;

    for (int i = 0; i < _tamTabla; i++){
        this->_tablaDispersion.at(i) = thash._tablaDispersion.at(i);
    }
}

///Destructor
TablaHash::~TablaHash() {

}

///Sobrecargas de operadore
void TablaHash::operator=(const TablaHash &orig) {
    this->_tablaDispersion.resize(orig._tamTabla);
    for (int i = 0; i < orig._tamTabla; i++){
        this->_tablaDispersion.at(i) = orig._tablaDispersion.at(i);
    }

    this->_tamTabla = orig._tamTabla;
    this->_factorCarga = orig._factorCarga;
    this->_promedioColisiones = orig._promedioColisiones;
    this->_numMax10 = orig._numMax10;
    this->_numElementosContenidos = orig._numElementosContenidos;
}

///Getter y Setter
void TablaHash::setTablaDispersion(const vector<Entrada> &tablaDispersion) {
    _tablaDispersion = tablaDispersion;
}

int TablaHash::getNumElementosContenidos() const {
    return _numElementosContenidos;
}

void TablaHash::setNumElementosContenidos(int numElementosContenidos) {
    _numElementosContenidos = numElementosContenidos;
}

unsigned int TablaHash::getMaximoColisiones() const {
    return _maximoColisiones;
}

void TablaHash::setMaximoColisiones(unsigned int maximoColisiones) {
    _maximoColisiones = maximoColisiones;
}

unsigned int TablaHash::getNumMax10() const {
    return _numMax10;
}

void TablaHash::setNumMax10(unsigned int numMax10) {
    _numMax10 = numMax10;
}

float TablaHash::getPromedioColisiones() const {
    return _promedioColisiones;
}

void TablaHash::setPromedioColisiones(float promedioColisiones) {
    _promedioColisiones = promedioColisiones;
}

float TablaHash::getFactorCarga()  {
    return _factorCarga;
}

void TablaHash::setFactorCarga(float factorCarga) {
    _factorCarga = factorCarga;
}

unsigned int TablaHash::getTamTabla() const {
    return _tamTabla;
}

void TablaHash::setTamTabla(unsigned int tamTabla) {
    _tamTabla = tamTabla;
}

int TablaHash::getContadorRedispersion() const {
    return contadorRedispersion;
}

void TablaHash::setContadorRedispersion(int contadorRedispersion) {
    TablaHash::contadorRedispersion = contadorRedispersion;
}

void TablaHash::setLambda(float lambda) {
    _lambda = lambda;
}


///Metodos de ajuste y estadistica de la tabla
/**
 * @brief Metodo para obtener el numero maximo de colisiones que se han producido en la operacion de insercion mas costosa
 * @return unsigned int
 */
unsigned int TablaHash::maxColisiones() {
    return this->_maximoColisiones;
}

/**
 * @brief Devuelve el numero de veces que se superan 10 colisiones
 * @return unsigned int
 */
unsigned int TablaHash::numMax10() {
    return this->_numMax10;
}

/**
 * @brief Metodo para obtener el promedio de colisiones por operacion de insercion realizada sobre la tabla
 * @return unsigned int
 */
float TablaHash::promedioColisiones() {

    _promedioColisiones = ((float)_maximoColisiones/_tamTabla);
    return _promedioColisiones;
}
/**
 * @brief Metodo para obtener el factor de carga de la tabla de dispersion
 * @return float
 */
float TablaHash::factorCarga() {
    return _factorCarga;
}

/**
 * @brief Metodo para obtener el tamaño de la tabla de dispersion
 * @return unsigned int
 */
unsigned int TablaHash::tamTabla() {
    return _tablaDispersion.size();
}

void TablaHash::mostrarEstadoTabla() {
    cout << "***** ESTADO DE LA TABLA HASH CERRADA *****" << endl;
    cout << "   - Numero maximo de colisiones: " << this->_maximoColisiones << endl;
    cout << "   - Numero de veces que se han superado las 10 colisiones: " << this->_numMax10 << endl;
    cout << "   - Promedio de colisiones por operacion de insersion: " << this->_promedioColisiones << endl;
    cout << "   - Factor de carga: " << this->_factorCarga << endl;
    cout << "   - Tamaño de la tabla: " << this->_tamTabla << endl;
    cout << "   - Numero de redispersiones ocurridas: " << this->contadorRedispersion << endl;
    cout << "*******************************************" << endl;
}


///
bool TablaHash::insertar(unsigned long clave, string &claveUsuario, Usuario &Usuario) {
    int intento = 0;
    unsigned long posicion = 0;

    int contadorRedis = 0;

    while (true) {
        posicion = this->hashCuadratico(clave, intento);


        if ((this->_tablaDispersion[posicion]._estado == libre) || (this->_tablaDispersion[posicion]._estado == disponible)) {


            this->_tablaDispersion[posicion]._dato = aeropuerto;
            this->_tablaDispersion[posicion]._estado = ocupado;
            this->_tablaDispersion[posicion]._clave = clave;
            _numElementosContenidos++;

            float auxNumCont = this->getNumElementosContenidos();
            float auxTamTabla = this->getTamTabla();
            _factorCarga = auxNumCont / auxTamTabla;

            if (this->_factorCarga > _lambda) {
                contadorRedis++;
                this->contadorRedispersion = contadorRedis;
                this->redispersar(siguientePrimo(this->getTamTabla() + (this->getTamTabla() * 0.3)));
            }

            if (intento > _maximoColisiones) {
                _maximoColisiones = intento;
            }

            if (intento > 10) {
                _numMax10++;
            }

            _promedioColisiones = (float)this->_numColisiones / this->_numElementosContenidos;

            return true;
        } else {
            if (this->_tablaDispersion[posicion]._dato == aeropuerto) {
                return false;
            }
            _numColisiones++;
            _promedioColisiones = (float)this->_numColisiones / this->_numElementosContenidos;
            intento++;
        }
    }
}


///
bool TablaHash::buscar(unsigned long int clave,string &claveUsuario) {
    int _intento = 0;
    unsigned long _posEncontrar = 0;


    while (_intento < _tamTabla){

        _posEncontrar = hashCuadratico(clave, _intento);

        ///_tablaDispersion[_posEncontrar]._clave == clave &&
        if ( _tablaDispersion[_posEncontrar]._estado == ocupado || _tablaDispersion[_posEncontrar]._estado == disponible ) {
            if(_tablaDispersion[_posEncontrar]._dato.getIata() == id) {
                a = &(_tablaDispersion[_posEncontrar]._dato);
                return true;
            }
        }
        _intento++;

    }
    return false;
}


///
bool TablaHash::borrar(unsigned long clave,const string &claveBuscar) {
    int _intento = 0;
    unsigned long int _posBorrar = 0;

    while( _intento < _tamTabla ){
        _posBorrar = hashCuadratico(clave, _intento);
        if ( (_tablaDispersion[_posBorrar]._clave == clave) && (_tablaDispersion[_posBorrar]._estado == ocupado) && (_tablaDispersion[_posBorrar])._dato.getIata() == id ) {
            _tablaDispersion[_posBorrar] = Entrada();
            _numElementosContenidos--;
            _factorCarga = (float)_numElementosContenidos/_tamTabla;

            return true;
        } else {
            _intento++;
        }
    }
    return false;
}