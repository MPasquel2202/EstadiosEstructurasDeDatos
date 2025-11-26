#include <iostream>
#include "utils/InputUtils.hpp"
#include "utils/OrdenamientoController.hpp"
#include "view/Printer.hpp"
#include <algorithm>
#include <vector>
#include "model/Reserva.hpp"
#include "model/Fecha.hpp"

void OrdenamientoController::mostrarMenuOrdenamiento(LinkedList<Evento>& eventos, 
                                                   LinkedList<InventarioEvento>& inventarios) {
    OrdenadorEventos<Evento> ordenador;
    
    // Convertir LinkedList a vector para el ordenador
    std::vector<Evento*> eventosVec;
    eventos.for_each([&](Evento& e) {
        eventosVec.push_back(&e);
    });
    
    // Crear mapa de inventarios para acceso rápido
    std::unordered_map<std::string, InventarioEvento*> inventariosMap;
    inventarios.for_each([&](InventarioEvento& inv) {
        inventariosMap[inv.eventoId] = &inv;
    });
    
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

void OrdenamientoController::mostrarMenuOrdenamientoReservas(Usuario& usuario,
                                                            const LinkedList<Evento>& eventos) {
    if (usuario.reservas.size() == 0) {
        std::cout << "\nNo tienes reservas registradas.\n";
        return;
    }

    while(true) {
        std::cout << "\n=== MENÚ DE ORDENAMIENTO DE MIS RESERVAS ===" << std::endl;
        std::cout << "Criterios de ordenamiento:" << std::endl;
        std::cout << "[1] Por Fecha" << std::endl;
        std::cout << "[2] Por Nombre de Evento" << std::endl;
        std::cout << "[3] Por Total de Boletos" << std::endl;
        std::cout << "[0] Volver al menú principal" << std::endl;
        std::cout << "Seleccione criterio: ";
        
        int opcCriterio = InputUtils::leerEnteroEnRango(0, 3);
        if(opcCriterio == 0) break;
        
        std::cout << "\n=== ALGORITMOS DE ORDENAMIENTO ===" << std::endl;
        std::cout << "[1] Selección     [2] Inserción" << std::endl;
        std::cout << "[3] Burbuja       [4] Shell" << std::endl;
        std::cout << "[5] Heapsort      [6] Mergesort" << std::endl;
        std::cout << "[7] Quicksort     [0] Volver" << std::endl;
        std::cout << "Seleccione algoritmo: ";
        
        int opcAlgoritmo = InputUtils::leerEnteroEnRango(0, 7);
        if(opcAlgoritmo == 0) continue;
        
        // Convertir reservas a vector
        std::vector<Reserva*> reservasVec;
        usuario.reservas.for_each([&](Reserva& r) {
            reservasVec.push_back(&r);
        });
        
        // Aplicar ordenamiento según el criterio y algoritmo
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "RESULTADO - " << obtenerNombreCriterio(opcCriterio) 
                  << " (" << obtenerNombreAlgoritmo(opcAlgoritmo) << ")" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        
        switch(opcCriterio) {
            case 1: { // Por Fecha
                auto comparador = [&](Reserva* a, Reserva* b) {
                    const Evento* ea = eventos.find([&](const Evento& e) { return e.id == a->eventoId; });
                    const Evento* eb = eventos.find([&](const Evento& e) { return e.id == b->eventoId; });
                    Fecha fa = ea ? ea->fecha : Fecha();
                    Fecha fb = eb ? eb->fecha : Fecha();
                    return fa < fb;
                };
                
                switch(opcAlgoritmo) {
                    case 1: std::sort(reservasVec.begin(), reservasVec.end(), comparador); break;
                    case 2: std::stable_sort(reservasVec.begin(), reservasVec.end(), comparador); break;
                    case 3: std::stable_sort(reservasVec.begin(), reservasVec.end(), comparador); break;
                    case 4: std::stable_sort(reservasVec.begin(), reservasVec.end(), comparador); break;
                    case 5: std::make_heap(reservasVec.begin(), reservasVec.end(), 
                                          [comparador](Reserva* a, Reserva* b) { return !comparador(a, b); });
                            std::sort_heap(reservasVec.begin(), reservasVec.end(), 
                                          [comparador](Reserva* a, Reserva* b) { return !comparador(a, b); });
                            break;
                    case 6: std::stable_sort(reservasVec.begin(), reservasVec.end(), comparador); break;
                    case 7: std::stable_sort(reservasVec.begin(), reservasVec.end(), comparador); break;
                }
                break;
            }
            case 2: { // Por Nombre de Evento
                auto comparador = [&](Reserva* a, Reserva* b) {
                    const Evento* ea = eventos.find([&](const Evento& e) { return e.id == a->eventoId; });
                    const Evento* eb = eventos.find([&](const Evento& e) { return e.id == b->eventoId; });
                    std::string nomA = ea ? ea->nombre : "";
                    std::string nomB = eb ? eb->nombre : "";
                    return nomA < nomB;
                };
                
                switch(opcAlgoritmo) {
                    case 1: std::sort(reservasVec.begin(), reservasVec.end(), comparador); break;
                    case 2: std::stable_sort(reservasVec.begin(), reservasVec.end(), comparador); break;
                    case 3: std::stable_sort(reservasVec.begin(), reservasVec.end(), comparador); break;
                    case 4: std::stable_sort(reservasVec.begin(), reservasVec.end(), comparador); break;
                    case 5: std::make_heap(reservasVec.begin(), reservasVec.end(), 
                                          [comparador](Reserva* a, Reserva* b) { return !comparador(a, b); });
                            std::sort_heap(reservasVec.begin(), reservasVec.end(), 
                                          [comparador](Reserva* a, Reserva* b) { return !comparador(a, b); });
                            break;
                    case 6: std::stable_sort(reservasVec.begin(), reservasVec.end(), comparador); break;
                    case 7: std::stable_sort(reservasVec.begin(), reservasVec.end(), comparador); break;
                }
                break;
            }
            case 3: { // Por Total de Boletos
                auto comparador = [](Reserva* a, Reserva* b) {
                    return a->total() < b->total();
                };
                
                switch(opcAlgoritmo) {
                    case 1: std::sort(reservasVec.begin(), reservasVec.end(), comparador); break;
                    case 2: std::stable_sort(reservasVec.begin(), reservasVec.end(), comparador); break;
                    case 3: std::stable_sort(reservasVec.begin(), reservasVec.end(), comparador); break;
                    case 4: std::stable_sort(reservasVec.begin(), reservasVec.end(), comparador); break;
                    case 5: std::make_heap(reservasVec.begin(), reservasVec.end(), 
                                          [comparador](Reserva* a, Reserva* b) { return !comparador(a, b); });
                            std::sort_heap(reservasVec.begin(), reservasVec.end(), 
                                          [comparador](Reserva* a, Reserva* b) { return !comparador(a, b); });
                            break;
                    case 6: std::stable_sort(reservasVec.begin(), reservasVec.end(), comparador); break;
                    case 7: std::stable_sort(reservasVec.begin(), reservasVec.end(), comparador); break;
                }
                break;
            }
        }
        
        // Mostrar reservas ordenadas
        Printer::mostrarReservasOrdenadas(usuario, reservasVec, eventos);
        
        std::cout << "\nPresione Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
    }
}