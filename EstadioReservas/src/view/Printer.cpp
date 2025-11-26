#include "view/Printer.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

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
                  << " | Total=" << r->total()
                  << "\n";
    }
}


}
