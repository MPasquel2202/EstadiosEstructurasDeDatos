#ifdef _WIN32
#include <windows.h>
#endif
#include <locale.h>
#include <iostream>

#include "ds/LinkedList.hpp"
#include "model/Usuario.hpp"
#include "model/Evento.hpp"
#include "model/InventarioEvento.hpp"
#include "controller/AuthController.hpp"
#include "controller/EventoController.hpp"
#include "controller/ReservaController.hpp"
#include "utils/JsonStore.hpp"
#include "utils/DateUtils.hpp"
#include "utils/Exceptions.hpp"
#include "utils/InputUtils.hpp"
#include "view/MenuView.hpp"
#include "view/Printer.hpp"
#include "utils/OrdenamientoController.hpp"

static void guardarUsuarios(const LinkedList<Usuario>& usuarios){
    JsonStore::saveUsuarios(usuarios, "data/usuarios.json");
}
static void guardarInventarios(const LinkedList<InventarioEvento>& invs){
    JsonStore::saveInventarios(invs, "data/boletos.json");
}

int main(){
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    setlocale(LC_ALL, "");

    LinkedList<Usuario> usuarios;
    LinkedList<Evento> eventos;
    LinkedList<InventarioEvento> inventarios;

    try{
        JsonStore::loadEventos(eventos, "data/eventos.json");
        JsonStore::loadInventarios(inventarios, "data/boletos.json");
        JsonStore::loadUsuarios(usuarios, "data/usuarios.json");
    }catch(const std::exception& e){
        std::cout << "Error cargando JSON: " << e.what() << "\n";
    }

    while(true){
        try{
            Usuario* usr = nullptr;
            while(!usr){
                usr = AuthController::login(usuarios);
                if(!usr){
                    std::cout << "Credenciales incorrectas o canceladas. Intenta de nuevo.\n";
                }
            }

            bool seguir = true;
            while(seguir){
                Printer::listarEventos(eventos, inventarios,
                    [&](const Evento& e){ return EventoController::esReservable(e); });

                std::cout << "\n[1] Reservar  [2] Menu Ordenamiento  [3] Cancelar reserva  [4] Ordenar Nombres  [0] Cerrar sesion \n Opcion: ";
                int opc = InputUtils::leerEnteroEnRango(0,4); // Cambiado a 4

                switch(opc){
                    case 1: {
                        Evento* evt = EventoController::seleccionarEvento(eventos);
                        if(!evt) break;
                        if(!EventoController::esReservable(*evt)){
                            MenuView::noReservableYVolver();
                            break;
                        }
                        if(auto* inv = EventoController::obtenerInventario(inventarios, evt->id)){
                            try{
                                ReservaController::reservar(*usr, *inv, *evt);
                                guardarUsuarios(usuarios);
                                guardarInventarios(inventarios);
                            }catch(const LimiteExcedido& e){ std::cout << e.what() << "\n"; }
                             catch(const CupoInsuficiente& e){ std::cout << e.what() << "\n"; }
                             catch(const EntradaInvalida& e){ std::cout << e.what() << "\n"; }
                             catch(const std::exception& e){ std::cout << "Error: " << e.what() << "\n"; }
                        }else{
                            std::cout << "Error de configuracion: inventario inexistente.\n";
                        }
                        break;
                    }
                    case 2: {
                        // Menú completo de ordenamiento (eventos e inventarios)
                        OrdenamientoController::mostrarMenuOrdenamiento(eventos, inventarios);
                        break;
                    }
                    case 3: {
                        Evento* evt = EventoController::seleccionarEvento(eventos);
                        if(!evt) break;
                        if(!EventoController::esReservable(*evt)){
                            MenuView::noReservableYVolver();
                            break;
                        }
                        if(auto* inv = EventoController::obtenerInventario(inventarios, evt->id)){
                            ReservaController::cancelar(*usr, *inv, *evt);
                            guardarUsuarios(usuarios);
                            guardarInventarios(inventarios);
                        }else{
                            std::cout << "Error de configuracion: inventario inexistente.\n";
                        }
                        break;
                    }
                    case 4: {
                        // Nueva opción directa para ordenar letras de nombres
                        OrdenamientoController::ordenarLetrasNombresUsuarios();
                        break;
                    }
                    case 0:
                    default:
                        seguir = false;
                        break;
                }
            }

        }catch(const CedulaInvalida& e){
            std::cout << e.what() << "\n";
            continue;
        }catch(const EntradaInvalida& e){
            std::cout << e.what() << "\n";
            continue;
        }catch(const std::exception& e){
            std::cout << "Error: " << e.what() << "\n";
            continue;
        }

        std::cout << "\n¿Desea iniciar otra sesion? [1=Si / 0=No]: ";
        int otra = InputUtils::leerEnteroEnRango(0,1);
        if(!otra) break;
    }

    std::cout << "Hasta pronto.\n";
    return 0;
}
