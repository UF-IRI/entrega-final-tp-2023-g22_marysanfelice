#ifndef GYM_H
#define GYM_H

#include "cliente.h"
#include "encabezados.h"
#include "asistencia.h"

enum buscarClase { ErrBuscarClase = -1, ExitoBuscarClase = 1 };
enum ReservarClase { ErrEstadoNeg = -8, ErrNohayespacio = -7,ErrNoExisteClase = -6,ErrClienteYaInscripto = -5 ,ErrClienteInscriptoEnOtraClase = -4 ,ErrNoExisteCliente = -3,ErrSpacio = -2,   ErrClaseNoEncontrada = -1, ExitoReservar = 1 };

typedef enum buscarClase eBuscarClase;
typedef enum ReservarClase eReservarClase;

struct clase{
    uint idClase;
    str nombre;
    uint cuposActuales;
    uint cuposMax;
    str sala;
    uint horario;
};
typedef struct clase Clase;

const Clase ClaseNulo = { 0,"",0,0,"",0};

struct reserva{
    uint idReserva;
    uint idClase;
    uint horario;
    str* inscriptos;
    int cantRegistrados;
};typedef struct reserva Reserva;

const Reserva ReservaNulo = {0,0,0,0,0};


struct sistema {
    Cliente* clientes;
    uint cantClientes;
    Asistencia* asistencias;
    uint cantAsistencias;
    uint cantMaxAsistencias;
    Clase* clases;
    uint cantClases;
    Reserva* reservas;
    uint cantReservas;
};typedef struct sistema Sistema;


Cliente BuscarCliente(Sistema* sistema, uint idCliente);
eBuscarClase buscarClase(Clase* clases, uint cant , str nombre);
eCodArchivos leerClases(Clase* clases, ifstream& Archi);
eReservarClase ReservarClase(Sistema *sistema, uint idReserva, uint idCliente);
bool clienteYaInscripto(str *inscripciones, uint cant, uint idCliente);
bool clienteMismoHorario(Reserva* reservas, uint cant, uint horario, uint idCliente);
bool ReservaExistente(Reserva *reservas, uint cant, uint idReserva);
Clase BuscarClase(Clase *clases, uint cant, uint idClase);
Reserva BuscarReserva(Reserva *reservas, uint cant, uint idReserva);
uint numeroRandom(uint min, uint max);
#endif // GYM_H
