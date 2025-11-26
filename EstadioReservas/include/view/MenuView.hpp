
#pragma once
#include <string>
#include "model/Usuario.hpp"
#include "model/Evento.hpp"
#include "model/InventarioEvento.hpp"
#include "ds/LinkedList.hpp"

namespace MenuView{
    void bienvenida();
    void recordarNombreCaseSensitive();
    void principal(const LinkedList<Evento>& eventos, const LinkedList<InventarioEvento>& invs);
    void noReservableYVolver();
    void error(const std::string& msg);
}
