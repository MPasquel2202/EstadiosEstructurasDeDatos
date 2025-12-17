#include "model/Usuario.hpp"
#include <algorithm>
#include <vector>

namespace{
Reserva* buscarReservaBinaria(LinkedList<Reserva>& reservas, const std::string& eventoId){
    if(reservas.size() == 0) return nullptr;

    std::vector<Reserva*> ordenadas;
    ordenadas.reserve(reservas.size());
    reservas.for_each([&](Reserva& r){ ordenadas.push_back(&r); });

    std::sort(ordenadas.begin(), ordenadas.end(), [](const Reserva* a, const Reserva* b){ return a->eventoId < b->eventoId; });

    int l = 0, r = (int)ordenadas.size() - 1;
    while(l <= r){
        int m = l + (r - l) / 2;
        // Búsqueda binaria #5: reservas del usuario ordenadas por eventoId
        if(ordenadas[m]->eventoId == eventoId) return ordenadas[m];
        if(ordenadas[m]->eventoId < eventoId) l = m + 1; else r = m - 1;
    }

    return nullptr;
}
}

int Usuario::totalReservadoEn(const std::string& eventoId) const{
    int total = 0;
    reservas.for_each([&](const Reserva& r){ if(r.eventoId == eventoId) total += r.total(); });
    return total;
}

Reserva* Usuario::buscarReserva(const std::string& eventoId){
    return buscarReservaBinaria(reservas, eventoId);
}

void Usuario::agregarOModificarReserva(const Reserva& r){
    Reserva* ex = buscarReserva(r.eventoId); // Usa la búsqueda binaria sobre el vector ordenado (#5)
    if(ex){ ex->acumular(r); }
    else { reservas.push_back(r); }
}

bool Usuario::eliminarReserva(const std::string& eventoId, Reserva& out){
    return reservas.remove_first([&](const Reserva& r){ return r.eventoId == eventoId; }, out);
}

bool operator==(const Usuario& a, const Usuario& b){ return a.cedula == b.cedula; }

std::ostream& operator<<(std::ostream& os, const Usuario& u){
    return os << u.cedula << " - " << u.nombre;
}
