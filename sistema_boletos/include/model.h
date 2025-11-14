#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <functional>
#include <algorithm>
#include <memory>

// Template para políticas de validación
template<typename T>
class ValidacionPolicy {
public:
    static bool validar(const T& valor) { return true; }
};

template<>
class ValidacionPolicy<std::string> {
public:
    static bool validar(const std::string& valor) {
        return !valor.empty();
    }
};

// Template Boleto con políticas de precio
template<typename PrecioPolicy>
class Boleto {
private:
    std::string tipo;
    double precio;
    std::string fechaCompra;
    std::string numeroSerie;
    std::string asiento;
    PrecioPolicy politicaPrecio;

public:
    Boleto(std::string t, double p, std::string f, std::string n, std::string a)
        : tipo(t), precio(p), fechaCompra(f), numeroSerie(n), asiento(a) {}

    // Getters
    std::string getTipo() const { return tipo; }
    double getPrecio() const { return precio; }
    std::string getFechaCompra() const { return fechaCompra; }
    std::string getNumeroSerie() const { return numeroSerie; }
    std::string getAsiento() const { return asiento; }

    // Template method para aplicar políticas
    template<typename DescuentoPolicy>
    double calcularPrecioFinal(const DescuentoPolicy& descuento) const {
        return politicaPrecio.aplicar(precio, descuento);
    }

    // Función lambda para formatear información
    auto getInfoFormateada() const {
        return [this]() -> std::string {
            std::stringstream ss;
            ss << "Boleto " << numeroSerie << " - " << tipo 
               << " - Asiento: " << asiento << " - $" << precio;
            return ss.str();
        };
    }
};

// Políticas de precio
class PrecioBasePolicy {
public:
    double aplicar(double precio, double descuento) const {
        return precio * (1.0 - descuento);
    }
};

class PrecioConImpuestoPolicy {
public:
    double aplicar(double precio, double descuento) const {
        return (precio * (1.0 - descuento)) * 1.15; // 15% impuesto
    }
};

// Template Cliente con gestión de boletos
template<typename BoletoType>
class Cliente {
private:
    std::string cedula;
    std::string nombre;
    std::string fechaNacimiento;
    std::vector<BoletoType> boletos;

public:
    Cliente(std::string c, std::string n, std::string f)
        : cedula(c), nombre(n), fechaNacimiento(f) {}

    // Getters
    std::string getCedula() const { return cedula; }
    std::string getNombre() const { return nombre; }
    std::string getFechaNacimiento() const { return fechaNacimiento; }
    std::vector<BoletoType> getBoletos() const { return boletos; }

    // Métodos sobrecargados para agregar boletos
    void agregarBoleto(const BoletoType& boleto) {
        boletos.push_back(boleto);
    }

    template<typename... Args>
    void agregarBoleto(Args&&... args) {
        boletos.emplace_back(std::forward<Args>(args)...);
    }

    // Función lambda para filtrar boletos
    auto filtrarBoletos(const std::string& tipo) const {
        return [this, tipo]() -> std::vector<BoletoType> {
            std::vector<BoletoType> resultado;
            std::copy_if(boletos.begin(), boletos.end(), 
                        std::back_inserter(resultado),
                        [&tipo](const BoletoType& boleto) {
                            return boleto.getTipo() == tipo;
                        });
            return resultado;
        };
    }

    // Template method para procesar boletos
    template<typename Func>
    void procesarBoletos(Func&& procesador) const {
        for (const auto& boleto : boletos) {
            procesador(boleto);
        }
    }

    // Método sobrecargado para obtener total
    double getTotalGastado() const {
        return getTotalGastado([](const BoletoType& b) { return b.getPrecio(); });
    }

    template<typename PrecioFunc>
    double getTotalGastado(PrecioFunc&& precioFunc) const {
        double total = 0.0;
        procesarBoletos([&total, &precioFunc](const BoletoType& boleto) {
            total += precioFunc(boleto);
        });
        return total;
    }
};

// Template Nodo para lista doble circular
template<typename T>
class Nodo {
public:
    T dato;
    std::shared_ptr<Nodo<T>> siguiente;
    std::shared_ptr<Nodo<T>> anterior;

    Nodo(T d) : dato(d), siguiente(nullptr), anterior(nullptr) {}
};

