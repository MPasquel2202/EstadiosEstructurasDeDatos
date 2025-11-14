#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <iomanip>
#include <algorithm>
#include "model.h"

// Template para políticas de formato
template<typename T>
class FormatoPolicy {
public:
    static std::string formatear(const T& valor) { 
        return std::to_string(valor); 
    }
};

template<>
class FormatoPolicy<std::string> {
public:
    static std::string formatear(const std::string& valor) {
        return valor;
    }
};

template<>
class FormatoPolicy<double> {
public:
    static std::string formatear(double valor) {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << valor;
        return ss.str();
    }
};

// Template base para vistas
template<typename FormatoPolicy = FormatoPolicy<std::string>>
class VistaBase {
protected:
    FormatoPolicy formateador;

public:
    // Template method para mostrar mensajes con diferentes estilos
    template<typename MensajeType>
    void mostrarMensaje(const MensajeType& mensaje, 
                       const std::string& estilo = "normal") const {
        auto aplicarEstilo = [&estilo](const std::string& texto) -> std::string {
            if (estilo == "error") return "✗ " + texto;
            if (estilo == "exito") return "✓ " + texto;
            if (estilo == "advertencia") return "⚠ " + texto;
            if (estilo == "titulo") return "\n=== " + texto + " ===";
            if (estilo == "subtitulo") return "\n--- " + texto + " ---";
            return texto;
        };
        
        std::cout << aplicarEstilo(formateador.formatear(mensaje)) << std::endl;
    }

    // Función lambda para limpiar pantalla (multi-plataforma)
    auto limpiarPantalla = []() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    };

    // Template method para mostrar tablas
    template<typename Container, typename HeaderFunc, typename RowFunc>
    void mostrarTabla(const Container& datos, 
                     const std::vector<std::string>& headers,
                     HeaderFunc&& headerFormatter,
                     RowFunc&& rowFormatter,
                     const std::string& titulo = "") const {
        
        if (!titulo.empty()) {
            mostrarMensaje(titulo, "titulo");
        }

        // Mostrar headers
        std::cout << std::endl;
        for (const auto& header : headers) {
            std::cout << std::setw(15) << std::left << header;
        }
        std::cout << std::endl;
        
        // Línea separadora
        std::cout << std::string(headers.size() * 15, '-') << std::endl;
        
        // Mostrar datos
        for (const auto& dato : datos) {
            rowFormatter(dato);
        }
    }
};

// Template Vista principal
template<typename ClienteType = Cliente<Boleto<PrecioBasePolicy>>,
         typename FormatoPolicy = FormatoPolicy<std::string>>
class Vista : public VistaBase<FormatoPolicy> {
private:
    using Base = VistaBase<FormatoPolicy>;

public:
    // Métodos sobrecargados para mostrar menú
    void mostrarMenu() const {
        mostrarMenu([](const std::string& opcion, const std::string& descripcion) {
            std::cout << opcion << ". " << descripcion << std::endl;
        });
    }

    template<typename MenuFormatter>
    void mostrarMenu(MenuFormatter&& formatter) const {
        Base::limpiarPantalla();
        Base::mostrarMensaje("SISTEMA DE COMPRA DE BOLETOS", "titulo");
        
        auto opciones = {
            std::make_pair("1", "Reservar boleto"),
            std::make_pair("2", "Imprimir boleto"),
            std::make_pair("3", "Asientos disponibles"),
            std::make_pair("4", "Salir")
        };
        
        for (const auto& [opcion, descripcion] : opciones) {
            formatter(opcion, descripcion);
        }
        
        std::cout << "Seleccione una opción: ";
    }

    // Métodos sobrecargados para solicitar datos de reserva
    void solicitarDatosReserva(std::string& cedula, std::string& nombre, 
                              std::string& fechaNacimiento, std::string& tipoBoleto, 
                              int& cantidad) const {
        solicitarDatosReserva(cedula, nombre, fechaNacimiento, tipoBoleto, cantidad,
                            [](const auto&... args) {
                                // Lambda por defecto para entrada estándar
                                (std::cout << ... << args) << std::endl;
                            });
    }

