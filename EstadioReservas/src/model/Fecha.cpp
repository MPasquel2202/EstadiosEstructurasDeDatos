
#include "model/Fecha.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>

std::string Fecha::iso() const{
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << y << "-" << std::setw(2) << m << "-" << std::setw(2) << d;
    return oss.str();
}

Fecha Fecha::hoy(){
    std::time_t t = std::time(nullptr);
    std::tm* lt = std::localtime(&t);
    return Fecha{lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday};
}

Fecha Fecha::parseISO(const std::string& s){
    if(s.size()!=10 || s[4]!='-' || s[7]!='-') throw std::runtime_error("Formato de fecha invalido: "+s);
    int Y = std::stoi(s.substr(0,4));
    int M = std::stoi(s.substr(5,2));
    int D = std::stoi(s.substr(8,2));
    return Fecha{Y,M,D};
}

bool operator==(const Fecha& a, const Fecha& b){ return a.y==b.y && a.m==b.m && a.d==b.d; }

static int toDays(const Fecha& f){
    int y = f.y;
    int m = f.m;
    int d = f.d;
    if(m < 3){ y--; m += 12; }
    long long A = y/100; long long B = 2 - A + A/4;
    long long days = (long long)(365.25*(y+4716)) + (long long)(30.6001*(m+1)) + d + B - 1524;
    return (int)days;
}

bool operator<(const Fecha& a, const Fecha& b){
    return toDays(a) < toDays(b);
}

std::ostream& operator<<(std::ostream& os, const Fecha& f){
    return os << f.iso();
}
