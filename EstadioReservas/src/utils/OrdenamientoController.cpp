#include "../../include/utils/OrdenamientoController.hpp"
#include "../../include/utils/InputUtils.hpp"
#include "../../include/view/Printer.hpp"
#include <iostream>

void OrdenamientoController::mostrarMenuOrdenamiento(LinkedList<Evento>& eventos, 
                                                   LinkedList<InventarioEvento>& inventarios) {
    OrdenadorEventos<Evento> ordenador;
    
    // Convertir LinkedList a vector para el ordenador
    std::vector<Evento*> eventosVec;
    for (auto& evento : eventos) {
        eventosVec.push_back(&evento);
    }
    
    // Crear mapa de inventarios para acceso rápido
    std::unordered_map<std::string, InventarioEvento*> inventariosMap;
    for (auto& inv : inventarios) {
        inventariosMap[inv.eventoId] = &inv;
    }
    
    ordenador.cargarDatos(eventosVec, inventariosMap);
    
    while(true) {
        std::cout << "\n=== MENÚ DE ORDENAMIENTO ===" << std::endl;
        std::cout << "Criterios de ordenamiento:" << std::endl;
        std::cout << "[1] Por Fecha" << std::endl;
        std::cout << "[2] Por Evento más Cercano" << std::endl;
        std::cout << "[3] Por Asientos Disponibles" << std::endl;
        std::cout << "[0] Volver al menú principal" << std::endl;
        std::cout << "Seleccione criterio: ";
        
        int opcCriterio = InputUtils::leerEnteroEnRango(0, 3);
        if(opcCriterio == 0) break;
        
        std::cout << "\n=== ALGORITMOS DE ORDENAMIENTO ===" << std::endl;
        std::cout << "[1] Selección     [2] Inserción" << std::endl;
        std::cout << "[3] Burbuja       [4] Shell" << std::endl;
        std::cout << "[5] Heapsort      [6] Mergesort" << std::endl;
        std::cout << "[7] Quicksort     [8] Radixsort" << std::endl;
        std::cout << "[9] Binsort       [0] Volver" << std::endl;
        std::cout << "Seleccione algoritmo: ";
        
        int opcAlgoritmo = InputUtils::leerEnteroEnRango(0, 9);
        if(opcAlgoritmo == 0) continue;
        
        bool ascendente = true;
        if(opcCriterio == 3) {
            std::cout << "\nOrden:" << std::endl;
            std::cout << "[1] Ascendente (menos a más asientos)" << std::endl;
            std::cout << "[2] Descendente (más a menos asientos)" << std::endl;
            std::cout << "Seleccione orden: ";
            int orden = InputUtils::leerEnteroEnRango(1, 2);
            ascendente = (orden == 1);
        }
        
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "RESULTADO - " << obtenerNombreCriterio(opcCriterio) 
                  << " (" << obtenerNombreAlgoritmo(opcAlgoritmo) << ")" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        
        aplicarOrdenamiento(ordenador, opcCriterio, opcAlgoritmo, ascendente);
        
        std::cout << "\nPresione Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
    }
}

void OrdenamientoController::aplicarOrdenamiento(OrdenadorEventos<Evento>& ordenador,
                                               int criterio, int algoritmo, bool ascendente) {
    try {
        switch(criterio) {
            case 1: // Fecha
                switch(algoritmo) {
                    case 1: ordenador.seleccion(Comparadores::porFecha); break;
                    case 2: ordenador.insercion(Comparadores::porFecha); break;
                    case 3: ordenador.burbuja(Comparadores::porFecha); break;
                    case 4: ordenador.shell(Comparadores::porFecha); break;
                    case 5: ordenador.heapsort(Comparadores::porFecha); break;
                    case 6: ordenador.mergesort(Comparadores::porFecha); break;
                    case 7: ordenador.quicksort(Comparadores::porFecha); break;
                    case 8: ordenador.radixsort(ascendente); break;
                    case 9: ordenador.binsort(ascendente); break;
                }
                break;
                
            case 2: // Evento más cercano
                switch(algoritmo) {
                    case 1: ordenador.seleccion(Comparadores::porEventoCercano); break;
                    case 2: ordenador.insercion(Comparadores::porEventoCercano); break;
                    case 3: ordenador.burbuja(Comparadores::porEventoCercano); break;
                    case 4: ordenador.shell(Comparadores::porEventoCercano); break;
                    case 5: ordenador.heapsort(Comparadores::porEventoCercano); break;
                    case 6: ordenador.mergesort(Comparadores::porEventoCercano); break;
                    case 7: ordenador.quicksort(Comparadores::porEventoCercano); break;
                    case 8: ordenador.radixsort(ascendente); break;
                    case 9: ordenador.binsort(ascendente); break;
                }
                break;
                
            case 3: // Asientos disponibles
                switch(algoritmo) {
                    case 1: ordenador.seleccion(Comparadores::porAsientosAsc); break;
                    case 2: ordenador.insercion(Comparadores::porAsientosAsc); break;
                    case 3: ordenador.burbuja(Comparadores::porAsientosAsc); break;
                    case 4: ordenador.shell(Comparadores::porAsientosAsc); break;
                    case 5: ordenador.heapsort(Comparadores::porAsientosAsc); break;
                    case 6: ordenador.mergesort(Comparadores::porAsientosAsc); break;
                    case 7: ordenador.quicksort(Comparadores::porAsientosAsc); break;
                    case 8: ordenador.radixsort(ascendente); break;
                    case 9: ordenador.binsort(ascendente); break;
                }
                break;
        }
        
        ordenador.mostrarEventosConInventarios();
        
    } catch(const std::exception& e) {
        std::cout << "Error durante el ordenamiento: " << e.what() << std::endl;
    }
}

std::string OrdenamientoController::obtenerNombreAlgoritmo(int algoritmo) {
    switch(algoritmo) {
        case 1: return "Selección";
        case 2: return "Inserción";
        case 3: return "Burbuja";
        case 4: return "Shell";
        case 5: return "Heapsort";
        case 6: return "Mergesort";
        case 7: return "Quicksort";
        case 8: return "Radixsort";
        case 9: return "Binsort";
        default: return "Desconocido";
    }
}

std::string OrdenamientoController::obtenerNombreCriterio(int criterio) {
    switch(criterio) {
        case 1: return "Fecha";
        case 2: return "Evento más Cercano";
        case 3: return "Asientos Disponibles";
        default: return "Desconocido";
    }
}