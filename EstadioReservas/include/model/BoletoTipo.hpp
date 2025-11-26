
#pragma once
#include <string>
#include <stdexcept>

enum class BoletoTipo { GENERAL, TRIBUNA, PALCO };

inline std::string to_string(BoletoTipo t){
    switch(t){
        case BoletoTipo::GENERAL: return "GENERAL";
        case BoletoTipo::TRIBUNA: return "TRIBUNA";
        case BoletoTipo::PALCO:   return "PALCO";
    }
    return "";
}

inline BoletoTipo boleto_from_string(const std::string& s){
    if(s == "GENERAL") return BoletoTipo::GENERAL;
    if(s == "TRIBUNA") return BoletoTipo::TRIBUNA;
    if(s == "PALCO")   return BoletoTipo::PALCO;
    throw std::runtime_error("Tipo de boleto desconocido: " + s);
}
