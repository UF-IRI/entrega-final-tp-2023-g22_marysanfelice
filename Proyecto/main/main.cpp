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

    uint cantAsistencias = -3;
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
    Sistema* sistema= new Sistema({clientes, cantClientes, asistencias, cantAsistencias  , cantAsistencias, clases, cantClases, reservas, cantReservas});
    if (sistema->cantAsistencias >= sistema->cantMaxAsistencias) {
        // Redimensiona el arreglo de asistencias
        resizeAsistencia(sistema->asistencias, sistema->cantMaxAsistencias);

        // Realiza operaciones que puedan depender del tamaño actualizado del arreglo asistencias
        Reserva* reservas;
        uint cantReservas;
        eReservarClase reservaFinal = ReservarClase(sistema, idReserva, idCliente);
        cout << reservaFinal;
        EscribirAsistencias(sistema->asistencias,sistema->cantAsistencias);

        // Resto del código para liberar memoria...
        delete[] clientes;
        delete[] clases;

        for (int i = 0; i < sistema->cantAsistencias; i++) {
            for (int j = 0; j < sistema->asistencias[i].cantInscripciones; j++) {
                // No necesitas delete para elementos individuales de ClasesInscriptas
            }

            // Libera el arreglo completo de ClasesInscriptas
            Asistencia aux = sistema->asistencias[i];
            delete[] aux.ClasesInscriptas;

        }

        delete[] sistema->asistencias;
        archivoClientes.close();
        archivoClases.close();
        archivoAsistencias.close();
    }

    delete sistema;
    return 0;
}
