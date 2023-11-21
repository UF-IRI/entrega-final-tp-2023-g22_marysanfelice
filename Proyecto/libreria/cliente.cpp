#include "cliente.h"
#include "gym.h"
#define std::string str

eCodArchivos leerClientes(Cliente* clientes,ifstream& Archi){
    Archi.clear();
    Archi.seekg(0);
    str header;
    getline(Archi, header);
    Cliente* aux = clientes;
    str line;
    while (getline(Archi,line)) {
        char delim = ',';
        str idCliente, nombre, apellido, email, telefono, fechaNac, estado;
        istringstream iss(line);
        getline(iss, idCliente, delim);
        getline(iss, nombre, delim);
        getline(iss, apellido, delim);
        getline(iss, email, delim);
        getline(iss, telefono, delim);
        getline(iss, fechaNac, delim);
        getline(iss, estado, delim);
        aux->idCliente = idCliente;
        aux->nombre  = nombre;
        aux->email  = email;
        aux->apellido  = apellido;
        aux->telefono  = telefono;
        aux->fechaNac  = fechaNac;
        aux->estado  = estado;
        aux++;
    }
    return eCodArchivos::ExitoOperacion;
}

