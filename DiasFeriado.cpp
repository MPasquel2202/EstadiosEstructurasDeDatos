#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>

// Template para fecha genérica
template<typename T>
class Fecha {
private:
    T dia, mes, anio;
public:
    Fecha(T d, T m, T a) : dia(d), mes(m), anio(a) {}
    
    // Métodos sobrecargados
    void mostrarFecha() const {
        std::cout << dia << "/" << mes << "/" << anio;
    }
    
    void mostrarFecha(const std::string& formato) const {
        if (formato == "americano") {
            std::cout << mes << "/" << dia << "/" << anio;
        } else {
            std::cout << dia << "/" << mes << "/" << anio;
        }
    }
    
    // Getters
    T getDia() const { return dia; }
    T getMes() const { return mes; }
    T getAnio() const { return anio; }
    
    // Sobrecarga del operador ==
    bool operator==(const Fecha& otra) const {
        return dia == otra.dia && mes == otra.mes && anio == otra.anio;
    }
    
    // Sobrecarga del operador < para ordenamiento
    bool operator<(const Fecha& otra) const {
        if (anio != otra.anio) return anio < otra.anio;
        if (mes != otra.mes) return mes < otra.mes;
        return dia < otra.dia;
    }
};

// Clase para días feriados
class DiaFeriado {
private:
    Fecha<int> fecha;
    std::string nombre;
    std::string tipo; // nacional, regional, etc.
    
public:
    DiaFeriado(int d, int m, int a, const std::string& n, const std::string& t = "nacional")
        : fecha(d, m, a), nombre(n), tipo(t) {}
    
    // Métodos sobrecargados
    void mostrarInfo() const {
        std::cout << "Feriado: " << nombre << " - ";
        fecha.mostrarFecha();
        std::cout << " - Tipo: " << tipo;
    }
    
    void mostrarInfo(bool detallado) const {
        if (detallado) {
            std::cout << "=== INFORMACIÓN DETALLADA ===" << std::endl;
            std::cout << "Nombre: " << nombre << std::endl;
            std::cout << "Fecha: ";
            fecha.mostrarFecha();
            std::cout << std::endl;
            std::cout << "Tipo: " << tipo << std::endl;
        } else {
            mostrarInfo();
        }
    }
    
    // Getters
    const Fecha<int>& getFecha() const { return fecha; }
    std::string getNombre() const { return nombre; }
    std::string getTipo() const { return tipo; }
    
    // Validar si la fecha es válida
    bool esFechaValida() const {
        auto dia = fecha.getDia();
        auto mes = fecha.getMes();
        
        if (mes < 1 || mes > 12) return false;
        if (dia < 1) return false;
        
        // Días por mes
        int diasPorMes[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return dia <= diasPorMes[mes - 1];
    }
};

// Gestor de días feriados usando templates
template<typename Container>
class GestorFeriados {
private:
    Container feriados;
    
public:
    // Método template para agregar feriados
    template<typename... Args>
    void agregarFeriado(Args&&... args) {
        feriados.emplace_back(std::forward<Args>(args)...);
    }
    
    // Buscar feriado por fecha - usando lambda
    std::shared_ptr<DiaFeriado> buscarPorFecha(const Fecha<int>& fecha) {
        auto it = std::find_if(feriados.begin(), feriados.end(),
            [&fecha](const DiaFeriado& feriado) {
                return feriado.getFecha() == fecha;
            });
        
        if (it != feriados.end()) {
            return std::make_shared<DiaFeriado>(*it);
        }
        return nullptr;
    }
    
    // Buscar feriados por nombre - usando lambda
    std::vector<std::shared_ptr<DiaFeriado>> buscarPorNombre(const std::string& nombre) {
        std::vector<std::shared_ptr<DiaFeriado>> resultados;
        
        std::for_each(feriados.begin(), feriados.end(),
            [&resultados, &nombre](const DiaFeriado& feriado) {
                if (feriado.getNombre().find(nombre) != std::string::npos) {
                    resultados.push_back(std::make_shared<DiaFeriado>(feriado));
                }
            });
        
        return resultados;
    }
    
    // Validar si una fecha es feriado
    bool esFeriado(const Fecha<int>& fecha) {
        return buscarPorFecha(fecha) != nullptr;
    }
    
    // Mostrar todos los feriados
    void mostrarTodos() const {
        std::cout << "=== LISTA DE DÍAS FERIADOS ===" << std::endl;
        for (const auto& feriado : feriados) {
            feriado.mostrarInfo();
            std::cout << std::endl;
        }
    }
    
    // Obtener cantidad de feriados
    size_t cantidadFeriados() const {
        return feriados.size();
    }
};

// Función template para validar formato de fecha
template<typename T>
bool validarFormatoFecha(T dia, T mes, T anio) {
    auto lambdaValidar = [](T d, T m, T a) -> bool {
        if (m < 1 || m > 12) return false;
        if (d < 1 || d > 31) return false;
        if (a < 2000 || a > 2100) return false; // Rango razonable
        
        // Validación básica de días por mes
        if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) return false;
        if (m == 2 && d > 29) return false;
        
        return true;
    };
    
    return lambdaValidar(dia, mes, anio);
}

