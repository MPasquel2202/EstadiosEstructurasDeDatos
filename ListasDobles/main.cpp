#include <iostream>
#include <limits>
#include <string>
#include "Persona.h"
#include "ListaDoble.h"

// Sobrecarga del operador << para imprimir objetos Persona
std::ostream& operator<<(std::ostream& os, const Persona& persona) {
    os << "Nombre: " << persona.getNombre() 
       << ", Cédula: " << persona.getCedula() 
       << ", ID: " << persona.getId();
    return os;
}

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Función para ingresar datos de una persona por consola
Persona ingresarPersona() {
    std::string nombre, cedula;
    int id;
    
    std::cout << "Ingrese el nombre: ";
    std::getline(std::cin, nombre);
    
    std::cout << "Ingrese la cédula: ";
    std::getline(std::cin, cedula);
    
    std::cout << "Ingrese el ID: ";
    while (!(std::cin >> id)) {
        std::cout << "Error: Ingrese un número válido para el ID: ";
        limpiarBuffer();
    }
    limpiarBuffer(); // Limpiar el buffer después de leer el entero
    
    return Persona(nombre, cedula, id);
}

// Función para mostrar el menú de opciones
void mostrarMenu() {
    std::cout << "\n===== MENU =====\n";
    std::cout << "1. Agregar persona\n";
    std::cout << "2. Buscar persona\n";
    std::cout << "3. Eliminar persona\n";
    std::cout << "4. Mostrar lista\n";
    std::cout << "5. Salir\n";
    std::cout << "Ingrese su opción: ";
}

int main() {
    ListaDoble<Persona> listaPersonas;
    int opcion;
    
    std::cout << "Sistema de Gestión de Personas\n";
    
    do {
        mostrarMenu();
        
        while (!(std::cin >> opcion) || opcion < 1 || opcion > 5) {
            std::cout << "Opción inválida. Ingrese un número entre 1 y 5: ";
            limpiarBuffer();
        }
        limpiarBuffer(); // Limpiar el buffer después de leer la opción
        
        switch (opcion) {
            case 1: { // Agregar persona
                std::cout << "\n--- Agregar Persona ---\n";
                Persona nuevaPersona = ingresarPersona();
                listaPersonas.crear(nuevaPersona);
                std::cout << "Persona agregada correctamente.\n";
                break;
            }
            case 2: { // Buscar persona
                std::cout << "\n--- Buscar Persona ---\n";
                if (listaPersonas.estaVacia()) {
                    std::cout << "La lista está vacía.\n";
                } else {
                    std::cout << "Ingrese los datos de la persona a buscar:\n";
                    Persona personaBuscada = ingresarPersona();
                    
                    Nodo<Persona>* nodoEncontrado = listaPersonas.buscar(personaBuscada);
                    if (nodoEncontrado != nullptr) {
                        std::cout << "Persona encontrada: " << nodoEncontrado->getDato() << std::endl;
                    } else {
                        std::cout << "Persona no encontrada.\n";
                    }
                }
                break;
            }
            case 3: { // Eliminar persona
                std::cout << "\n--- Eliminar Persona ---\n";
                if (listaPersonas.estaVacia()) {
                    std::cout << "La lista está vacía.\n";
                } else {
                    std::cout << "Ingrese los datos de la persona a eliminar:\n";
                    Persona personaEliminar = ingresarPersona();
                    
                    if (listaPersonas.eliminar(personaEliminar)) {
                        std::cout << "Persona eliminada correctamente.\n";
                    } else {
                        std::cout << "No se pudo eliminar la persona. No fue encontrada.\n";
                    }
                }
                break;
            }
            case 4: { // Mostrar lista
                std::cout << "\n--- Lista de Personas ---\n";
                listaPersonas.imprimir();
                break;
            }
            case 5: // Salir
                std::cout << "Saliendo del programa...\n";
                break;
        }
    } while (opcion != 5);
    
    return 0;
}