// Template ListaDobleCircular con iteradores
template<typename T>
class ListaDobleCircular {
private:
    std::shared_ptr<Nodo<T>> cabeza;
    std::shared_ptr<Nodo<T>> cola;
    size_t tamaño;

public:
    ListaDobleCircular() : cabeza(nullptr), cola(nullptr), tamaño(0) {}

    bool estaVacia() const {
        return cabeza == nullptr;
    }

    size_t getTamaño() const {
        return tamaño;
    }

    // Métodos sobrecargados para agregar
    void agregar(const T& dato) {
        auto nuevoNodo = std::make_shared<Nodo<T>>(dato);
        
        if (estaVacia()) {
            cabeza = nuevoNodo;
            cola = nuevoNodo;
            nuevoNodo->siguiente = nuevoNodo;
            nuevoNodo->anterior = nuevoNodo;
        } else {
            nuevoNodo->anterior = cola;
            nuevoNodo->siguiente = cabeza;
            cola->siguiente = nuevoNodo;
            cabeza->anterior = nuevoNodo;
            cola = nuevoNodo;
        }
        tamaño++;
    }

    void agregar(T&& dato) {
        auto nuevoNodo = std::make_shared<Nodo<T>>(std::move(dato));
        
        if (estaVacia()) {
            cabeza = nuevoNodo;
            cola = nuevoNodo;
            nuevoNodo->siguiente = nuevoNodo;
            nuevoNodo->anterior = nuevoNodo;
        } else {
            nuevoNodo->anterior = cola;
            nuevoNodo->siguiente = cabeza;
            cola->siguiente = nuevoNodo;
            cabeza->anterior = nuevoNodo;
            cola = nuevoNodo;
        }
        tamaño++;
    }

    // Template method para búsqueda con predicado
    template<typename Predicado>
    std::shared_ptr<Nodo<T>> buscar(Predicado&& predicado) const {
        if (estaVacia()) {
            return nullptr;
        }

        auto actual = cabeza;
        do {
            if (predicado(actual->dato)) {
                return actual;
            }
            actual = actual->siguiente;
        } while (actual != cabeza);

        return nullptr;
    }

    // Búsqueda específica por cédula (para clientes)
    template<typename = std::enable_if_t<std::is_same_v<T, Cliente<Boleto<PrecioBasePolicy>>>>>
    std::shared_ptr<Nodo<T>> buscarPorCedula(const std::string& cedula) const {
        return buscar([&cedula](const T& cliente) {
            return cliente.getCedula() == cedula;
        });
    }

    // Template method para procesar todos los elementos
    template<typename Func>
    void forEach(Func&& funcion) const {
        if (estaVacia()) return;

        auto actual = cabeza;
        do {
            funcion(actual->dato);
            actual = actual->siguiente;
        } while (actual != cabeza);
    }

    // Función lambda para obtener todos los elementos
    auto obtenerTodos() const {
        return [this]() -> std::vector<T> {
            std::vector<T> elementos;
            forEach([&elementos](const T& elemento) {
                elementos.push_back(elemento);
            });
            return elementos;
        };
    }
};

// Template SistemaBoletos con políticas configurables
template<typename ClienteType = Cliente<Boleto<PrecioBasePolicy>>,
         typename ListaType = ListaDobleCircular<ClienteType>,
         typename ValidacionType = ValidacionPolicy<std::string>>
class SistemaBoletos {
private:
    ListaType clientes;
    std::vector<std::string> asientosGeneral;
    std::vector<std::string> asientosPalco;
    std::vector<std::string> asientosTribuna;
    
    const int PRECIO_GENERAL = 50;
    const int PRECIO_PALCO = 100;
    const int PRECIO_TRIBUNA = 75;
    ValidacionType validador;

    // Función lambda para inicializar asientos
    auto inicializarAsientos = [this](const std::string& prefijo, int cantidad) {
        std::vector<std::string> asientos;
        for (int i = 1; i <= cantidad; i++) {
            asientos.push_back(prefijo + std::to_string(i));
        }
        return asientos;
    };

public:
    SistemaBoletos() {
        // Inicializar asientos usando lambdas
        asientosGeneral = inicializarAsientos("G", 10);
        asientosPalco = inicializarAsientos("P", 4);
        asientosTribuna = inicializarAsientos("T", 6);
    }

