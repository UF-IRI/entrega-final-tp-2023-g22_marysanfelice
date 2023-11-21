#include <catch2/catch.hpp>
#include <gym.h>

TEST_CASE("Buscar Cliente") {
    Sistema* sistema = new Sistema;
    REQUIRE(sistema != nullptr);

    sistema->clientes = new cliente[6];
    REQUIRE(sistema->clientes != nullptr);

    sistema->clientes[0]={"4","Juan", "Perez","juan@example.com", "123-456-7890", "5-3-1987", "-200"};
    sistema->clientes[1]= {"5","Maria", "Gonzalez",  "maria@example.com", "987-654-3210", "15-11-1992", "0"};
    sistema->clientes[2]= {"3","Carlos", "Lopez", "carlos@example.com", "555-123-4567", "8-7-1980", "600"};
    sistema->clientes[3]={"2","Ana", "Martinez", "ana@example.com", "111-222-3333", "20-12-1998",  "-4"};
    sistema->clientes[4]={"6","Pedro", "Rodriguez","pedro@example.com", "999-888-7777", "10-4-1987",  "0"};
    sistema->clientes[5]={"1","Laura", "Lopez", "laura@example.com", "333-444-5555", "3-9-1995", "3"};

    SECTION("Buscando Cliente") {
        Cliente res = BuscarCliente(sistema,4);
        REQUIRE(res.nombre == "Juan" );
    }
    delete[] sistema->clientes;
}

TEST_CASE("Buscar Clase"){
    Sistema* sistema = new Sistema;
    REQUIRE(sistema != nullptr);

    Clase* clases = new Clase[6];
    REQUIRE(clases != nullptr);

    clases[0] = {1, "Spinning", 20, 45, "Sala 101", 1200};
    clases[1] = {2, "Yoga", 15, 25, "Sala 102", 1430};
    clases[2] = {3, "Pilates", 10, 15, "Sala 103", 1600};
    clases[3] = {4, "Stretching", 18, 40, "Sala 104", 1030};
    clases[4] = {5, "Zumba", 22, 50, "Sala 105", 1345};
    clases[5] = {6, "Boxeo", 22, 30, "Sala 105", 1345};


    SECTION("Buscar clase"){
        uint idClaseExistente = 3;
        Clase res = BuscarClase(clases, 6, idClaseExistente);
        REQUIRE(res.nombre == "Pilates");
    }

    SECTION("Buscar clase que no existe"){
        uint idClaseInexistente = 7;
        Clase resul = BuscarClase(clases, 5, idClaseInexistente);
        REQUIRE(resul.idClase == ClaseNulo.idClase);
    }

    delete sistema;
    delete[] clases;
}

TEST_CASE("Buscar Reserva") {
    Reserva* reservas = new Reserva[5];
    REQUIRE(reservas != nullptr);

    reservas[0] = {1, 101, 1200, new str[2]{"Cliente1", "Cliente2"}, 2};
    reservas[1] = {2, 102, 1430, new str[3]{"Cliente3", "Cliente4", "Cliente5"}, 3};
    reservas[2] = {3, 103, 1600, new str[1]{"Cliente6"}, 1};
    reservas[3] = {4, 104, 1030, new str[4]{"Cliente7", "Cliente8", "Cliente9", "Cliente10"}, 4};
    reservas[4] = {5, 105, 1345, new str[2]{"Cliente11", "Cliente12"}, 2};


    SECTION("Buscar Reserva"){
        uint idReservaExistente = 3;
        Reserva res = BuscarReserva(reservas, 5, idReservaExistente);
        REQUIRE(res.idReserva == idReservaExistente);
        REQUIRE(res.idClase == 103);
        REQUIRE(res.horario == 1600);
        REQUIRE(res.inscriptos[0] == "Cliente6");
    }

    SECTION("Buscar Reserva que no existe"){
        uint idReservaInexistente = 6;
        Reserva resultadoInexistente = BuscarReserva(reservas, 5, idReservaInexistente);
        REQUIRE(resultadoInexistente.idReserva == ReservaNulo.idReserva);
    }

    for (int i = 0; i < 5; ++i) {
        delete[] reservas[i].inscriptos;
    }

    delete[] reservas;
}

TEST_CASE("Chequear Estado del Cliente") {

    Cliente cliente = {"1", "Juan", "Perez", "juan@example.com", "123-456-7890", "5-3-1985", "-200"};

    SECTION("Estado Negativo"){
        bool res = chequearEstado(cliente);
        REQUIRE(res == false);
    }

    cliente.estado = "100";

    SECTION("Estado positivo"){
        bool resul = chequearEstado(cliente);
        REQUIRE(resul == true);
    }
}

TEST_CASE("Cliente Mismo Horario") {
    Sistema* sistema = new Sistema;
    REQUIRE(sistema != nullptr);

    sistema->reservas = new Reserva[3];
    REQUIRE(sistema->reservas != nullptr);

    sistema->reservas[0].horario = 8;
    sistema->reservas[0].inscriptos = new str[1];
    sistema->reservas[0].inscriptos[0] = "1";
    sistema->reservas[0].cantRegistrados = 1;

    sistema->reservas[1].horario = 9;
    sistema->reservas[1].inscriptos = new str[1];
    sistema->reservas[1].inscriptos[0] = "2";
    sistema->reservas[1].cantRegistrados = 1;

    sistema->reservas[2].horario = 10;
    sistema->reservas[2].inscriptos = new str[1];
    sistema->reservas[2].inscriptos[0] = "3";
    sistema->reservas[2].cantRegistrados = 1;

    SECTION("Cliente está inscripto en otra clase en el mismo horario") {
    uint horarioTest = 8;
    str idClienteTest = "1";

    bool resultado = clienteMismoHorario(sistema->reservas, 3, horarioTest, stoul(idClienteTest));

    REQUIRE(resultado == true);
    }

    SECTION("Cliente no esta inscripto en otra clase en el mismo horario") {
    uint horarioTest = 16;
    str idClienteTest = "1";

    bool resultado = clienteMismoHorario(sistema->reservas, 3, horarioTest, stoul(idClienteTest));

    REQUIRE(resultado == false);
    }

    delete[] sistema->reservas[0].inscriptos;
    delete[] sistema->reservas[1].inscriptos;
    delete[] sistema->reservas[2].inscriptos;
    delete[] sistema->reservas;
    delete sistema;
}