    template<typename InputPrompter>
    void solicitarDatosReserva(std::string& cedula, std::string& nombre, 
                              std::string& fechaNacimiento, std::string& tipoBoleto, 
                              int& cantidad, InputPrompter&& prompter) const {
        
        Base::mostrarMensaje("RESERVA DE BOLETO", "subtitulo");
        
        auto solicitarEntrada = [&prompter](const std::string& mensaje, auto& variable) {
            prompter(mensaje);
            if constexpr (std::is_same_v<std::decay_t<decltype(variable)>, std::string>) {
                std::getline(std::cin >> std::ws, variable);
            } else {
                std::cin >> variable;
            }
        };

        solicitarEntrada("Cédula: ", cedula);
        solicitarEntrada("Nombre completo: ", nombre);
        solicitarEntrada("Fecha de nacimiento (dd/mm/aaaa): ", fechaNacimiento);
        
        // Mostrar tipos de boletos con template method
        mostrarTiposBoletos();
        
        std::string tipoOpcion;
        solicitarEntrada("Seleccione tipo de boleto (1-3): ", tipoOpcion);
        
        // Lambda para mapear opción a tipo
        auto mapearTipo = [](const std::string& opcion) -> std::string {
            if (opcion == "1") return "general";
            if (opcion == "2") return "palco";
            if (opcion == "3") return "tribuna";
            return "general"; // default
        };
        
        tipoBoleto = mapearTipo(tipoOpcion);
        solicitarEntrada("Cantidad de boletos: ", cantidad);
    }

    // Template method para mostrar tipos de boletos
    template<typename PrecioProvider = std::function<double(const std::string&)>>
    void mostrarTiposBoletos(PrecioProvider&& precioProvider = nullptr) const {
        auto tipos = {
            std::make_tuple("1", "General", 50.0),
            std::make_tuple("2", "Palco", 100.0),
            std::make_tuple("3", "Tribuna", 75.0)
        };
        
        Base::mostrarMensaje("Tipos de boletos disponibles:", "normal");
        
        for (const auto& [opcion, nombre, precioBase] : tipos) {
            double precioFinal = precioProvider ? precioProvider(nombre) : precioBase;
            std::cout << opcion << ". " << nombre << " - $" 
                     << Base::formateador.formatear(precioFinal) << std::endl;
        }
    }

    // Métodos sobrecargados para mostrar resultados
    void mostrarResultadoReserva(bool exito, const std::string& mensaje) const {
        mostrarResultadoReserva(exito, mensaje, [this](bool exito, const std::string& msg) {
            Base::mostrarMensaje(msg, exito ? "exito" : "error");
        });
    }

    template<typename ResultFormatter>
    void mostrarResultadoReserva(bool exito, const std::string& mensaje, 
                                ResultFormatter&& formatter) const {
        formatter(exito, mensaje);
    }

    // Métodos sobrecargados para solicitar cédula
    std::string solicitarCedulaImpresion() const {
        return solicitarCedulaImpresion([](const std::string& mensaje) {
            std::cout << mensaje;
            std::string cedula;
            std::cin >> cedula;
            return cedula;
        });
    }

    template<typename InputFunc>
    std::string solicitarCedulaImpresion(InputFunc&& inputFunc) const {
        return inputFunc("\nIngrese cédula para imprimir boletos: ");
    }

    // Métodos sobrecargados para mostrar boletos
    void mostrarBoletos(ClienteType* cliente) const {
        mostrarBoletos(cliente, [this](const ClienteType& cli) {
            return this->formatearBoletosCliente(cli);
        });
    }

