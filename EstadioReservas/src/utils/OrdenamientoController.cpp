#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <fstream>
#include <sstream>
#include "utils/InputUtils.hpp"
#include "utils/OrdenamientoController.hpp"
#include "utils/JsonStore.hpp"
#include "view/Printer.hpp"
#include "model/Reserva.hpp"
#include "model/Fecha.hpp"
#include "model/Usuario.hpp"

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
        std::cout << "[4] Ordenar Letras de Nombres de Usuarios" << std::endl;
        std::cout << "[0] Volver al menú principal" << std::endl;
        std::cout << "Seleccione criterio: ";
        
        int opcCriterio = InputUtils::leerEnteroEnRango(0, 4);
        if(opcCriterio == 0) break;
        
        if(opcCriterio == 4) {
            // Caso especial para ordenar letras de nombres
            ordenarLetrasNombresUsuarios();
            continue;
        }
        
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

void OrdenamientoController::ordenarLetrasNombresUsuarios() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "ORDENAR LETRAS DE NOMBRES DE USUARIOS" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    try {
        // ✅ CAMBIO IMPORTANTE: Recargar usuarios CADA VEZ que se ejecuta
        LinkedList<Usuario> usuarios;
        JsonStore::loadUsuarios(usuarios, "data/usuarios.json");
        
        if (usuarios.size() == 0) {
            std::cout << "No hay usuarios registrados.\n";
            return;
        }
        
        // Extraer nombres de usuarios
        std::vector<std::string> nombresUsuarios;
        usuarios.for_each([&](Usuario& usuario) {
            nombresUsuarios.push_back(usuario.nombre);
        });
        
        // FUNCIÓN LAMBDA para ordenar nombres alfabéticamente
        auto comparadorNombres = [](const std::string& a, const std::string& b) {
            std::string aMin = a;
            std::string bMin = b;
            std::transform(aMin.begin(), aMin.end(), aMin.begin(), ::tolower);
            std::transform(bMin.begin(), bMin.end(), bMin.begin(), ::tolower);
            return aMin < bMin;
        };
        
        // Ordenar los nombres alfabéticamente usando la lambda
        std::sort(nombresUsuarios.begin(), nombresUsuarios.end(), comparadorNombres);
        
        std::cout << "\nNombres originales de usuarios (ordenados alfabéticamente):\n";
        std::cout << std::string(50, '-') << std::endl;
        
        // Mostrar nombres originales y procesar cada nombre
        for (const auto& nombreOriginal : nombresUsuarios) {
            if (nombreOriginal.empty()) {
                std::cout << "• (Nombre vacío)" << std::endl;
            } else {
                std::cout << "• " << nombreOriginal << std::endl;
                
                // Ordenar las letras del nombre alfabéticamente en grupos de 3
                std::string nombreOrdenado = ordenarLetrasNombre(nombreOriginal);
                
                // Mostrar resultado
                std::cout << "  Letras ordenadas: " << nombreOrdenado << std::endl;
            }
            std::cout << std::endl;
        }
        
        std::cout << "Total de usuarios encontrados: " << nombresUsuarios.size() << std::endl;
        
    } catch(const std::exception& e) {
        std::cout << "Error al cargar usuarios: " << e.what() << std::endl;
        
        // Mostrar datos de ejemplo en caso de error
        std::cout << "\n--- MOSTRANDO DATOS DE EJEMPLO ---" << std::endl;
        std::vector<std::string> nombresEjemplo = {
            "JuanPerez",
            "Marlon Pasquel",
            "Brandon Pazmino", 
            "Roberto",
            "k l"
        };
        
        for (const auto& nombre : nombresEjemplo) {
            std::cout << "• " << nombre << std::endl;
            std::string nombreOrdenado = ordenarLetrasNombre(nombre);
            std::cout << "  Letras ordenadas: " << nombreOrdenado << std::endl << std::endl;
        }
    }
}

std::string OrdenamientoController::ordenarLetrasNombre(const std::string& nombre) {
    if (nombre.empty()) {
        return "(vacío)";
    }
    
    std::string nombreLimpio = nombre;
    
    // Convertir a minúsculas para ordenación case-insensitive
    std::transform(nombreLimpio.begin(), nombreLimpio.end(), nombreLimpio.begin(), ::tolower);
    
    // Separar letras
    std::vector<char> letras;
    for (char c : nombreLimpio) {
        if (std::isalpha(c)) { // Solo incluir letras
            letras.push_back(c);
        }
    }
    
    if (letras.empty()) {
        // Si no hay letras, mostrar los caracteres no alfabéticos ordenados
        std::vector<char> caracteres;
        for (char c : nombreLimpio) {
            if (!std::isspace(c)) { // Excluir espacios
                caracteres.push_back(c);
            }
        }
        
        if (caracteres.empty()) {
            return "(solo espacios)";
        }
        
        std::sort(caracteres.begin(), caracteres.end());
        std::string resultado;
        for (char c : caracteres) {
            resultado += c;
            resultado += ' ';
        }
        if (!resultado.empty()) resultado.pop_back();
        return resultado;
    }
    
    // Ordenar las letras alfabéticamente
    std::sort(letras.begin(), letras.end());
    
    // FUNCIÓN LAMBDA para agrupar en tripletes
    auto agruparEnTripletes = [](const std::vector<char>& letras) -> std::string {
        std::string resultado;
        for (size_t i = 0; i < letras.size(); ++i) {
            resultado += letras[i];
            
            // Agrupar en tripletes separados por espacios
            if ((i + 1) % 3 == 0 && i != letras.size() - 1) {
                resultado += "    ";
            } else if (i != letras.size() - 1) {
                resultado += ' ';
            }
        }
        return resultado;
    };
    
    // Reconstruir el string ordenado en grupos de 3
    std::string resultado = agruparEnTripletes(letras);
    
    return resultado;
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
        case 4: return "Letras de Nombres de Usuarios";
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
