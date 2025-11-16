#include "controller/AuthController.hpp"
#include "utils/CedulaEC.hpp"
#include "utils/InputUtils.hpp"
#include "utils/JsonStore.hpp"
#include "view/MenuView.hpp"
#include "utils/Exceptions.hpp"
#include <iostream>
#include <utility>

namespace AuthController{
    Usuario* login(LinkedList<Usuario>& usuarios){
        MenuView::bienvenida();
        MenuView::recordarNombreCaseSensitive();

        std::cout << "Ingrese cedula: ";
        std::string ced = InputUtils::leerLineaNoVacia(10);
        if(!CedulaEC::validar(ced)) throw CedulaInvalida("Cedula no valida.");

        Usuario* u = usuarios.find([&](const Usuario& uu){ return uu.cedula == ced; });
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

            JsonStore::saveUsuarios(usuarios, "data/usuarios.json");

            std::cout << "Usuario registrado. Bienvenido/a, " << nom << "\n";
            return usuarios.find([&](const Usuario& uu){ return uu.cedula == ced; });
        }
    }
}
