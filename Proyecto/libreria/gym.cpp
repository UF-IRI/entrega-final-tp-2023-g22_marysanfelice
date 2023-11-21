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

bool clienteMismoHorario(Reserva* reserva, uint cant, uint horario, uint idCliente) {
    Reserva* aux = reserva, *ultimo = reserva + (cant - 1);
    while (true) {
        if (aux->horario == horario) {
            str* auxInscriptos = aux->inscriptos;
            str* ultimoInscripto = aux->inscriptos + (aux->cantRegistrados - 1);
            while (true) {
                if (*auxInscriptos == std::to_string(idCliente)) {
                    return true;
                }
                if (auxInscriptos == ultimoInscripto)
                    break;
                auxInscriptos++;
            }
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return false;
}

Reserva BuscarReserva(Reserva *reservas, uint cant, uint idReserva) {
    Reserva *aux = reservas, *ultimo = reservas + (cant - 1);
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

Cliente BuscarCliente(Sistema* sistema, uint idCliente) {
    Cliente* aux = sistema->clientes;
    Cliente* ultimo = sistema->clientes + (sistema->cantClientes - 1);
    while(true) {
        if (stoul(aux->idCliente) == idCliente) {
            return *aux;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return ClienteNulo;
}

bool chequearEstado(Cliente cliente){
    if(stol(cliente.estado) >= 0){
        return true;
    }
    return false;
}

eReservarClase ReservarClase(Sistema *sistema, uint idReserva, uint idCliente) {
    Cliente cliente = BuscarCliente(sistema, idCliente);
    if(!chequearEstado(cliente)){
        return eReservarClase::ErrEstadoNeg;
    }
    Reserva ReservarClase = BuscarReserva(sistema->reservas, sistema->cantReservas, idReserva);
    if (ReservarClase.idClase == 0) {
        return eReservarClase::ErrNoExisteClase;
    }
    Clase claseActual = BuscarClase(sistema->clases, sistema->cantClases, ReservarClase.idClase);
    if (ReservarClase.cantRegistrados < claseActual.cuposMax) {
        return eReservarClase::ErrNohayespacio;
    }
    if (clienteMismoHorario(sistema->reservas, sistema->cantReservas, ReservarClase.horario, idCliente) || clienteYaInscripto(sistema->reservas->inscriptos, sistema->reservas->cantRegistrados, idCliente)) {
        return eReservarClase::ErrClienteInscriptoEnOtraClase;
    }
    uint cantClasesCliente = numeroRandom(1, 5); //Suponemos que el cliente se puede anotar entre 1 a 5 clases.
    EscribirAsistencias(sistema->asistencias, cantClasesCliente);
    return eReservarClase::ExitoReservar;
}
