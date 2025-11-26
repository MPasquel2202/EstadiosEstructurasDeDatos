
#include "model/InventarioEvento.hpp"

int InventarioEvento::disponibles(BoletoTipo t) const{
    switch(t){
        case BoletoTipo::GENERAL: return capGeneral - occGeneral;
        case BoletoTipo::TRIBUNA: return capTribuna - occTribuna;
        case BoletoTipo::PALCO:   return capPalco   - occPalco;
    }
    return 0;
}

bool InventarioEvento::cabe(const Reserva& r) const{
    if(r.general > disponibles(BoletoTipo::GENERAL)) return false;
    if(r.tribuna > disponibles(BoletoTipo::TRIBUNA)) return false;
    if(r.palco   > disponibles(BoletoTipo::PALCO))   return false;
    return true;
}

void InventarioEvento::ocupar(const Reserva& r){
    occGeneral += r.general;
    occTribuna += r.tribuna;
    occPalco   += r.palco;
}

bool operator==(const InventarioEvento& a, const InventarioEvento& b){ return a.eventoId == b.eventoId; }

std::ostream& operator<<(std::ostream& os, const InventarioEvento& inv){
    return os << inv.eventoId << " | limUsr=" << inv.limitePorUsuario
              << " | G " << inv.occGeneral << "/" << inv.capGeneral
              << " | T " << inv.occTribuna << "/" << inv.capTribuna
              << " | P " << inv.occPalco   << "/" << inv.capPalco;
}
