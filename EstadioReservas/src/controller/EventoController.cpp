#include "controller/EventoController.hpp"
#include "utils/DateUtils.hpp"
#include "utils/InputUtils.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include "utils/QuickSortPtr.hpp"
#include "view/Printer.hpp"

namespace EventoController{
    bool esReservable(const Evento& e){
        return DateUtils::esReservable(e.fecha, DateUtils::hoy());
    }

    Evento* buscarEventoPorIdBST(BinarySearchTree<Evento>& indice, const std::string& id){
        // Búsqueda binaria #2: wrapper sobre el BST mutable
        return indice.find(id);
    }

    const Evento* buscarEventoPorIdBST(const BinarySearchTree<Evento>& indice, const std::string& id){
        // Búsqueda binaria #3: wrapper sobre el BST constante
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
            // Búsqueda binaria #4: inventarios ordenados por eventoId
            // arr[m] -> *(arr.data() + m)
            if((*(arr.data() + m))->eventoId == eventoId) return *(arr.data() + m);
            if((*(arr.data() + m))->eventoId < eventoId) l = m + 1; else r = m - 1;
        }

        return nullptr;
    }

    std::vector<const Evento*> buscarEventosPorFecha(const LinkedList<Evento>& eventos, const Fecha& fechaObjetivo){
        std::vector<const Evento*> ordenados;
        eventos.for_each([&](const Evento& e){ ordenados.push_back(&e); });
        if(ordenados.empty()) return {};

        std::sort(ordenados.begin(), ordenados.end(), [](const Evento* a, const Evento* b){ return a->fecha < b->fecha; });

        int l = 0, r = (int)ordenados.size() - 1;
        int match = -1;
        while(l <= r){
            int m = l + (r - l) / 2;
            // Búsqueda binaria #6: fechas ordenadas para filtro de menú
            if(ordenados[m]->fecha == fechaObjetivo){ match = m; break; }
            if(ordenados[m]->fecha < fechaObjetivo) l = m + 1; else r = m - 1;
        }

        if(match == -1) return {};

        int left = match, right = match;
        while(left-1 >= 0 && ordenados[left-1]->fecha == fechaObjetivo) --left;
        while(right+1 < (int)ordenados.size() && ordenados[right+1]->fecha == fechaObjetivo) ++right;

        std::vector<const Evento*> resultado;
        for(int i = left; i <= right; ++i) resultado.push_back(ordenados[i]);
        return resultado;
    }

    void filtrarPorFecha(const LinkedList<Evento>& eventos, const LinkedList<InventarioEvento>& invs){
        (void)invs; // La visibilidad de inventarios no es necesaria en este filtro puntual
        std::cout << "Ingrese fecha (YYYY-MM-DD): ";
        std::string iso = InputUtils::leerLineaNoVacia(10);

        Fecha buscada;
        try{
            buscada = Fecha::parseISO(iso);
        }catch(const std::exception& e){
            std::cout << "Fecha invalida: " << e.what() << "\n";
            return;
        }

        auto coincidencias = buscarEventosPorFecha(eventos, buscada);
        if(coincidencias.empty()){
            std::cout << "No hay eventos programados en " << iso << "\n";
            return;
        }

        Printer::titulo("Eventos en " + buscada.iso());
        std::cout << std::left << std::setw(10) << "ID"
                  << std::setw(28) << "Nombre"
                  << std::setw(12) << "Fecha"
                  << "Estado" << "\n";
        Printer::linea();

        for(const Evento* ev : coincidencias){
            bool ok = esReservable(*ev);
            std::cout << std::left << std::setw(10) << ev->id
                      << std::setw(28) << ev->nombre.substr(0,27)
                      << std::setw(12) << ev->fecha.iso()
                      << (ok ? "Reservable" : "No reservable")
                      << "\n";
        }
    }
}