
#include "utils/InputUtils.hpp"
#include "utils/Exceptions.hpp"
#include <iostream>
#include <limits>
#include <cctype>

namespace InputUtils{
    std::string leerLineaNoVacia(std::size_t minLen){
        std::string s; std::getline(std::cin, s);
        if(s.size() < minLen) throw EntradaInvalida("Entrada demasiado corta");
        return s;
    }

    int leerEnteroEnRango(int min, int max){
        while(true){
            std::string s; std::getline(std::cin, s);
            try{
                int v = std::stoi(s);
                if(v < min || v > max) throw EntradaInvalida("Fuera de rango");
                return v;
            }catch(...){ std::cout << "Valor invalido, intente de nuevo: "; }
        }
    }

    bool nombreValido(const std::string& s){
        if(s.size() < 2) return false;
        for(char c: s){ if(!(std::isalpha((unsigned char)c) || std::isspace((unsigned char)c))) return false; }
        return true;
    }
}
