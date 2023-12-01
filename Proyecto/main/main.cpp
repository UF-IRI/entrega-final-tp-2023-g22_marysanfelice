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
    uint cantAsistencias = -1;
    uint auxLeerAsistencias;
    while (!archivoAsistencias.eof()) {
        archivoAsistencias.read((char *)&auxLeerAsistencias, sizeof(uint));
        archivoAsistencias.read((char *)&auxLeerAsistencias, sizeof(uint));
        Inscripcion auxInscripciones;
        for (uint i = 0; i < auxLeerAsistencias; i++) {
            archivoAsistencias.read((char *)&auxInscripciones, sizeof(Inscripcion));
        }
        cantAsistencias++;
    }
    cout << "Cantidad de asistencias: " << cantAsistencias << endl;
    Asistencia *asistencias = new Asistencia[cantAsistencias - 1];
    eCodArchivos resAsistencias = leerAsistencias(archivoAsistencias, asistencias);
    uint idReserva = numeroRandom(1, cantClases);
    uint idCliente = numeroRandom(1, cantClientes);
    Reserva* reservas;
    uint cantReservas;
    eReservarClase reservaFinal;
    Sistema* sistema= new Sistema({clientes, cantClientes, asistencias, cantAsistencias -1 , 45, clases, cantClases, reservas, cantReservas});

    if(sistema->cantAsistencias >= sistema->cantMaxAsistencias){
        resizeAsistencia(sistema->asistencias, sistema->cantAsistencias);

    reservaFinal = ReservarClase(sistema, idReserva, idCliente);
    ifstream ArchiFinal("../../asistencias_", ios::binary);
    uint cantAsistenciasFinal = -1;
    uint auxLeerAsistenciasFinal;
    while (!ArchiFinal.eof()) {
        ArchiFinal.read((char *)&auxLeerAsistenciasFinal, sizeof(uint));
        ArchiFinal.read((char *)&auxLeerAsistenciasFinal, sizeof(uint));
        Inscripcion auxInscripcionesFinal;
        for (uint i = 0; i < auxLeerAsistenciasFinal; i++) {
            ArchiFinal.read((char *)&auxInscripcionesFinal, sizeof(Inscripcion));
        }
        cantAsistenciasFinal++;
    }
    cout << "Cantidad de asistencias archivo nuevo: " << cantAsistenciasFinal << endl;
    Asistencia *asistenciasFinal = new Asistencia[cantAsistenciasFinal - 1];
    eCodArchivos resFinal = leerAsistencias(ArchiFinal, asistenciasFinal);
    cout << resFinal;
    delete[] clientes;
    delete[] clases;
    delete[] asistencias;
    delete[] asistenciasFinal;
    archivoClientes.close();
    archivoClases.close();
    archivoAsistencias.close();
    ArchiFinal.close();
    return 0;
}

}
