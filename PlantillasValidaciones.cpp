#include <iostream>
#include <string>
#include <cctype>
#include <functional>
#include <algorithm>
#include <sstream>

class Validador {
public:
    // Métodos sobrecargados para diferentes tipos de validación
    
    // 1. Validar solo mayúsculas
    template<typename T>
    static bool soloMayusculas(const T& entrada) {
        if constexpr (std::is_same_v<T, std::string>) {
            return std::all_of(entrada.begin(), entrada.end(), 
                [](char c) { return std::isupper(c) || std::isspace(c); });
        } else {
            std::string str = std::to_string(entrada);
            return soloMayusculas(str);
        }
    }
    
    // 2. Validar solo números
    template<typename T>
    static bool soloNumeros(const T& entrada) {
        if constexpr (std::is_same_v<T, std::string>) {
            return !entrada.empty() && std::all_of(entrada.begin(), entrada.end(), 
                [](char c) { return std::isdigit(c); });
        } else {
            return std::is_arithmetic_v<T>;
        }
    }
    
    // 3. Limitar tamaño
    template<typename T>
    static bool limitarTamano(const T& entrada, size_t maxTamano) {
        if constexpr (std::is_same_v<T, std::string>) {
            return entrada.length() <= maxTamano;
        } else {
            std::string str = std::to_string(entrada);
            return str.length() <= maxTamano;
        }
    }
    
    // 4. Validar enteros (versión con puntero a función)
    static bool soloEnteros(const std::string& entrada) {
        if (entrada.empty()) return false;
        
        // Puntero a función para validar cada carácter
        bool (*esDigitoOPunto)(int) = [](int c) -> bool {
            return std::isdigit(c) || c == '-' || c == '+';
        };
        
        // Verificar primer carácter
        if (!esDigitoOPunto(entrada[0])) return false;
        
        // Verificar resto de caracteres
        for (size_t i = 1; i < entrada.length(); i++) {
            if (!std::isdigit(entrada[i])) return false;
        }
        
        return true;
    }
    
    // Método genérico con función lambda personalizada
    template<typename T>
    static bool validarConLambda(const T& entrada, 
                                const std::function<bool(const T&)>& criterio) {
        return criterio(entrada);
    }
};

// Función template para entrada validada con puntero a función
template<typename T>
T obtenerEntradaValidada(const std::string& mensaje, 
                        bool (*validador)(const T&), 
                        const std::string& mensajeError = "Entrada inválida!") {
    T entrada;
    while (true) {
        std::cout << mensaje;
        if constexpr (std::is_same_v<T, std::string>) {
            std::getline(std::cin, entrada);
        } else {
            std::cin >> entrada;
            std::cin.ignore(); // Limpiar buffer
        }
        
        if (validador(entrada)) {
            return entrada;
        } else {
            std::cout << mensajeError << std::endl;
        }
    }
}

// Ejemplos de uso con lambdas
class ValidadorAvanzado {
public:
    // Validación con lambda para mayúsculas
    static auto getValidadorMayusculas() {
        return [](const std::string& str) -> bool {
            return !str.empty() && std::all_of(str.begin(), str.end(),
                [](char c) { return std::isupper(c) || std::isspace(c); });
        };
    }
    
    // Validación con lambda para números
    static auto getValidadorNumeros() {
        return [](const std::string& str) -> bool {
            return !str.empty() && std::all_of(str.begin(), str.end(),
                [](char c) { return std::isdigit(c); });
        };
    }
    
    // Validación con lambda para tamaño límite
    static auto getValidadorTamano(size_t maxTamano) {
        return [maxTamano](const std::string& str) -> bool {
            return str.length() <= maxTamano;
        };
    }
    
