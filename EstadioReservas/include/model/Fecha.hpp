
#pragma once
#include <string>
#include <ostream>

struct Fecha{
    int y{1970}, m{1}, d{1};
    std::string iso() const;
    static Fecha hoy();
    static Fecha parseISO(const std::string& s); 
};

bool operator==(const Fecha& a, const Fecha& b);
bool operator<(const Fecha& a, const Fecha& b);
inline bool operator<=(const Fecha& a, const Fecha& b){ return (a<b)|| (a==b); }
std::ostream& operator<<(std::ostream& os, const Fecha& f);
