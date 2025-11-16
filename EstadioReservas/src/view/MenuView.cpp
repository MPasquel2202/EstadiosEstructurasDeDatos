#include "view/MenuView.hpp"
#include "view/Printer.hpp"
#include <iostream>

namespace MenuView{
    void bienvenida(){
        Printer::titulo("Sistema de Reservas Estadio");
    }

    void recordarNombreCaseSensitive(){
        std::cout << "Nota: El nombre distingue MAYUSCULAS Y MINUSCULAS (case-sensitive).\n";
    }

    void principal(const LinkedList<Evento>& eventos, const LinkedList<InventarioEvento>& invs){
        Printer::listarEventos(eventos, invs, [](const Evento&){ return true; });
    }

    void noReservableYVolver(){
        std::cout << "No reservable (evento fuera de fecha). Volviendo al menu principal...\n";
    }

    void error(const std::string& msg){ std::cout << "[ERROR] " << msg << "\n"; }
}
