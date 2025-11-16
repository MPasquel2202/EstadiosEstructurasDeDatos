
#pragma once
#include <string>
#include "model/Fecha.hpp"

namespace DateUtils{
    Fecha hoy();
    bool esReservable(const Fecha& fechaEvento, const Fecha& hoy);
    Fecha parseISO(const std::string& s);
}
