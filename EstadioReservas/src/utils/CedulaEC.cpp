
#include "utils/CedulaEC.hpp"
#include <cctype>
#include <string>

namespace CedulaEC{
    static bool soloDigitos(const std::string& s){
        if(s.size()!=10) return false;
        for(char c: s) if(!std::isdigit((unsigned char)c)) return false;
        return true;
    }

    bool validar(const std::string& ced){
        if(!soloDigitos(ced)) return false;
        int prov = std::stoi(ced.substr(0,2));
        if(!((prov>=1 && prov<=24) || prov==30)) return false;
        int tercer = ced[2]-'0';
        if(!(tercer>=0 && tercer<=5)) return false;
        int suma = 0;
        for(int i=0;i<9;i++){
            int val = ced[i]-'0';
            if((i%2)==0){ 
                val *= 2; if(val>9) val -= 9;
            }
            suma += val;
        }
        int verif = (10 - (suma % 10)) % 10;
        return verif == (ced[9]-'0');
    }
}
