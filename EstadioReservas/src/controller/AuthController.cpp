#include "controller/AuthController.hpp"
#include "utils/CedulaEC.hpp"
#include "utils/InputUtils.hpp"
#include "utils/MongoStore.hpp"
#include "view/MenuView.hpp"
#include "utils/Exceptions.hpp"
#include <iostream>
#include <utility>

// Quicksort y búsqueda binaria basados en punteros (uso de utilitario común)
#include "utils/QuickSortPtr.hpp"

namespace AuthController{
    Usuario* login(LinkedList<Usuario>& usuarios){
        MenuView::bienvenida();
        MenuView::recordarNombreCaseSensitive();

        std::cout << "Ingrese cedula: ";
        std::string ced = InputUtils::leerLineaNoVacia(10);
        if(!CedulaEC::validar(ced)) throw CedulaInvalida("Cedula no valida.");

        // Construir arreglo dinámico de punteros a usuarios que cumplan la condición (cédula válida)
        size_t cap = usuarios.size();
        Usuario** arr = nullptr;
        Usuario* u = nullptr;
        if(cap > 0){
            arr = new Usuario*[cap];
            size_t filled = 0;
            usuarios.for_each([&](Usuario& uu){ if(CedulaEC::validar(uu.cedula)) arr[filled++] = &uu; });

            if(filled > 0){
                // Búsqueda binaria #1: login por cédula (ordenamos punteros y buscamos)
                // Ordenar por cédula usando quicksort basado en punteros (utilitario compartido)
                QuickSortPtr::quickSort<Usuario*>(arr, arr + (ptrdiff_t)filled - 1, [](const Usuario* a, const Usuario* b){ return a->cedula < b->cedula; });

                // Búsqueda binaria por cédula usando aritmética de punteros
                Usuario** lo = arr;
                Usuario** hi = arr + (ptrdiff_t)filled - 1;
                while(lo <= hi){
                    Usuario** mid = lo + (hi - lo) / 2;
                    if((*mid)->cedula == ced){ u = *mid; break; }
                    if((*mid)->cedula < ced) lo = mid + 1; else hi = mid - 1;
                }
            }
            delete [] arr; // liberar arreglo dinámico
        }

        if(u){
            std::cout << "Ingrese nombre (sensible a mayusculas): ";
            std::string nom = InputUtils::leerLineaNoVacia(2);
            if(nom != u->nombre){
                std::cout << "Nombre no coincide.\n";
                return nullptr;
            }
            std::cout << "Bienvenido/a, " << u->nombre << "\n";
            return u;
        }else{
            std::cout << "No existe usuario. Registro nuevo. Ingrese nombre: ";
            std::string nom = InputUtils::leerLineaNoVacia(2);
            if(!InputUtils::nombreValido(nom)) throw EntradaInvalida("Nombre invalido");

            Usuario nu;
            nu.cedula = ced;
            nu.nombre = nom;

            usuarios.push_back(std::move(nu)); 

            MongoStore::saveUsuarios(usuarios);

            std::cout << "Usuario registrado. Bienvenido/a, " << nom << "\n";
            // Devolver puntero al usuario recién insertado (buscamos con el mismo método por simplicidad)
            Usuario* res = usuarios.find([&](const Usuario& uu){ return uu.cedula == ced; });
            return res;
        }
    }
}
