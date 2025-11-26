
#include "model/Reserva.hpp"

void Reserva::acumular(const Reserva& r){
    if(eventoId != r.eventoId) return;
    general += r.general;
    tribuna += r.tribuna;
    palco   += r.palco;
}

bool operator==(const Reserva& a, const Reserva& b){ return a.eventoId == b.eventoId; }

std::ostream& operator<<(std::ostream& os, const Reserva& r){
    return os << "{" << r.eventoId << ": G=" << r.general << ", T=" << r.tribuna << ", P=" << r.palco << "}";
}
