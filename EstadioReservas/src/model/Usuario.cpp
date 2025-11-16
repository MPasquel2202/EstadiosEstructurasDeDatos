#include "model/Usuario.hpp"

int Usuario::totalReservadoEn(const std::string& eventoId) const{
    int total = 0;
    reservas.for_each([&](const Reserva& r){ if(r.eventoId == eventoId) total += r.total(); });
    return total;
}

Reserva* Usuario::buscarReserva(const std::string& eventoId){
    return reservas.find([&](const Reserva& r){ return r.eventoId == eventoId; });
}

void Usuario::agregarOModificarReserva(const Reserva& r){
    Reserva* ex = buscarReserva(r.eventoId);
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
