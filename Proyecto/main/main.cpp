#include "asistencia.h"
#include "cliente.h"
#include "gym.h"
#include <ctime>

int main() {
    ifstream archivoClientes("../../iriClientesGYM.csv");
    if (!archivoClientes.is_open()) {
        cout << "No se ha podido abrir el archivo Clientes" << endl;
        return 0;
    }
    ifstream archivoClases("../../iriClasesGYM.csv");
    if (!archivoClases.is_open()) {
        cout << "No se ha podido abrir el archivo Clases" << endl;
        return 0;
    }
    ifstream archivoAsistencias("../../asistencias_1697673600000.dat", ios::binary);
    if (!archivoAsistencias.is_open()) {
        cout << "No se ha podido abrir el archivo Asistencias" << endl;
        return 0;
    }
    string header;
    getline(archivoClientes, header);
    string line;
    uint cantClientes = -1;
    archivoClientes.clear();
    archivoClientes.seekg(0);
    while (getline(archivoClientes, line)) {
        cantClientes++;
    }
    cout<< "Cantidad de clientes: " << cantClientes;
    Cliente *clientes = new Cliente[cantClientes];
    eCodArchivos resClientes = leerClientes(clientes, archivoClientes);
    uint cantClases = -1;
    while (getline(archivoClases, line)){
        cantClases++;
    }
    Clase *clases = new Clase[cantClases];
    eCodArchivos resClases = leerClases(clases, archivoClases);
    cout<< "Cantidad de clases: " << cantClases << endl;


    //----------------------------------------------------------


    uint cantAsistencias = -2;
    uint auxLeerAsistencias;
    while (!archivoAsistencias.eof()) {
        archivoAsistencias.read((char *)&auxLeerAsistencias, sizeof(uint));
        archivoAsistencias.read((char *)&auxLeerAsistencias, sizeof(uint));
        Inscripcion auxInscriptions;
        for (uint i = 0; i < auxLeerAsistencias; i++) {
            archivoAsistencias.read((char *)&auxInscriptions, sizeof(Inscripcion));
        }
        cantAsistencias++;
    }
    cout << "Cantidad de asistencias: " << cantAsistencias << endl;
    Asistencia *asistencias = new Asistencia[cantAsistencias];
    eCodArchivos resAsistencias = leerAsistencias(archivoAsistencias, asistencias, cantAsistencias);
    uint idReserva = numeroRandom(1, cantClases);
    uint idCliente = numeroRandom(1, cantClientes);
    Reserva* reservas;
    uint cantReservas;
    eReservarClase reservaFinal;
    Sistema* sistema= new Sistema({clientes, cantClientes, asistencias, cantAsistencias -1 , 45, clases, cantClases, reservas, cantReservas});

    if(sistema->cantAsistencias >= sistema->cantMaxAsistencias){
        resizeAsistencia(sistema->asistencias, sistema->cantAsistencias);

    reservaFinal = ReservarClase(sistema, idReserva, idCliente);
    cout << reservaFinal;
    delete[] clientes;
    delete[] clases;
    Asistencia *auxLista = sistema->asistencias;
    for(int i=0;i < sistema->cantAsistencias ; i++){
            delete[] auxLista->ClasesInscriptas;
            auxLista++;
    }
    delete[] asistencias;
    archivoClientes.close();
    archivoClases.close();
    archivoAsistencias.close();
    }
    delete sistema;
    return 0;
}
