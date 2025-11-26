
#pragma once
#include <string>
#include <ostream>

struct Reserva {
    std::string eventoId;
    int general{0};
    int tribuna{0};
    int palco{0};
    int total() const { return general + tribuna + palco; }
    void acumular(const Reserva& r);
};

bool operator==(const Reserva& a, const Reserva& b);
std::ostream& operator<<(std::ostream& os, const Reserva& r);
