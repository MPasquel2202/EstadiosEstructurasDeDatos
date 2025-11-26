#pragma once
#include <ctime>
#include <string>
#include "../model/Evento.hpp"

namespace Comparadores {
    // Comparador por fecha (ascendente)
    inline bool porFecha(Evento* a, Evento* b) {
        return a->fecha < b->fecha;
    }

    // Comparador por evento más cercano (fecha ascendente)
    inline bool porEventoCercano(Evento* a, Evento* b) {
        return a->fecha < b->fecha;
    }

    // Comparador por nombre
    inline bool porNombre(Evento* a, Evento* b) {
        return a->nombre < b->nombre;
    }

    // Comparadores para asientos (se manejan en OrdenadorEventos)
    inline bool porAsientosAsc(Evento* /* a */, Evento* /* b */) {
        // Estos no se usan directamente - se manejan en los métodos específicos
        return true;
    }

    inline bool porAsientosDesc(Evento* /* a */, Evento* /* b */) {
        return false;
    }
}