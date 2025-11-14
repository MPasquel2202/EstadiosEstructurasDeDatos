#include <iostream>
#include <memory>
#include <functional>
#include <variant>
#include <any>
#include "model.h"
#include "view.h"
#include "controller.h"

// Template para configuración del sistema
template<typename ModelType, typename ViewType, typename ControllerType>
struct SistemaConfig {
    using Model = ModelType;
    using View = ViewType;
    using Controller = ControllerType;
    
    std::string nombre;
    std::string version;
    std::function<void()> onInicio;
    std::function<void()> onFinalizacion;
};

// Template Factory para crear componentes del sistema
template<typename Config>
class SistemaFactory {
public:
    static auto crearModelo() {
        return typename Config::Model();
    }
    
    static auto crearVista() {
        return typename Config::View();
    }
    
    static auto crearControlador(auto&& modelo, auto&& vista) {
        return typename Config::Controller(std::forward<decltype(modelo)>(modelo), 
                                         std::forward<decltype(vista)>(vista));
    }
};

// Configuración por defecto del sistema
using ConfigDefault = SistemaConfig<
    SistemaBoletos<>,  // Modelo por defecto
    Vista<>,           // Vista por defecto  
    Controlador<>      // Controlador por defecto
>;

// Configuración alternativa con políticas diferentes
using ConfigPremium = SistemaConfig<
    SistemaBoletos<Cliente<Boleto<PrecioConImpuestoPolicy>>, ListaDobleCircular<Cliente<Boleto<PrecioConImpuestoPolicy>>>, ValidacionPolicy<std::string>>,
    Vista<Cliente<Boleto<PrecioConImpuestoPolicy>>, FormatoPolicy<std::string>>,
    Controlador<SistemaBoletos<Cliente<Boleto<PrecioConImpuestoPolicy>>, ListaDobleCircular<Cliente<Boleto<PrecioConImpuestoPolicy>>>, ValidacionPolicy<std::string>>, 
                Vista<Cliente<Boleto<PrecioConImpuestoPolicy>>, FormatoPolicy<std::string>>>
>;

// Template para el gestor principal de la aplicación
template<typename Config = ConfigDefault>
class GestorAplicacion {
private:
    using ModelType = typename Config::Model;
    using ViewType = typename Config::View;
    using ControllerType = typename Config::Controller;
    
    std::unique_ptr<ModelType> modelo;
    std::unique_ptr<ViewType> vista;
    std::unique_ptr<ControllerType> controlador;
    Config config;

public:
    GestorAplicacion(Config cfg = Config()) : config(std::move(cfg)) {
        inicializar();
    }

    void inicializar() {
        // Lambda para inicialización con manejo de excepciones
        auto inicializarSeguro = [this]() -> bool {
            try {
                modelo = std::make_unique<ModelType>(SistemaFactory<Config>::crearModelo());
                vista = std::make_unique<ViewType>(SistemaFactory<Config>::crearVista());
                controlador = std::make_unique<ControllerType>(
                    SistemaFactory<Config>::crearControlador(*modelo, *vista)
                );
                
                if (config.onInicio) {
                    config.onInicio();
                }
                
                return true;
            } catch (const std::exception& e) {
                std::cerr << "Error inicializando aplicación: " << e.what() << std::endl;
                return false;
            }
        };

        if (!inicializarSeguro()) {
            throw std::runtime_error("No se pudo inicializar la aplicación");
        }
    }

    void ejecutar() {
        // Lambda para ejecución principal con manejo de estados
        auto ejecutarAplicacion = [this]() {
            std::cout << "Iniciando " << config.nombre 
                      << " v" << config.version << std::endl;
            
            mostrarBanner();
            
            try {
                controlador->ejecutar();
            } catch (const std::exception& e) {
                std::cerr << "Error durante la ejecución: " << e.what() << std::endl;
            }
            
            if (config.onFinalizacion) {
                config.onFinalizacion();
            }
            
            std::cout << "Aplicación finalizada correctamente." << std::endl;
        };

        ejecutarAplicacion();
    }

private:
    void mostrarBanner() {
        auto banner = []() {
            std::cout << R"(
    ╔══════════════════════════════════════════════╗
    ║           SISTEMA DE GESTIÓN DE BOLETOS      ║
    ║              (Versión Template++)            ║
    ║                                              ║
    ║  Características:                            ║
    ║  • Templates avanzados                       ║
    ║  • Funciones lambda                         ║
    ║  • Métodos sobrecargados                    ║
    ║  • Políticas configurables                  ║
    ║  • Gestión de memoria inteligente           ║
    ╚══════════════════════════════════════════════╝
            )" << std::endl;
        };
        
        banner();
    }
};

