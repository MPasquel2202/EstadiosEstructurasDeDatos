#include "view/Printer.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include "utils/DateUtils.hpp"

namespace Printer{
    void titulo(const std::string& t){ std::cout << "\n=== " << t << " ===\n"; }
    void linea(){ std::cout << std::string(60,'-') << "\n"; }

    void listarEventos(const LinkedList<Evento>& eventos,
                       const LinkedList<InventarioEvento>& invs,
                       const std::function<bool(const Evento&)>& esReservable){
        (void)invs; 

        titulo("Eventos disponibles");
        std::cout << std::left << std::setw(10) << "ID"
                  << std::setw(28) << "Nombre"
                  << std::setw(12) << "Fecha"
                  << "Estado" << "\n";
        linea();
        eventos.for_each([&](const Evento& e){
            bool ok = esReservable(e);
            std::cout << std::left << std::setw(10) << e.id
                      << std::setw(28) << e.nombre.substr(0,27)
                      << std::setw(12) << e.fecha.iso()
                      << (ok ? "Reservable" : "No reservable")
                      << "\n";
        });
    }

    void mostrarInventario(const InventarioEvento& inv){
        titulo("Inventario del evento " + inv.eventoId);
        std::cout << "Limite por usuario: " << inv.limitePorUsuario << "\n";
        std::cout << "GENERAL: " << inv.occGeneral << "/" << inv.capGeneral
                  << " (disp " << (inv.capGeneral - inv.occGeneral) << ")\n";
        std::cout << "TRIBUNA: " << inv.occTribuna << "/" << inv.capTribuna
                  << " (disp " << (inv.capTribuna - inv.occTribuna) << ")\n";
        std::cout << "PALCO:   " << inv.occPalco   << "/" << inv.capPalco
                  << " (disp " << (inv.capPalco   - inv.occPalco)   << ")\n";
    }

void mostrarReservasUsuario(const Usuario& u, const LinkedList<Evento>& eventos){
    titulo("Mis reservas (" + u.nombre + " - " + u.cedula + ")");

    if(u.reservas.size() == 0){
        std::cout << "Sin reservas.\n";
        return;
    }

    std::vector<const Reserva*> ordenadas;
    ordenadas.reserve(u.reservas.size());

    u.reservas.for_each([&](const Reserva& r){
        ordenadas.push_back(&r);
    });

    std::sort(ordenadas.begin(), ordenadas.end(),
        [&](const Reserva* a, const Reserva* b){
            const Evento* ea = eventos.find([&](const Evento& e){ return e.id == a->eventoId; });
            const Evento* eb = eventos.find([&](const Evento& e){ return e.id == b->eventoId; });

            Fecha fa = ea ? ea->fecha : Fecha();
            Fecha fb = eb ? eb->fecha : Fecha();

            return fa < fb;  
        }
    );

    for(const Reserva* r : ordenadas){
        const Evento* ev = eventos.find([&](const Evento& e){ return e.id == r->eventoId; });
        std::string nom = ev ? ev->nombre : "(evento desconocido)";

        std::cout << r->eventoId << " | " << nom
                  << " | G=" << r->general
                  << ", T=" << r->tribuna
                  << ", P=" << r->palco
                  << " | Total=" << r->total() << "\n";
    }
}

void mostrarReservasOrdenadas(const Usuario& u, const std::vector<Reserva*>& reservas,
                              const LinkedList<Evento>& eventos){
    titulo("Mis reservas ordenadas (" + u.nombre + " - " + u.cedula + ")");

    if(reservas.empty()){
        std::cout << "Sin reservas.\n";
        return;
    }

    std::cout << std::left << std::setw(12) << "Evento ID"
              << std::setw(30) << "Nombre del Evento"
              << std::setw(5) << "Gen"
              << std::setw(5) << "Trib"
              << std::setw(5) << "Palco"
              << "Total" << "\n";
    linea();

    for(const Reserva* r : reservas){
        const Evento* ev = eventos.find([&](const Evento& e){ return e.id == r->eventoId; });
        std::string nom = ev ? ev->nombre : "(evento desconocido)";

        std::cout << std::left << std::setw(12) << r->eventoId
                  << std::setw(30) << nom.substr(0, 29)
                  << std::setw(5) << r->general
                  << std::setw(5) << r->tribuna
                  << std::setw(5) << r->palco
                  << r->total()
                  << "\n";
    }
}

void imprimirTablaHashInventarios(const HashTable& tabla){
    titulo("Tabla hash de inventarios");

    if(tabla.size() == 0){
        std::cout << "Tabla vacia.\n";
        return;
    }

    auto items = tabla.entries();
    std::sort(items.begin(), items.end(), [](const auto& a, const auto& b){
        return a.first < b.first;
    });

    std::cout << std::left << std::setw(12) << "Evento ID"
              << std::setw(15) << "General"
              << std::setw(15) << "Tribuna"
              << std::setw(15) << "Palco" << "\n";
    linea();

    for(const auto& par : items){
        const InventarioEvento* inv = par.second;
        if(!inv) continue;

        std::cout << std::left << std::setw(12) << par.first
                  << std::setw(15) << (std::to_string(inv->occGeneral) + "/" + std::to_string(inv->capGeneral))
                  << std::setw(15) << (std::to_string(inv->occTribuna) + "/" + std::to_string(inv->capTribuna))
                  << std::setw(15) << (std::to_string(inv->occPalco) + "/" + std::to_string(inv->capPalco))
                  << "\n";
    }

    std::cout << "(La tabla se reconstruye al consultar para reflejar cambios recientes.)\n";
}

void listarEventosEnOrdenBST(const BinarySearchTree<Evento>& indice){
    titulo("Eventos en BST (in-order por ID)");
    if(indice.size() == 0){
        std::cout << "Indice vacio.\n";
        return;
    }

    std::cout << std::left << std::setw(10) << "ID"
              << std::setw(28) << "Nombre"
              << std::setw(12) << "Fecha"
              << "Estado" << "\n";
    linea();

    Fecha hoy = DateUtils::hoy();
    indice.inOrder([&](const BinarySearchTree<Evento>::Node& nodo){
        const Evento* e = nodo.payload;
        if(!e) return;
        bool ok = DateUtils::esReservable(e->fecha, hoy);
        std::cout << std::left << std::setw(10) << e->id
                  << std::setw(28) << e->nombre.substr(0,27)
                  << std::setw(12) << e->fecha.iso()
                  << (ok ? "Reservable" : "No reservable")
                  << "\n";
    });
}
}