    // Validación combinada con múltiples criterios
    static auto getValidadorCombinado(size_t minTamano, size_t maxTamano, bool requiereMayusculas = false) {
        return [minTamano, maxTamano, requiereMayusculas](const std::string& str) -> bool {
            bool tamanoValido = str.length() >= minTamano && str.length() <= maxTamano;
            bool mayusculasValido = true;
            
            if (requiereMayusculas) {
                mayusculasValido = std::all_of(str.begin(), str.end(),
                    [](char c) { return std::isupper(c) || std::isspace(c); });
            }
            
            return tamanoValido && mayusculasValido;
        };
    }
};

int main() {
    std::cout << "=== DEMOSTRACIÓN DE VALIDADORES ===" << std::endl;
    
    // 1. Validación de mayúsculas
    std::cout << "\n1. Validación de MAYÚSCULAS:" << std::endl;
    auto validadorMayus = ValidadorAvanzado::getValidadorMayusculas();
    std::string textoMayus = obtenerEntradaValidada<std::string>(
        "Ingrese texto en MAYÚSCULAS: ", 
        [](const std::string& str) -> bool {
            return Validador::soloMayusculas(str);
        },
        "Error: Solo se permiten MAYÚSCULAS!"
    );
    std::cout << "Texto válido: " << textoMayus << std::endl;
    
    // 2. Validación de números
    std::cout << "\n2. Validación de NÚMEROS:" << std::endl;
    auto validadorNumeros = ValidadorAvanzado::getValidadorNumeros();
    std::string textoNumeros = obtenerEntradaValidada<std::string>(
        "Ingrese solo números: ", 
        validadorNumeros,
        "Error: Solo se permiten números!"
    );
    std::cout << "Números válidos: " << textoNumeros << std::endl;
    
    // 3. Validación de tamaño límite
    std::cout << "\n3. Validación de TAMAÑO:" << std::endl;
    size_t maxTamano = 10;
    auto validadorTamano = ValidadorAvanzado::getValidadorTamano(maxTamano);
    std::string textoTamano = obtenerEntradaValidada<std::string>(
        "Ingrese texto (máx " + std::to_string(maxTamano) + " caracteres): ", 
        validadorTamano,
        "Error: Texto demasiado largo!"
    );
    std::cout << "Texto válido: " << textoTamano << std::endl;
    
    // 4. Validación de enteros
    std::cout << "\n4. Validación de ENTEROS:" << std::endl;
    std::string textoEntero = obtenerEntradaValidada<std::string>(
        "Ingrese un número entero: ", 
        Validador::soloEnteros,
        "Error: No es un entero válido!"
    );
    std::cout << "Entero válido: " << textoEntero << std::endl;
    
    // 5. Validación combinada
    std::cout << "\n5. Validación COMBINADA:" << std::endl;
    auto validadorCombinado = ValidadorAvanzado::getValidadorCombinado(3, 8, true);
    std::string textoCombinado = obtenerEntradaValidada<std::string>(
        "Ingrese texto (3-8 chars, MAYÚSCULAS): ", 
        validadorCombinado,
        "Error: No cumple los criterios!"
    );
    std::cout << "Texto combinado válido: " << textoCombinado << std::endl;
    
    // Ejemplos de uso directo de las plantillas
    std::cout << "\n=== PRUEBAS DIRECTAS ===" << std::endl;
    
    std::string prueba1 = "HOLA MUNDO";
    std::string prueba2 = "12345";
    std::string prueba3 = "hola";
    
    std::cout << "'" << prueba1 << "' es mayúsculas: " 
              << Validador::soloMayusculas(prueba1) << std::endl;
    std::cout << "'" << prueba2 << "' son números: " 
              << Validador::soloNumeros(prueba2) << std::endl;
    std::cout << "'" << prueba3 << "' tamaño <= 5: " 
              << Validador::limitarTamano(prueba3, 5) << std::endl;
    std::cout << "'" << prueba2 << "' es entero: " 
              << Validador::soloEnteros(prueba2) << std::endl;
    
    return 0;
}
