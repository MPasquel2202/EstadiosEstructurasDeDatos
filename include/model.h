#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cctype>

class Boleto {
private:
    std::string tipo;
    double precio;
    std::string fechaCompra;
    std::string numeroSerie;
    std::string asiento;

public:
    Boleto(std::string t, double p, std::string f, std::string n, std::string a)
        : tipo(t), precio(p), fechaCompra(f), numeroSerie(n), asiento(a) {}

    // Getters
    std::string getTipo() const { return tipo; }
    double getPrecio() const { return precio; }
    std::string getFechaCompra() const { return fechaCompra; }
    std::string getNumeroSerie() const { return numeroSerie; }
    std::string getAsiento() const { return asiento; }
};

class Cliente {
private:
    std::string cedula;
    std::string nombre;
    std::string fechaNacimiento;
    std::vector<Boleto> boletos;

public:
    Cliente(std::string c, std::string n, std::string f)
        : cedula(c), nombre(n), fechaNacimiento(f) {}

    // Getters
    std::string getCedula() const { return cedula; }
    std::string getNombre() const { return nombre; }
    std::string getFechaNacimiento() const { return fechaNacimiento; }
    std::vector<Boleto> getBoletos() const { return boletos; }

    // Métodos
    void agregarBoleto(const Boleto& boleto) {
        boletos.push_back(boleto);
    }
};

class Nodo {
public:
    Cliente cliente;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(Cliente c) : cliente(c), siguiente(nullptr), anterior(nullptr) {}
};

class ListaDobleCircular {
private:
    Nodo* cabeza;
    Nodo* cola;

public:
    ListaDobleCircular() : cabeza(nullptr), cola(nullptr) {}

    bool estaVacia() const {
        return cabeza == nullptr;
    }

    void agregarCliente(Cliente cliente) {
        Nodo* nuevoNodo = new Nodo(cliente);
        
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
    }

    Cliente* buscarPorCedula(const std::string& cedula) {
        if (estaVacia()) {
            return nullptr;
        }

        Nodo* actual = cabeza;
        do {
            if (actual->cliente.getCedula() == cedula) {
                return &(actual->cliente);
            }
            actual = actual->siguiente;
        } while (actual != cabeza);

        return nullptr;
    }

    std::vector<Cliente> obtenerTodosClientes() const {
        std::vector<Cliente> clientes;
        if (estaVacia()) {
            return clientes;
        }

        Nodo* actual = cabeza;
        do {
            clientes.push_back(actual->cliente);
            actual = actual->siguiente;
        } while (actual != cabeza);

        return clientes;
    }

    ~ListaDobleCircular() {
        if (estaVacia()) return;

        Nodo* actual = cabeza;
        Nodo* temp;
        
        do {
            temp = actual;
            actual = actual->siguiente;
            delete temp;
        } while (actual != cabeza);
    }
};

class SistemaBoletos {
private:
    ListaDobleCircular clientes;
    std::vector<std::string> asientosGeneral;
    std::vector<std::string> asientosPalco;
    std::vector<std::string> asientosTribuna;
    
    const int PRECIO_GENERAL = 50;
    const int PRECIO_PALCO = 100;
    const int PRECIO_TRIBUNA = 75;

public:
    SistemaBoletos() {
        // Inicializar asientos disponibles
        for (int i = 1; i <= 10; i++) {
            asientosGeneral.push_back("G" + std::to_string(i));
        }
        for (int i = 1; i <= 4; i++) {
            asientosPalco.push_back("P" + std::to_string(i));
        }
        for (int i = 1; i <= 6; i++) {
            asientosTribuna.push_back("T" + std::to_string(i));
        }
    }

    bool validarCedula(const std::string& cedula) {
        if (cedula.length() < 6) return false;
        for (char c : cedula) {
            if (!std::isdigit(c)) return false;
        }
        return true;
    }

    bool validarNombre(const std::string& nombre) {
        if (nombre.length() < 2) return false;
        for (char c : nombre) {
            if (!std::isalpha(c) && !std::isspace(c)) return false;
        }
        return true;
    }

    bool validarFecha(const std::string& fechaStr) {
        // Validación simple - formato dd/mm/aaaa
        if (fechaStr.length() != 10) return false;
        if (fechaStr[2] != '/' || fechaStr[5] != '/') return false;
        
        try {
            int dia = std::stoi(fechaStr.substr(0, 2));
            int mes = std::stoi(fechaStr.substr(3, 2));
            int año = std::stoi(fechaStr.substr(6, 4));
            
            if (dia < 1 || dia > 31) return false;
            if (mes < 1 || mes > 12) return false;
            if (año < 1900 || año > 2024) return false;
            
            return true;
        } catch (...) {
            return false;
        }
    }

