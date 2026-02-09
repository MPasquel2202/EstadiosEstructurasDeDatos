#pragma once

#include "ds/LinkedList.hpp"
#include "model/Evento.hpp"
#include "model/InventarioEvento.hpp"
#include "model/Usuario.hpp"

class EstrategiasController {
public:
    static void mostrarMenuEstrategias(LinkedList<Evento>& eventos,
                                       LinkedList<InventarioEvento>& inventarios,
                                       LinkedList<Usuario>& usuarios);
};
