
#pragma once
#include <string>
#include <vector>
#include "ds/LinkedList.hpp"
#include "structures/BinarySearchTree.h"
#include "model/Evento.hpp"
#include "model/Fecha.hpp"
#include "model/InventarioEvento.hpp"

namespace EventoController{
    Evento* seleccionarEvento(BinarySearchTree<Evento>& indice, LinkedList<Evento>& eventos);
    const Evento* seleccionarEvento(const BinarySearchTree<Evento>& indice, const LinkedList<Evento>& eventos);
    Evento* buscarEventoPorIdBST(BinarySearchTree<Evento>& indice, const std::string& id);
    const Evento* buscarEventoPorIdBST(const BinarySearchTree<Evento>& indice, const std::string& id);
    bool esReservable(const Evento& e);
    InventarioEvento* obtenerInventario(LinkedList<InventarioEvento>& invs, const std::string& eventoId);
    std::vector<const Evento*> buscarEventosPorFecha(const LinkedList<Evento>& eventos, const Fecha& fechaObjetivo);
    void filtrarPorFecha(const LinkedList<Evento>& eventos, const LinkedList<InventarioEvento>& invs);
}
