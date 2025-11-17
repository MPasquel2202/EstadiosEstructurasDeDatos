#include "utils/InputUtils.hpp"
#include "utils/Exceptions.hpp"
#include <iostream>
#include <limits>
#include <cctype>
#include <regex>

namespace InputUtils{

    std::string leerLineaNoVacia(std::size_t minLen){
        std::string s; 
        std::getline(std::cin, s);

        // Verificar si está vacía o solo contiene espacios
        bool soloEspacios = true;
        for(char c : s){
            if(!std::isspace((unsigned char)c)){
                soloEspacios = false;
                break;
            }
        }
        if(s.empty() || soloEspacios)
            throw EntradaInvalida("Entrada vacía");

        if(s.size() < minLen)
            throw EntradaInvalida("Entrada demasiado corta");

        // Validación vía regex (no vacío)
        std::regex patron("^.+$");
        if(!std::regex_match(s, patron))
            throw EntradaInvalida("Formato inválido");

        return s;
    }

    int leerEnteroEnRango(int min, int max){
        while(true){
            std::string s; 
            std::getline(std::cin, s);

            try{
                // Verificar si está vacía o solo contiene espacios
                bool soloEspacios = true;
                for(char c : s){
                    if(!std::isspace((unsigned char)c)){
                        soloEspacios = false;
                        break;
                    }
                }
                if(s.empty() || soloEspacios)
                    throw EntradaInvalida("Entrada vacía");

                // Validar formato entero
                std::regex patron("^-?[0-9]+$");
                if(!std::regex_match(s, patron))
                    throw EntradaInvalida("Formato inválido");

                int v = std::stoi(s);

                if(v < min || v > max)
                    throw EntradaInvalida("Fuera de rango");

                return v;

            }catch(...){
                std::cout << "Valor invalido, intente de nuevo: ";
            }
        }
    }

    bool nombreValido(const std::string& s){
        if(s.size() < 2)
            return false;

        // Rechazar si es solo espacios
        bool soloEspacios = true;
        for(char c : s){
            if(!std::isspace((unsigned char)c)){
                soloEspacios = false;
                break;
            }
        }
        if(soloEspacios) 
            return false;

            // Rechazar si hay espacios al principio o al final
        if(std::isspace((unsigned char)s.front()) || std::isspace((unsigned char)s.back()))
        return false;

        std::regex patron("^[A-Za-zÁÉÍÓÚáéíóúÑñ ]{2,}$");
        return std::regex_match(s, patron);
    }

}