    template<typename BoletosFormatter>
    void mostrarBoletos(ClienteType* cliente, BoletosFormatter&& formatter) const {
        if (!cliente) return;
        
        Base::mostrarMensaje("BOLETOS DE " + cliente->getNombre(), "subtitulo");
        std::cout << "Cédula: " << cliente->getCedula() << std::endl;
        std::cout << "Fecha de nacimiento: " << cliente->getFechaNacimiento() << std::endl;
        
        formatter(*cliente);
    }

private:
    // Función lambda para formatear boletos de cliente
    auto formatearBoletosCliente = [this](const ClienteType& cliente) {
        const auto& boletos = cliente.getBoletos();
        
        if (boletos.empty()) {
            Base::mostrarMensaje("No hay boletos comprados", "advertencia");
            return;
        }

        // Usar template method para mostrar tabla de boletos
        std::vector<std::string> headers = {"N°", "Tipo", "Asiento", "Precio", "N° Serie", "Fecha"};
        
        auto rowFormatter = [](const auto& boletoWrapper) {
            // Lambda para extraer y formatear datos del boleto
            const auto& boleto = boletoWrapper;
            std::cout << std::setw(15) << std::left << "Boleto"
                     << std::setw(15) << boleto.getTipo()
                     << std::setw(15) << boleto.getAsiento()
                     << std::setw(15) << ("$" + Base::formateador.formatear(boleto.getPrecio()))
                     << std::setw(15) << boleto.getNumeroSerie()
                     << std::setw(15) << boleto.getFechaCompra()
                     << std::endl;
        };

        // Mostrar como tabla
        Base::template mostrarTabla(boletos, headers, 
                                   [](const std::vector<std::string>& h) {
                                       for (const auto& header : h) {
                                           std::cout << std::setw(15) << std::left << header;
                                       }
                                       std::cout << std::endl;
                                       std::cout << std::string(h.size() * 15, '-') << std::endl;
                                   },
                                   rowFormatter,
                                   "BOLETOS COMPRADOS");
    };

public:
    // Métodos sobrecargados para mostrar asientos disponibles
    void mostrarAsientosDisponibles(int general, int palco, int tribuna,
                                   const std::vector<std::string>& asientosG,
                                   const std::vector<std::string>& asientosP,
                                   const std::vector<std::string>& asientosT) const {
        
        mostrarAsientosDisponibles(general, palco, tribuna, asientosG, asientosP, asientosT,
                                 [this](int g, int p, int t, 
                                        const auto& ag, const auto& ap, const auto& at) {
                                    this->mostrarAsientosDetallados(g, p, t, ag, ap, at);
                                });
    }

    template<typename AsientosFormatter>
    void mostrarAsientosDisponibles(int general, int palco, int tribuna,
                                   const std::vector<std::string>& asientosG,
                                   const std::vector<std::string>& asientosP,
                                   const std::vector<std::string>& asientosT,
                                   AsientosFormatter&& formatter) const {
        
        Base::mostrarMensaje("ASIENTOS DISPONIBLES", "subtitulo");
        formatter(general, palco, tribuna, asientosG, asientosP, asientosT);
    }

private:
    // Lambda para mostrar asientos detallados
    auto mostrarAsientosDetallados = [this](int general, int palco, int tribuna,
                                           const std::vector<std::string>& asientosG,
                                           const std::vector<std::string>& asientosP,
                                           const std::vector<std::string>& asientosT) {
        
        auto mostrarSeccion = [this](const std::string& nombre, int disponibles, 
                                    const std::vector<std::string>& asientos) {
            std::cout << "\n" << nombre << ": " << disponibles << " asientos disponibles" << std::endl;
            if (!asientos.empty()) {
                std::cout << "  Asientos: ";
                std::for_each(asientos.begin(), asientos.end(), [](const auto& asiento) {
                    std::cout << asiento << " ";
                });
                std::cout << std::endl;
            }
        };

        mostrarSeccion("GENERAL", general, asientosG);
        mostrarSeccion("PALCO", palco, asientosP);
        mostrarSeccion("TRIBUNA", tribuna, asientosT);
    };

public:
    // Métodos sobrecargados para mostrar errores y mensajes
    void mostrarError(const std::string& mensaje) const {
        mostrarError(mensaje, [this](const std::string& msg) {
            Base::mostrarMensaje(msg, "error");
        });
    }

    template<typename ErrorFormatter>
    void mostrarError(const std::string& mensaje, ErrorFormatter&& formatter) const {
        formatter(mensaje);
    }

    void mostrarMensaje(const std::string& mensaje) const {
        mostrarMensaje(mensaje, [this](const std::string& msg) {
            Base::mostrarMensaje(msg, "normal");
        });
    }

    template<typename MessageFormatter>
    void mostrarMensaje(const std::string& mensaje, MessageFormatter&& formatter) const {
        formatter(mensaje);
    }

    // Template method para mostrar estadísticas
    template<typename StatsProvider>
    void mostrarEstadisticas(StatsProvider&& statsProvider) const {
        auto stats = statsProvider();
        Base::mostrarMensaje("ESTADÍSTICAS DEL SISTEMA", "titulo");
        std::cout << stats << std::endl;
    }
};

// Alias para compatibilidad con código existente
using Vista = Vista<>;

#endif