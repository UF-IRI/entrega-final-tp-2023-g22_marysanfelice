#ifndef CLIENTE_H
#define CLIENTE_H

#include "encabezados.h"

struct cliente{
    str idCliente, nombre, apellido, email, telefono, fechaNac, estado;
};typedef struct cliente Cliente;

const Cliente ClienteNulo={"","","","","","",""};

eCodArchivos leerClientes(Cliente* clientes,ifstream& archivo);
bool chequearEstado(Cliente cliente);
//bool ExisteCliente(Cliente* cliente,uint cant, str id);

#endif // CLIENTE_H
