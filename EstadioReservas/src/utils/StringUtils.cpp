#include "StringUtils.hpp"
#include <algorithm>
#include <cctype>

namespace StringUtils {

    std::string ordenarLetras(const std::string& nombre) {
        std::string limpio;
        limpio.reserve(nombre.size());

        // quitar espacios
        for (char c : nombre) {
            if (!isspace(c)) {
                limpio += c;
            }
        }

        // ordenar ignorando mayúsculas/minúsculas
        std::sort(limpio.begin(), limpio.end(),
            [](char a, char b) {
                return std::tolower(a) < std::tolower(b);
            }
        );

        return limpio;
    }

}