// Función template para demostrar características del sistema
template<typename Sistema>
void demostrarCaracteristicas(Sistema& sistema) {
    std::cout << "\n=== DEMOSTRACIÓN DE CARACTERÍSTICAS ===" << std::endl;
    
    // Lambda para mostrar características de templates
    auto mostrarTemplates = []() {
        std::cout << "1. Templates utilizados:" << std::endl;
        std::cout << "   - SistemaBoletos con políticas" << std::endl;
        std::cout << "   - Vista con formateadores" << std::endl;
        std::cout << "   - Controlador genérico" << std::endl;
        std::cout << "   - Lista doble circular template" << std::endl;
    };
    
    // Lambda para mostrar características de lambdas
    auto mostrarLambdas = []() {
        std::cout << "2. Funciones lambda implementadas:" << std::endl;
        std::cout << "   - Validaciones personalizadas" << std::endl;
        std::cout << "   - Formateo de datos" << std::endl;
        std::cout << "   - Procesamiento de colecciones" << std::endl;
        std::cout << "   - Callbacks y handlers" << std::endl;
    };
    
    // Lambda para mostrar métodos sobrecargados
    auto mostrarSobrecarga = []() {
        std::cout << "3. Métodos sobrecargados:" << std::endl;
        std::cout << "   - Reserva de boletos con callbacks" << std::endl;
        std::cout << "   - Múltiples formas de mostrar datos" << std::endl;
        std::cout << "   - Diferentes estrategias de validación" << std::endl;
    };
    
    mostrarTemplates();
    mostrarLambdas();
    mostrarSobrecarga();
}

// Función template para crear diferentes configuraciones
template<typename ConfigType>
auto crearSistemaConfigurado() {
    ConfigType config;
    config.nombre = "Sistema de Boletos Avanzado";
    config.version = "2.0";
    
    config.onInicio = []() {
        std::cout << " Inicializando sistema..." << std::endl;
    };
    
    config.onFinalizacion = []() {
        std::cout << " Cerrando sistema..." << std::endl;
    };
    
    return config;
}

// Variant para manejar diferentes tipos de sistemas
using SistemaVariant = std::variant<
    GestorAplicacion<ConfigDefault>,
    GestorAplicacion<ConfigPremium>
>;

// Visitor para operaciones sobre el variant
class SistemaVisitor {
public:
    void operator()(GestorAplicacion<ConfigDefault>& sistema) {
        std::cout << "Sistema Default seleccionado" << std::endl;
        sistema.ejecutar();
    }
    
    void operator()(GestorAplicacion<ConfigPremium>& sistema) {
        std::cout << "Sistema Premium seleccionado" << std::endl;
        sistema.ejecutar();
    }
};

// Función principal template
template<typename Config = ConfigDefault>
int ejecutarAplicacion() {
    try {
        auto config = crearSistemaConfigurado<Config>();
        GestorAplicacion<Config> app(std::move(config));
        
        // Demostrar características antes de ejecutar
        demostrarCaracteristicas(app);
        
        std::cout << "\nPresione Enter para continuar..." << std::endl;
        std::cin.ignore();
        std::cin.get();
        
        app.ejecutar();
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << " Error crítico: " << e.what() << std::endl;
        return 1;
    }
}

// Función para seleccionar tipo de sistema
auto seleccionarSistema() -> SistemaVariant {
    std::cout << "Seleccione el tipo de sistema:" << std::endl;
    std::cout << "1. Sistema Default (Sin impuestos)" << std::endl;
    std::cout << "2. Sistema Premium (Con impuestos 15%)" << std::endl;
    std::cout << "Opción: ";
    
    int opcion;
    std::cin >> opcion;
    
    switch (opcion) {
        case 1:
            return GestorAplicacion<ConfigDefault>(crearSistemaConfigurado<ConfigDefault>());
        case 2:
            return GestorAplicacion<ConfigPremium>(crearSistemaConfigurado<ConfigPremium>());
        default:
            std::cout << "Opción inválida, usando sistema default." << std::endl;
            return GestorAplicacion<ConfigDefault>(crearSistemaConfigurado<ConfigDefault>());
    }
}

// Punto de entrada principal
int main() {
    std::cout << "  SISTEMA DE GESTIÓN DE BOLETOS - TEMPLATE++ " << std::endl;
    
    // Opción 1: Ejecutar sistema específico
    // return ejecutarAplicacion<ConfigDefault>();
    
    // Opción 2: Seleccionar sistema interactivamente
    try {
        auto sistema = seleccionarSistema();
        std::visit(SistemaVisitor{}, sistema);
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}

// Función de demostración adicional (opcional)
void demostracionAvanzada() {
    std::cout << "\n=== DEMOSTRACIÓN AVANZADA ===" << std::endl;
    
    // Demo de templates con diferentes políticas
    auto demoPoliticas = []() {
        std::cout << "Creando sistema con diferentes políticas..." << std::endl;
        
        // Sistema con precio base
        SistemaBoletos<> sistemaBase;
        
        // Sistema con impuestos
        SistemaBoletos<Cliente<Boleto<PrecioConImpuestoPolicy>>> sistemaConImpuestos;
        
        std::cout << "✓ Sistemas creados con diferentes políticas de precio" << std::endl;
    };
    
    // Demo de funciones lambda complejas
    auto demoLambdas = []() {
        std::cout << "Demostrando funciones lambda avanzadas..." << std::endl;
        
        // Lambda recursiva para factorial
        auto factorial = [](auto self, int n) -> int {
            return n <= 1 ? 1 : n * self(self, n - 1);
        };
        
        std::cout << "Factorial de 5: " << factorial(factorial, 5) << std::endl;
        
        // Lambda con capture complejo
        auto contador = [count = 0]() mutable {
            return ++count;
        };
        
        std::cout << "Contador lambda: " << contador() << ", " << contador() << std::endl;
    };
    
    demoPoliticas();
    demoLambdas();
}