    // Métodos de validación sobrecargados
    bool validarCedula(const std::string& cedula) {
        return validarCedula(cedula, [](const std::string& c) {
            return c.length() >= 6 && 
                   std::all_of(c.begin(), c.end(), ::isdigit);
        });
    }

    template<typename ValidacionFunc>
    bool validarCedula(const std::string& cedula, ValidacionFunc&& validador) {
        return validador(cedula);
    }

    bool validarNombre(const std::string& nombre) {
        return validarNombre(nombre, [](const std::string& n) {
            return n.length() >= 2 && 
                   std::all_of(n.begin(), n.end(), [](char c) {
                       return std::isalpha(c) || std::isspace(c);
                   });
        });
    }

    template<typename ValidacionFunc>
    bool validarNombre(const std::string& nombre, ValidacionFunc&& validador) {
        return validador(nombre);
    }

    bool validarFecha(const std::string& fechaStr) {
        return validarFecha(fechaStr, [](const std::string& f) {
            if (f.length() != 10 || f[2] != '/' || f[5] != '/') 
                return false;
            
            try {
                int dia = std::stoi(f.substr(0, 2));
                int mes = std::stoi(f.substr(3, 2));
                int año = std::stoi(f.substr(6, 4));
                
                return dia >= 1 && dia <= 31 && 
                       mes >= 1 && mes <= 12 && 
                       año >= 1900 && año <= 2024;
            } catch (...) {
                return false;
            }
        });
    }

    template<typename ValidacionFunc>
    bool validarFecha(const std::string& fechaStr, ValidacionFunc&& validador) {
        return validador(fechaStr);
    }

    // Template method para calcular edad
    template<typename TimeProvider = std::function<std::tm*()>>
    int calcularEdad(const std::string& fechaNacimiento, TimeProvider&& timeProvider = []() {
        std::time_t t = std::time(nullptr);
        return std::localtime(&t);
    }) {
        try {
            int añoNacimiento = std::stoi(fechaNacimiento.substr(6, 4));
            auto timePtr = timeProvider();
            int añoActual = timePtr->tm_year + 1900;
            return añoActual - añoNacimiento;
        } catch (...) {
            return 0;
        }
    }

    std::string obtenerFechaActual() {
        return obtenerFechaActual([]() {
            std::time_t t = std::time(nullptr);
            return std::localtime(&t);
        });
    }

    template<typename TimeProvider>
    std::string obtenerFechaActual(TimeProvider&& timeProvider) {
        auto timePtr = timeProvider();
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << timePtr->tm_mday << "/"
           << std::setw(2) << std::setfill('0') << (timePtr->tm_mon + 1) << "/"
           << (timePtr->tm_year + 1900);
        return ss.str();
    }

    // Función lambda para generar números de serie
    auto generarNumeroSerie = [contador = 1000]() mutable {
        return "B" + std::to_string(contador++);
    };

    // Métodos sobrecargados para asientos disponibles
    int asientosDisponiblesPorTipo(const std::string& tipo) {
        return asientosDisponiblesPorTipo(tipo, [this](const std::string& t) {
            if (t == "general") return asientosGeneral.size();
            if (t == "palco") return asientosPalco.size();
            if (t == "tribuna") return asientosTribuna.size();
            return size_t(0);
        });
    }

    template<typename AsientosFunc>
    int asientosDisponiblesPorTipo(const std::string& tipo, AsientosFunc&& asientosFunc) {
        return asientosFunc(tipo);
    }

