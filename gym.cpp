#include "gym.h"
#include <ctime>
#include "asistencia.h"

#define string str

unsigned int asignarCupo(str nombre){
    unsigned int cupo=0;
    if(nombre=="Spinning" || nombre=="spinning"){
        cupo=45;
    }
    if(nombre=="Yoga" || nombre=="yoga"){
        cupo=25;
    }
    if(nombre=="Pilates" || nombre=="pilates"){
        cupo=15;
    }
    if(nombre=="Stretching" || nombre=="stretching"){
        cupo=40;
    }
    if(nombre=="Zumba" || nombre=="zumba"){
        cupo=50;
    }
    if(nombre=="Boxeo" || nombre=="boxeo"){
        cupo=30;
    }
    return cupo;
}

eBuscarClase buscarClase(Clase* clases, int cant ,str nombre){
    Clase* aux = clases;
    Clase* ultimo = clases + (cant - 1);
    while(true) {
        if (aux->nombre == nombre) {
            return eBuscarClase::ExitoBuscarClase;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return eBuscarClase::ErrBuscarClase;
}


eCodArchivos leerClases(Clase* clases, ifstream& Archi){
    Archi.clear();
    Archi.seekg(0);
    str header;
    getline(Archi, header);
    Clase* aux = clases;
    str line;
    while (getline(Archi,line)) {
        char delim = ',';
        string idClase, nombre, horario;
        std::istringstream iss(line);
        getline(iss, idClase, delim);
        getline(iss, nombre, delim);
        getline(iss, horario, delim);
        aux->idClase = stoi(idClase);
        aux->nombre  = nombre;
        aux->cuposMax = asignarCupo(nombre);
        aux++;
        }
    cout << endl;
    return eCodArchivos::ExitoOperacion;
}

uint numeroRandom(uint min, uint max){
    uint n;
    n = (rand() % max) + min;
    return n;
}



bool clienteYaInscripto(str* inscriptos, uint cant, uint idCliente){
    str *aux = inscriptos;
    str *ultimo = inscriptos + (cant - 1);
    while (true) {
        if (*aux == std::to_string(idCliente)) {
            return true;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return false;
}

bool clienteMismoHorario(Reserva *reservas, uint cant, uint horario, uint idCliente) {
    Reserva *aux = reservas;
    Reserva *ultimo = reservas + (cant - 1);
    while (true) {
        if (aux->horario == horario) {
            return true;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return false;
}

Reserva BuscarReserva(Reserva *reservas, uint cant, uint idReserva) {
    Reserva *aux = reservas, *ultimo = (reservas) + cant - 1;
    while (true) {
        if (aux->idReserva == idReserva) {
            return *aux;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return ReservaNulo;
}

bool ReservaExistente(Reserva *reservas, uint cant, uint idReserva){

    //return BuscarClase(reservas, cant, id).idClass != "";
    return true;
 }

Clase BuscarClase(Clase *clases, uint cant, uint idClase) {
    Clase* aux = clases;
    Clase* ultimo = clases + (cant - 1);
    while (true) {
        if (aux->idClase == idClase) {
            return *aux;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return ClaseNulo;
}

eReservarClase ReservarClase(Sistema &sistema, uint idReserva, uint idCliente) {
    Reserva ReservarClase = BuscarReserva(sistema.reservas, sistema.cantReservas, idReserva);
    if (ReservarClase.idClase == 0) { //Si la clase no existe
        return eReservarClase::ErrNoExisteClase;
    }
    Clase claseActual = BuscarClase(sistema.clases, sistema.cantClases, ReservarClase.idClase);
    if (ReservarClase.cantRegistrados < claseActual.cuposMax) { //Si no hay espacio en esa clase
        return eReservarClase::ErrNohayespacio;
    }


    if (clienteMismoHorario(sistema.reservas, sistema.cantReservas, ReservarClase.horario, idCliente) || clienteYaInscripto(sistema.reservas->inscriptos, sistema.reservas->cantRegistrados, idCliente)) {
        return eReservarClase::ErrClienteInscriptoEnOtraClase;
    }
    time_t now = time(0);
    uint diff = difftime(now, sistema.hoy) / 60 / 60 / 24;
    if (diff >= 1) {
        sistema.hoy = now;
        stringstream ss;
        str timeAsString;
        ss << now << ',' << endl;
        getline(ss, timeAsString, ',');
        EscribirAsistencias(sistema.asistencias,sistema.cantAsistencias,timeAsString);
        resizeAsistencia(sistema.asistencias, sistema.cantAsistencias, 0);
        sistema.cantAsistencias = 0;
    } else {
        Inscripcion NuevaInscripcion = {idReserva,time(0)};
        if (sistema.cantAsistencias < sistema.cantMaxAsistencias) {
            Asistencia* asistencia =
                BuscarAsistencias(sistema.asistencias,sistema.cantAsistencias, idCliente);
            if (asistencia == nullptr) {
                Asistencia NuevaAsistencias = {idCliente,1,new Inscripcion[5]};
                *NuevaAsistencias.ClasesInscriptas=NuevaInscripcion;
                sistema.cantAsistencias ++;
                NuevaAsistencia(sistema.asistencias,sistema.cantAsistencias ,NuevaAsistencias);
            } else {
                if(asistencia->cantInscripciones < 5){
                    asistencia->cantInscripciones++;
                    NuevaInscripcionAsistencia(asistencia->ClasesInscriptas, asistencia->cantInscripciones, NuevaInscripcion);
                } else {
                    return eReservarClase::ErrNohayespacio;
                }
            }
        } else {
            resizeAsistencia(sistema.asistencias, sistema.cantAsistencias, sistema.cantMaxAsistencias * 2);
            sistema.cantAsistencias = sistema.cantMaxAsistencias * 2;
            if (sistema.asistencias == nullptr){
                return eReservarClase::ErrSpacio;
            }
        }
    }
    return eReservarClase::ExitoReservar;
}
