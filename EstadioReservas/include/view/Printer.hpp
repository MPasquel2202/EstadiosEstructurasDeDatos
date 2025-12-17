#pragma once
#include <string>
#include <functional>
#include "ds/LinkedList.hpp"
#include "model/Evento.hpp"
#include "model/Usuario.hpp"
#include "model/InventarioEvento.hpp"
#include "structures/HashTable.h"
#include "structures/BinarySearchTree.h"
#include <vector>
#include "model/Reserva.hpp"

namespace Printer{
    void titulo(const std::string& t);
    void linea();

    void listarEventos(const LinkedList<Evento>& eventos,
                       const LinkedList<InventarioEvento>& invs,
                       const std::function<bool(const Evento&)>& esReservable);

    void mostrarInventario(const InventarioEvento& inv);
    void mostrarReservasUsuario(const Usuario& u, const LinkedList<Evento>& eventos);
        void mostrarReservasOrdenadas(const Usuario& u, const std::vector<Reserva*>& reservas,
                                       const LinkedList<Evento>& eventos);
    void imprimirTablaHashInventarios(const HashTable& tabla);
    void listarEventosEnOrdenBST(const BinarySearchTree<Evento>& indice);

}
