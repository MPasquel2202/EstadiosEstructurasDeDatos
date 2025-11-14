#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "view.h"
#include <functional>
#include <memory>

template<typename Model = SistemaBoletos, typename View = Vista>
class Controlador {
private:
    Model modelo;
    View vista;
    
    // Template para manejar diferentes tipos de operaciones
    template<typename Func, typename... Args>
    auto ejecutarOperacion(Func&& operacion, Args&&... args) {
        return std::invoke(std::forward<Func>(operacion), 
                          std::forward<Args>(args)...);
    }
    
    // Función lambda para validar opciones del menú
    const std::function<bool(int)> validarOpcion = [](int opcion) {
        return opcion >= 1 && opcion <= 4;
    };

public:
    // Constructor sobrecargado
    Controlador() = default;
    
    Controlador(const Model& mod, const View& vis) : modelo(mod), vista(vis) {}
    
    Controlador(Model&& mod, View&& vis) 
        : modelo(std::move(mod)), vista(std::move(vis)) {}

    void ejecutar() {
        int opcion;
        
        auto procesarMenu = [this]() {
            do {
                vista.mostrarMenu();
                std::cin >> opcion;
                
                // Lambda para manejar la opción seleccionada
                auto manejarOpcion = [this](int opc) {
                    switch (opc) {
                        case 1: reservarBoleto(); break;
                        case 2: imprimirBoleto(); break;
                        case 3: mostrarAsientosDisponibles(); break;
                        case 4: vista.mostrarMensaje("¡Gracias por usar el sistema!"); break;
                        default: vista.mostrarError("Opción inválida"); break;
                    }
                };
                
                manejarOpcion(opcion);
                
            } while (opcion != 4);
        };
        
        procesarMenu();
    }

    // Métodos sobrecargados para reservar boletos
    void reservarBoleto() {
        reservarBoleto([](const auto& resultado) {
            // Lambda por defecto para mostrar resultado
            Vista::mostrarResultadoReserva(resultado.first, resultado.second);
        });
    }
    
    template<typename Callback>
    void reservarBoleto(Callback&& callback) {
        std::string cedula, nombre, fechaNacimiento, tipoBoleto;
        int cantidad;
        
        vista.solicitarDatosReserva(cedula, nombre, fechaNacimiento, tipoBoleto, cantidad);
        
        auto operacionReserva = [&]() {
            return modelo.reservarBoleto(cedula, nombre, fechaNacimiento, tipoBoleto, cantidad);
        };
        
        auto resultado = ejecutarOperacion(operacionReserva);
        std::forward<Callback>(callback)(resultado);
    }

    // Métodos sobrecargados para imprimir boletos
    void imprimirBoleto() {
        imprimirBoleto([](bool exito, const auto& boletos) {
            // Lambda por defecto para manejar impresión
            if (exito) {
                Vista::mostrarBoletos(boletos);
            } else {
                Vista::mostrarError("Cliente no encontrado o no tiene boletos");
            }
        });
    }
    
    template<typename Callback>
    void imprimirBoleto(Callback&& callback) {
        std::string cedula = vista.solicitarCedulaImpresion();
        
        auto operacionImpresion = [&]() {
            return modelo.imprimirBoleto(cedula);
        };
        
        auto resultado = ejecutarOperacion(operacionImpresion);
        std::forward<Callback>(callback)(resultado.first, resultado.second);
    }

    // Métodos sobrecargados para mostrar asientos
    void mostrarAsientosDisponibles() {
        mostrarAsientosDisponibles([](int general, int palco, int tribuna, 
                                     int totalGeneral, int totalPalco, int totalTribuna) {
            // Lambda por defecto para mostrar asientos
            Vista::mostrarAsientosDisponibles(general, palco, tribuna,
                                             totalGeneral, totalPalco, totalTribuna);
        });
    }
    
    template<typename Callback>
    void mostrarAsientosDisponibles(Callback&& callback) {
        int general, palco, tribuna;
        
        auto operacionAsientos = [&]() {
            modelo.obtenerAsientosDisponibles(general, palco, tribuna);
        };
        
        ejecutarOperacion(operacionAsientos);
        
        std::forward<Callback>(callback)(general, palco, tribuna,
                                       modelo.getAsientosGeneral(),
                                       modelo.getAsientosPalco(),
                                       modelo.getAsientosTribuna());
    }

    // Template method pattern para operaciones genéricas
    template<typename Operation, typename... Params>
    auto ejecutarConValidacion(Operation&& op, Params&&... params) {
        // Lambda para validar y ejecutar
        auto validarYEjecutar = [&]() -> decltype(auto) {
            if constexpr (std::is_invocable_v<Operation, Params...>) {
                return std::invoke(std::forward<Operation>(op), 
                                 std::forward<Params>(params)...);
            } else {
                static_assert(sizeof...(Params) == 0, "Operación no invocable con los parámetros dados");
                return std::invoke(std::forward<Operation>(op));
            }
        };
        
        return validarYEjecutar();
    }

    // Getters sobrecargados
    const Model& getModelo() const { return modelo; }
    Model& getModelo() { return modelo; }
    
    const View& getVista() const { return vista; }
    View& getVista() { return vista; }
};

#endif