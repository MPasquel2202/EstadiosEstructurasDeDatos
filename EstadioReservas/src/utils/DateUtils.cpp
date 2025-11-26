
#include "utils/DateUtils.hpp"

namespace DateUtils{
    Fecha hoy(){ return Fecha::hoy(); }

    bool esReservable(const Fecha& fechaEvento, const Fecha& h){
        auto toKey = [](const Fecha& f){ return f.y*10000 + f.m*100 + f.d; };
        return toKey(h) < toKey(fechaEvento);
    }

    Fecha parseISO(const std::string& s){ return Fecha::parseISO(s); }
}