    int calcularEdad(const std::string& fechaNacimiento) {
        // Simplificación - asumimos formato dd/mm/aaaa
        try {
            int añoNacimiento = std::stoi(fechaNacimiento.substr(6, 4));
            // Obtener año actual (simplificado)
            std::time_t t = std::time(nullptr);
            std::tm* timePtr = std::localtime(&t);
            int añoActual = timePtr->tm_year + 1900;
            
            return añoActual - añoNacimiento;
        } catch (...) {
            return 0;
        }
    }

    std::string obtenerFechaActual() {
        std::time_t t = std::time(nullptr);
        std::tm* timePtr = std::localtime(&t);
        
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << timePtr->tm_mday << "/"
           << std::setw(2) << std::setfill('0') << (timePtr->tm_mon + 1) << "/"
           << (timePtr->tm_year + 1900);
        
        return ss.str();
    }

    std::string generarNumeroSerie() {
        static int contador = 1000;
        return "B" + std::to_string(contador++);
    }

    int asientosDisponiblesPorTipo(const std::string& tipo) {
        if (tipo == "general") return asientosGeneral.size();
        if (tipo == "palco") return asientosPalco.size();
        if (tipo == "tribuna") return asientosTribuna.size();
        return 0;
    }

    std::pair<bool, std::string> reservarBoleto(const std::string& cedula, 
                                               const std::string& nombre,
                                               const std::string& fechaNacimiento,
                                               const std::string& tipoBoleto,
                                               int cantidad) {
        // Validaciones
        if (!validarCedula(cedula)) {
            return {false, "Cédula inválida"};
        }
        
        if (!validarNombre(nombre)) {
            return {false, "Nombre inválido"};
        }
        
        if (!validarFecha(fechaNacimiento)) {
            return {false, "Fecha de nacimiento inválida"};
        }
        
        if (tipoBoleto != "general" && tipoBoleto != "palco" && tipoBoleto != "tribuna") {
            return {false, "Tipo de boleto inválido"};
        }
        
        if (cantidad <= 0) {
            return {false, "Cantidad debe ser mayor a 0"};
        }
        
        // Verificar disponibilidad
        if (asientosDisponiblesPorTipo(tipoBoleto) < cantidad) {
            return {false, "No hay suficientes asientos disponibles en " + tipoBoleto};
        }
        
        int edad = calcularEdad(fechaNacimiento);
        
        // Buscar o crear cliente
        Cliente* cliente = clientes.buscarPorCedula(cedula);
        if (!cliente) {
            Cliente nuevoCliente(cedula, nombre, fechaNacimiento);
            clientes.agregarCliente(nuevoCliente);
            cliente = clientes.buscarPorCedula(cedula);
        }
        
        // Calcular precio
        double precioBase = 0;
        std::vector<std::string>* asientosDisponibles = nullptr;
        
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
        
        double total = 0;
        std::string fechaActual = obtenerFechaActual();
        
        // Reservar boletos
        for (int i = 0; i < cantidad; i++) {
            if (!asientosDisponibles->empty()) {
                std::string asiento = asientosDisponibles->back();
                asientosDisponibles->pop_back();
                
                std::string numeroSerie = generarNumeroSerie();
                Boleto boleto(tipoBoleto, precioBase, fechaActual, numeroSerie, asiento);
                
                // Agregar boleto al cliente
                const_cast<Cliente*>(cliente)->agregarBoleto(boleto);
                total += precioBase;
            }
        }
        
        std::stringstream ss;
        ss << "Reserva exitosa. Total: $" << std::fixed << std::setprecision(2) << total;
        return {true, ss.str()};
    }

    std::pair<bool, Cliente*> imprimirBoleto(const std::string& cedula) {
        Cliente* cliente = clientes.buscarPorCedula(cedula);
        if (!cliente || cliente->getBoletos().empty()) {
            return {false, nullptr};
        }
        return {true, cliente};
    }

    void obtenerAsientosDisponibles(int& general, int& palco, int& tribuna) const {
        general = asientosGeneral.size();
        palco = asientosPalco.size();
        tribuna = asientosTribuna.size();
    }

    std::vector<std::string> getAsientosGeneral() const { return asientosGeneral; }
    std::vector<std::string> getAsientosPalco() const { return asientosPalco; }
    std::vector<std::string> getAsientosTribuna() const { return asientosTribuna; }
};

#endif
