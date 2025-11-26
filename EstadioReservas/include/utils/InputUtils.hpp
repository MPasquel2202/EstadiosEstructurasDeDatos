
#pragma once
#include <string>

namespace InputUtils{
    std::string leerLineaNoVacia(std::size_t minLen = 1);
    int leerEnteroEnRango(int min, int max);
    bool nombreValido(const std::string& s);
}
