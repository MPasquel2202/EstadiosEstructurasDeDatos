#include "controller/EventoController.hpp"
#include "utils/DateUtils.hpp"
#include "utils/InputUtils.hpp"
#include <iostream>
#include <vector>
#include "utils/QuickSortPtr.hpp"

namespace EventoController{
    bool esReservable(const Evento& e){
        return DateUtils::esReservable(e.fecha, DateUtils::hoy());
    }

    Evento* buscarEventoPorIdBST(BinarySearchTree<Evento>& indice, const std::string& id){
        return indice.find(id);
    }

    const Evento* buscarEventoPorIdBST(const BinarySearchTree<Evento>& indice, const std::string& id){
        return indice.find(id);
    }

    Evento* seleccionarEvento(BinarySearchTree<Evento>& indice){
        std::cout << "Ingrese ID de evento: ";
        std::string id = InputUtils::leerLineaNoVacia(1);

        if(auto* encontrado = buscarEventoPorIdBST(indice, id)) return encontrado;

        std::cout << "Evento no encontrado.\n";
        return nullptr;
    }

    const Evento* seleccionarEvento(const BinarySearchTree<Evento>& indice){
        std::cout << "Ingrese ID de evento: ";
        std::string id = InputUtils::leerLineaNoVacia(1);

        if(auto* encontrado = buscarEventoPorIdBST(indice, id)) return encontrado;

        std::cout << "Evento no encontrado.\n";
        return nullptr;
    }

    InventarioEvento* obtenerInventario(LinkedList<InventarioEvento>& invs, const std::string& eventoId){
        std::vector<InventarioEvento*> arr;
        invs.for_each([&](InventarioEvento& i){ arr.push_back(&i); });
        if(arr.empty()) return nullptr;

        QuickSortPtr::quickSort<InventarioEvento*>(arr, [](const InventarioEvento* a, const InventarioEvento* b){ return a->eventoId < b->eventoId; });

        int l = 0, r = (int)arr.size()-1;
        while(l <= r){
            int m = l + (r-l)/2;
            // arr[m] -> *(arr.data() + m)
            if((*(arr.data() + m))->eventoId == eventoId) return *(arr.data() + m);
            if((*(arr.data() + m))->eventoId < eventoId) l = m + 1; else r = m - 1;
        }

        return nullptr;
    }
}