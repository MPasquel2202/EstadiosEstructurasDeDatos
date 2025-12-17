
#pragma once
#include <string>
#include "ds/LinkedList.hpp"
#include "structures/BinarySearchTree.h"
#include "model/Evento.hpp"
#include "model/InventarioEvento.hpp"

namespace EventoController{
    Evento* seleccionarEvento(BinarySearchTree<Evento>& indice);
    const Evento* seleccionarEvento(const BinarySearchTree<Evento>& indice);
    Evento* buscarEventoPorIdBST(BinarySearchTree<Evento>& indice, const std::string& id);
    const Evento* buscarEventoPorIdBST(const BinarySearchTree<Evento>& indice, const std::string& id);
    bool esReservable(const Evento& e);
    InventarioEvento* obtenerInventario(LinkedList<InventarioEvento>& invs, const std::string& eventoId);
}
