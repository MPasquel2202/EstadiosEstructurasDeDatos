
#pragma once
#include <string>
#include <ostream>
#include "model/Fecha.hpp"

class Evento{
public:
    std::string id;
    std::string nombre;
    Fecha fecha;
};

bool operator==(const Evento& a, const Evento& b);
std::ostream& operator<<(std::ostream& os, const Evento& e);
