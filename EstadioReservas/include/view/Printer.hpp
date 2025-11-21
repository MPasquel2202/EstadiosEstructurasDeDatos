#pragma once
#include <string>
#include <functional>
#include "ds/LinkedList.hpp"
#include "model/Evento.hpp"
#include "model/Usuario.hpp"
#include "model/InventarioEvento.hpp"

namespace Printer{
    void titulo(const std::string& t);
    void linea();

    void listarEventos(const LinkedList<Evento>& eventos,
                       const LinkedList<InventarioEvento>& invs,
                       const std::function<bool(const Evento&)>& esReservable);

    void mostrarInventario(const InventarioEvento& inv);
    void mostrarReservasUsuario(const Usuario& u, const LinkedList<Evento>& eventos);
    
}
