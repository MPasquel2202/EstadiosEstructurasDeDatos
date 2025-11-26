
#include "controller/EventoController.hpp"
#include "utils/DateUtils.hpp"
#include "utils/InputUtils.hpp"
#include <iostream>

namespace EventoController{
    bool esReservable(const Evento& e){
        return DateUtils::esReservable(e.fecha, DateUtils::hoy());
    }

    Evento* seleccionarEvento(LinkedList<Evento>& eventos){
        std::cout << "Ingrese ID de evento: ";
        std::string id = InputUtils::leerLineaNoVacia(1);
        Evento* ev = eventos.find([&](const Evento& e){ return e.id == id; });
        if(!ev){ std::cout << "Evento no encontrado.\n"; return nullptr; }
        return ev;
    }

    const Evento* seleccionarEvento(const LinkedList<Evento>& eventos){
        std::cout << "Ingrese ID de evento: ";
        std::string id = InputUtils::leerLineaNoVacia(1);
        const Evento* ev = eventos.find([&](const Evento& e){ return e.id == id; }); 
        if(!ev){ std::cout << "Evento no encontrado.\n"; return nullptr; }
        return ev;
    }

    InventarioEvento* obtenerInventario(LinkedList<InventarioEvento>& invs, const std::string& eventoId){
        return invs.find([&](const InventarioEvento& i){ return i.eventoId == eventoId; });
    }
}
