#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "view.h"

class Controlador {
private:
    SistemaBoletos modelo;
    Vista vista;

public:
    void ejecutar() {
        int opcion;
        
        do {
            Vista::mostrarMenu();
            std::cin >> opcion;
            
            switch (opcion) {
                case 1:
                    reservarBoleto();
                    break;
                case 2:
                    imprimirBoleto();
                    break;
                case 3:
                    mostrarAsientosDisponibles();
                    break;
                case 4:
                    Vista::mostrarMensaje("¡Gracias por usar el sistema!");
                    break;
                default:
                    Vista::mostrarError("Opción inválida");
                    break;
            }
        } while (opcion != 4);
    }

private:
    void reservarBoleto() {
        std::string cedula, nombre, fechaNacimiento, tipoBoleto;
        int cantidad;
        
        Vista::solicitarDatosReserva(cedula, nombre, fechaNacimiento, tipoBoleto, cantidad);
        auto resultado = modelo.reservarBoleto(cedula, nombre, fechaNacimiento, tipoBoleto, cantidad);
        Vista::mostrarResultadoReserva(resultado.first, resultado.second);
    }

    void imprimirBoleto() {
        std::string cedula = Vista::solicitarCedulaImpresion();
        auto resultado = modelo.imprimirBoleto(cedula);
        
        if (resultado.first) {
            Vista::mostrarBoletos(resultado.second);
        } else {
            Vista::mostrarError("Cliente no encontrado o no tiene boletos");
        }
    }

    void mostrarAsientosDisponibles() {
        int general, palco, tribuna;
        modelo.obtenerAsientosDisponibles(general, palco, tribuna);
        
        Vista::mostrarAsientosDisponibles(general, palco, tribuna,
                                         modelo.getAsientosGeneral(),
                                         modelo.getAsientosPalco(),
                                         modelo.getAsientosTribuna());
    }
};

#endif
