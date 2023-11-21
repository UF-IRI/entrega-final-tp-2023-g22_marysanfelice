#include "asistencia.h"


void resizeAsistencia(Asistencia* miLista, uint tam, uint nuevoTam) {
    Asistencia* aux = new Asistencia[nuevoTam];

    uint longitud = (tam <  nuevoTam) ? tam : nuevoTam;

    if(aux != nullptr) {

        for(uint i = 0; i < longitud; i++)
            aux[i] = miLista[i]; // *(miLista + i)

        delete[] miLista;
    }
}

eCodArchivos leerAsistencias(ifstream& Archi, Asistencia* asistencias)
{
    Archi.clear();
    Archi.seekg(0);
    Asistencia *aux = asistencias;
    while (!Archi.eof()) {
        Archi.read((char *)&aux->idCliente, sizeof(uint));
        Archi.read((char *)&aux->cantInscripciones, sizeof(uint));
        Inscripcion* anotados = new Inscripcion[aux->cantInscripciones];
        Inscripcion* auxInscriptions = anotados;
        for (uint i = 0; i < aux->cantInscripciones; i++) {
            Archi.read((char *)auxInscriptions, sizeof(Inscripcion));
            auxInscriptions++;
        }
        aux->ClasesInscriptas = anotados;
        aux++;
    }
    return eCodArchivos::ExitoOperacion;
}


void EscribirAsistencias(Asistencia *asistencias, uint cant) {
    ofstream ArchiEscritura("../../asistencias_", ios::binary);
    if (!ArchiEscritura.is_open()) {
        cout << "No se pudo abrir el archivo de asistencias para escribir";
        return;
    }
    Asistencia *aux = asistencias;
    if (ArchiEscritura.is_open()) {
        for (uint i = 0; i < cant; i++) {
            ArchiEscritura.write((char *)&aux[i].idCliente, sizeof(uint));
            ArchiEscritura.write((char *)&aux[i].cantInscripciones, sizeof(uint));
            for (uint j = 0; j < aux[i].cantInscripciones; j++) {
                ArchiEscritura.write((char *)&aux[i].ClasesInscriptas[j], sizeof(Inscripcion));
                cout<< "Asistencia nro " << i << "reservada" << endl;
            }
        }
    }
}

Asistencia* BuscarAsistencias(Asistencia* asistencias, uint cant, uint idCliente){
    Asistencia* aux = asistencias,
        * ultimo = asistencias + (cant - 1);
    if(cant == 0){
        return nullptr;
    }
    while(true) {
        if (std::to_string(aux->idCliente) == std::to_string(idCliente)) {
            return aux;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return nullptr;
}

eAgrAsistencia NuevaAsistencia(Asistencia* asistencias, uint cant, Asistencia asistencia){
    if(cant==0){
        asistencias[0] = asistencia;
        return eAgrAsistencia::ExitoAgregar;
    }
    *(asistencias + cant -1) = asistencia;
    return eAgrAsistencia::ExitoAgregar;
}

eAgregarIncripcionAsistencia NuevaInscripcionAsistencia(Inscripcion* inscripciones, uint cant, Inscripcion inscripcion){
    if(cant == 0){
        *inscripciones  = inscripcion;
    }
    *(inscripciones + cant - 1) = inscripcion;
    return eAgregarIncripcionAsistencia::ExAgregar;
}