    // Template method para reservar boletos
    template<typename BoletoCreator = std::function<Boleto<PrecioBasePolicy>(std::string, double, std::string, std::string, std::string)>>
    std::pair<bool, std::string> reservarBoleto(const std::string& cedula, 
                                               const std::string& nombre,
                                               const std::string& fechaNacimiento,
                                               const std::string& tipoBoleto,
                                               int cantidad,
                                               BoletoCreator&& boletoCreator = nullptr) {
        // Validaciones usando funciones lambda
        auto validaciones = {
            std::make_pair(validarCedula(cedula), "Cédula inválida"),
            std::make_pair(validarNombre(nombre), "Nombre inválido"),
            std::make_pair(validarFecha(fechaNacimiento), "Fecha de nacimiento inválida"),
            std::make_pair(tipoBoleto == "general" || tipoBoleto == "palco" || tipoBoleto == "tribuna", 
                          "Tipo de boleto inválido"),
            std::make_pair(cantidad > 0, "Cantidad debe ser mayor a 0")
        };

        for (const auto& [valido, mensaje] : validaciones) {
            if (!valido) return {false, mensaje};
        }

        if (asientosDisponiblesPorTipo(tipoBoleto) < cantidad) {
            return {false, "No hay suficientes asientos disponibles en " + tipoBoleto};
        }

        int edad = calcularEdad(fechaNacimiento);
        
        // Buscar o crear cliente
        auto nodoCliente = clientes.buscarPorCedula(cedula);
        if (!nodoCliente) {
            clientes.agregar(ClienteType(cedula, nombre, fechaNacimiento));
            nodoCliente = clientes.buscarPorCedula(cedula);
        }

        // Configurar boleto
        double precioBase = 0;
        std::vector<std::string>* asientosDisponibles = nullptr;
        
        auto configurarBoleto = [&]() {
            if (tipoBoleto == "general") {
                precioBase = PRECIO_GENERAL;
                asientosDisponibles = &asientosGeneral;
            } else if (tipoBoleto == "palco") {
                precioBase = PRECIO_PALCO;
                asientosDisponibles = &asientosPalco;
            } else if (tipoBoleto == "tribuna") {
                precioBase = PRECIO_TRIBUNA;
                asientosDisponibles = &asientosTribuna;
            }
            
            // Aplicar descuento para niños
            if (edad <= 12) {
                precioBase *= 0.5;
            }
        };

        configurarBoleto();

        double total = 0;
        std::string fechaActual = obtenerFechaActual();

        // Reservar boletos
        for (int i = 0; i < cantidad; i++) {
            if (!asientosDisponibles->empty()) {
                std::string asiento = asientosDisponibles->back();
                asientosDisponibles->pop_back();
                
                std::string numeroSerie = generarNumeroSerie();
                
                if (boletoCreator) {
                    auto boleto = boletoCreator(tipoBoleto, precioBase, fechaActual, numeroSerie, asiento);
                    nodoCliente->dato.agregarBoleto(boleto);
                } else {
                    nodoCliente->dato.agregarBoleto(tipoBoleto, precioBase, fechaActual, numeroSerie, asiento);
                }
                
                total += precioBase;
            }
        }

        std::stringstream ss;
        ss << "Reserva exitosa. Total: $" << std::fixed << std::setprecision(2) << total;
        return {true, ss.str()};
    }

    // Métodos sobrecargados para imprimir boleto
    std::pair<bool, ClienteType*> imprimirBoleto(const std::string& cedula) {
        return imprimirBoleto(cedula, [](const ClienteType& cliente) {
            return !cliente.getBoletos().empty();
        });
    }

    template<typename CondicionFunc>
    std::pair<bool, ClienteType*> imprimirBoleto(const std::string& cedula, CondicionFunc&& condicion) {
        auto nodoCliente = clientes.buscarPorCedula(cedula);
        if (!nodoCliente || !condicion(nodoCliente->dato)) {
            return {false, nullptr};
        }
        return {true, &nodoCliente->dato};
    }

    void obtenerAsientosDisponibles(int& general, int& palco, int& tribuna) const {
        general = asientosGeneral.size();
        palco = asientosPalco.size();
        tribuna = asientosTribuna.size();
    }

    // Template method para obtener asientos con formateo
    template<typename Formatter>
    auto obtenerAsientosDisponibles(Formatter&& formatter) const {
        int general, palco, tribuna;
        obtenerAsientosDisponibles(general, palco, tribuna);
        return formatter(general, palco, tribuna);
    }

    std::vector<std::string> getAsientosGeneral() const { return asientosGeneral; }
    std::vector<std::string> getAsientosPalco() const { return asientosPalco; }
    std::vector<std::string> getAsientosTribuna() const { return asientosTribuna; }

    // Función lambda para obtener estadísticas
    auto obtenerEstadisticas() const {
        return [this]() -> std::string {
            int general, palco, tribuna;
            obtenerAsientosDisponibles(general, palco, tribuna);
            
            std::stringstream ss;
            ss << "Asientos disponibles - General: " << general 
               << ", Palco: " << palco << ", Tribuna: " << tribuna
               << "\nTotal clientes: " << clientes.getTamaño();
            return ss.str();
        };
    }
};

#endif
