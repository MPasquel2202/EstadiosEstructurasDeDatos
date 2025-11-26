
#include "model/Evento.hpp"

bool operator==(const Evento& a, const Evento& b){ return a.id == b.id; }

std::ostream& operator<<(std::ostream& os, const Evento& e){
    return os << e.id << " | " << e.nombre << " | " << e.fecha;
}
