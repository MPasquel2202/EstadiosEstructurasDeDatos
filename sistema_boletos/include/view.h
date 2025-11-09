#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <string>
#include "model.h"

class Vista {
public:
    static void mostrarMenu() {
        std::cout << "\n=== SISTEMA DE COMPRA DE BOLETOS ===" << std::endl;
        std::cout << "1. Reservar boleto" << std::endl;
        std::cout << "2. Imprimir boleto" << std::endl;
        std::cout << "3. Asientos disponibles" << std::endl;
        std::cout << "4. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
    }

    static void solicitarDatosReserva(std::string& cedula, std::string& nombre, 
                                     std::string& fechaNacimiento, std::string& tipoBoleto, 
                                     int& cantidad) {
        std::cout << "\n--- RESERVA DE BOLETO ---" << std::endl;
        std::cout << "Cédula: ";
        std::cin >> cedula;
        std::cin.ignore();
        
        std::cout << "Nombre completo: ";
        std::getline(std::cin, nombre);
        
        std::cout << "Fecha de nacimiento (dd/mm/aaaa): ";
        std::cin >> fechaNacimiento;
        
        std::cout << "\nTipos de boletos disponibles:" << std::endl;
        std::cout << "1. General - $50" << std::endl;
        std::cout << "2. Palco - $100" << std::endl;
        std::cout << "3. Tribuna - $75" << std::endl;
        
        std::string tipoOpcion;
        std::cout << "Seleccione tipo de boleto (1-3): ";
        std::cin >> tipoOpcion;
        
        if (tipoOpcion == "1") tipoBoleto = "general";
        else if (tipoOpcion == "2") tipoBoleto = "palco";
        else if (tipoOpcion == "3") tipoBoleto = "tribuna";
        else tipoBoleto = "general";
        
        std::cout << "Cantidad de boletos: ";
        std::cin >> cantidad;
    }

    static void mostrarResultadoReserva(bool exito, const std::string& mensaje) {
        if (exito) {
            std::cout << "✓ " << mensaje << std::endl;
        } else {
            std::cout << "✗ " << mensaje << std::endl;
        }
    }

    static std::string solicitarCedulaImpresion() {
        std::string cedula;
        std::cout << "\nIngrese cédula para imprimir boletos: ";
        std::cin >> cedula;
        return cedula;
    }

    static void mostrarBoletos(Cliente* cliente) {
        if (!cliente) return;
        
        std::cout << "\n--- BOLETOS DE " << cliente->getNombre() << " ---" << std::endl;
        std::cout << "Cédula: " << cliente->getCedula() << std::endl;
        std::cout << "Fecha de nacimiento: " << cliente->getFechaNacimiento() << std::endl;
        std::cout << "\nBoletos comprados:" << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
        
        int i = 1;
        for (const Boleto& boleto : cliente->getBoletos()) {
            std::cout << "Boleto " << i++ << ":" << std::endl;
            std::cout << "  Tipo: " << boleto.getTipo() << std::endl;
            std::cout << "  Asiento: " << boleto.getAsiento() << std::endl;
            std::cout << "  Precio: $" << boleto.getPrecio() << std::endl;
            std::cout << "  N° Serie: " << boleto.getNumeroSerie() << std::endl;
            std::cout << "  Fecha: " << boleto.getFechaCompra() << std::endl;
            std::cout << "------------------------------------------------------------" << std::endl;
        }
    }

    static void mostrarAsientosDisponibles(int general, int palco, int tribuna,
                                          const std::vector<std::string>& asientosG,
                                          const std::vector<std::string>& asientosP,
                                          const std::vector<std::string>& asientosT) {
        std::cout << "\n--- ASIENTOS DISPONIBLES ---" << std::endl;
        
        std::cout << "GENERAL: " << general << " asientos disponibles" << std::endl;
        if (!asientosG.empty()) {
            std::cout << "  Asientos: ";
            for (const auto& asiento : asientosG) {
                std::cout << asiento << " ";
            }
            std::cout << std::endl;
        }
        
        std::cout << "PALCO: " << palco << " asientos disponibles" << std::endl;
        if (!asientosP.empty()) {
            std::cout << "  Asientos: ";
            for (const auto& asiento : asientosP) {
                std::cout << asiento << " ";
            }
            std::cout << std::endl;
        }
        
        std::cout << "TRIBUNA: " << tribuna << " asientos disponibles" << std::endl;
        if (!asientosT.empty()) {
            std::cout << "  Asientos: ";
            for (const auto& asiento : asientosT) {
                std::cout << asiento << " ";
            }
            std::cout << std::endl;
        }
    }

    static void mostrarError(const std::string& mensaje) {
        std::cout << "Error: " << mensaje << std::endl;
    }

    static void mostrarMensaje(const std::string& mensaje) {
        std::cout << mensaje << std::endl;
    }
};

#endif