int main() {
    std::cout << "=== SISTEMA DE GESTIÓN DE DÍAS FERIADOS ===" << std::endl;
    
    // Usando lista simple (std::list) para feriados nacionales
    GestorFeriados<std::list<DiaFeriado>> gestorSimple;
    
    // Usando lista doble (std::vector) para todos los feriados
    GestorFeriados<std::vector<DiaFeriado>> gestorDoble;
    
    // Agregar feriados usando métodos template
    gestorSimple.agregarFeriado(1, 1, 2024, "Año Nuevo", "nacional");
    gestorSimple.agregarFeriado(25, 12, 2024, "Navidad", "nacional");
    gestorSimple.agregarFeriado(1, 5, 2024, "Día del Trabajo", "nacional");
    
    gestorDoble.agregarFeriado(1, 1, 2024, "Año Nuevo", "nacional");
    gestorDoble.agregarFeriado(6, 1, 2024, "Reyes Magos", "nacional");
    gestorDoble.agregarFeriado(25, 3, 2024, "Día Regional", "regional");
    gestorDoble.agregarFeriado(1, 5, 2024, "Día del Trabajo", "nacional");
    gestorDoble.agregarFeriado(15, 8, 2024, "Asunción", "nacional");
    gestorDoble.agregarFeriado(12, 10, 2024, "Día de la Hispanidad", "nacional");
    gestorDoble.agregarFeriado(1, 11, 2024, "Todos los Santos", "nacional");
    gestorDoble.agregarFeriado(6, 12, 2024, "Día de la Constitución", "nacional");
    gestorDoble.agregarFeriado(25, 12, 2024, "Navidad", "nacional");
    
    // Menú interactivo
    int opcion;
    do {
        std::cout << "\n=== MENÚ PRINCIPAL ===" << std::endl;
        std::cout << "1. Ver todos los feriados" << std::endl;
        std::cout << "2. Buscar feriado por fecha" << std::endl;
        std::cout << "3. Buscar feriado por nombre" << std::endl;
        std::cout << "4. Validar si una fecha es feriado" << std::endl;
        std::cout << "5. Validar formato de fecha" << std::endl;
        std::cout << "6. Estadísticas" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        
        switch (opcion) {
            case 1: {
                std::cout << "\n--- LISTA SIMPLE ---" << std::endl;
                gestorSimple.mostrarTodos();
                std::cout << "\n--- LISTA DOBLE ---" << std::endl;
                gestorDoble.mostrarTodos();
                break;
            }
            
            case 2: {
                int d, m, a;
                std::cout << "Ingrese fecha (dia mes año): ";
                std::cin >> d >> m >> a;
                
                Fecha<int> fecha(d, m, a);
                auto feriado = gestorDoble.buscarPorFecha(fecha);
                
                if (feriado) {
                    std::cout << "✓ ENCONTRADO: ";
                    feriado->mostrarInfo(true);
                } else {
                    std::cout << "✗ No se encontró feriado para esa fecha" << std::endl;
                }
                break;
            }
            
            case 3: {
                std::string nombre;
                std::cout << "Ingrese nombre o parte del nombre: ";
                std::cin.ignore();
                std::getline(std::cin, nombre);
                
                auto resultados = gestorDoble.buscarPorNombre(nombre);
                
                if (!resultados.empty()) {
                    std::cout << "Resultados encontrados (" << resultados.size() << "):" << std::endl;
                    for (const auto& feriado : resultados) {
                        feriado->mostrarInfo();
                        std::cout << std::endl;
                    }
                } else {
                    std::cout << "No se encontraron feriados con ese nombre" << std::endl;
                }
                break;
            }
            
            case 4: {
                int d, m, a;
                std::cout << "Ingrese fecha a validar (dia mes año): ";
                std::cin >> d >> m >> a;
                
                Fecha<int> fecha(d, m, a);
                if (gestorDoble.esFeriado(fecha)) {
                    std::cout << "✓ La fecha ES feriado" << std::endl;
                    auto feriado = gestorDoble.buscarPorFecha(fecha);
                    feriado->mostrarInfo();
                    std::cout << std::endl;
                } else {
                    std::cout << "✗ La fecha NO es feriado" << std::endl;
                }
                break;
            }
            
            case 5: {
                int d, m, a;
                std::cout << "Ingrese fecha para validar formato (dia mes año): ";
                std::cin >> d >> m >> a;
                
                if (validarFormatoFecha(d, m, a)) {
                    std::cout << "✓ Formato de fecha VÁLIDO" << std::endl;
                } else {
                    std::cout << "✗ Formato de fecha INVÁLIDO" << std::endl;
                }
                break;
            }
            
            case 6: {
                std::cout << "=== ESTADÍSTICAS ===" << std::endl;
                std::cout << "Feriados en lista simple: " << gestorSimple.cantidadFeriados() << std::endl;
                std::cout << "Feriados en lista doble: " << gestorDoble.cantidadFeriados() << std::endl;
                break;
            }
            
            case 0:
                std::cout << "¡Hasta luego!" << std::endl;
                break;
                
            default:
                std::cout << "Opción inválida" << std::endl;
        }
        
    } while (opcion != 0);
    
    return 0;
}
