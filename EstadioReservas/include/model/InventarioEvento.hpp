
#pragma once
#include <string>
#include <ostream>
#include "model/BoletoTipo.hpp"
#include "model/Reserva.hpp"

class InventarioEvento{
public:
    std::string eventoId;
    int limitePorUsuario{0};
    int capGeneral{0}, capTribuna{0}, capPalco{0};
    int occGeneral{0}, occTribuna{0}, occPalco{0};

    int disponibles(BoletoTipo t) const;
    bool cabe(const Reserva& r) const;
    void ocupar(const Reserva& r);
};

bool operator==(const InventarioEvento& a, const InventarioEvento& b);
std::ostream& operator<<(std::ostream& os, const InventarioEvento& inv);
