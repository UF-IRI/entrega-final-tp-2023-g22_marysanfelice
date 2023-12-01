#ifndef ASISTENCIA_H
#define ASISTENCIA_H

#include "encabezados.h"

enum agregarAsistencia{ErrEspacio=-1,  ExitoAgregar=1};
enum agregarIncripcionAsistencia{ErrorEspacio=-1,  ExAgregar=1};
typedef enum agregarAsistencia eAgrAsistencia;
typedef enum agregarIncripcionAsistencia eAgregarIncripcionAsistencia;

struct inscripcion {
    uint idClase;
    time_t fechaInscripcion;
};
typedef struct inscripcion Inscripcion;

struct asistencia{
    uint idCliente, cantInscripciones;
    Inscripcion* ClasesInscriptas; //clases a las que se inscribió
    };
    typedef struct asistencia Asistencia;

const Asistencia AsistenciasNulo={0, 0, nullptr};

void resizeAsistencia(Asistencia*& vector, uint& n);
eAgrAsistencia NuevaAsistencia(Asistencia* asistencias,uint cant ,Asistencia asistencia);
eAgregarIncripcionAsistencia NuevaInscripcionAsistencia(Inscripcion* inscripciones,uint cant,Inscripcion inscripcion);
//bool hayEspacio(Asistencia* asistencias);
eCodArchivos leerAsistencias(ifstream& Archi, Asistencia* asistencias,uint cant);
void EscribirAsistencias(Asistencia *asistencias, uint cant);
Asistencia* BuscarAsistencias(Asistencia* asistencias,uint cant ,uint idCliente);

#endif // ASISTENCIA_H
