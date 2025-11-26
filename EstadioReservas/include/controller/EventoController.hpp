
#pragma once
#include <string>
#include "ds/LinkedList.hpp"
#include "model/Evento.hpp"
#include "model/InventarioEvento.hpp"

namespace EventoController{
    Evento* seleccionarEvento(LinkedList<Evento>& eventos);
    const Evento* seleccionarEvento(const LinkedList<Evento>& eventos); 
    bool esReservable(const Evento& e);
    InventarioEvento* obtenerInventario(LinkedList<InventarioEvento>& invs, const std::string& eventoId);
}
