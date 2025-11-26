#pragma once
#include "model/Usuario.hpp"
#include "model/InventarioEvento.hpp"
#include "model/Evento.hpp"

namespace ReservaController{
    void reservar(Usuario& u, InventarioEvento& inv, const Evento& e);

    void cancelar(Usuario& u, InventarioEvento& inv, const Evento& e);
}
