// Main.cpp
#include "Validaciones.h"
#include "Lista.h"
#include <iostream>
#include <limits>
#include <cstring>

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Función para asignar memoria dinámicamente y leer entrada desde la consola
char* leerEntrada(int maxLength) {
    char* buffer = new char[maxLength];
    char* ptr = buffer;
    char c;
    int count = 0;
    
    while (count < maxLength - 1 && (c = std::cin.get()) != '\n') {
        *ptr = c;
        ptr++;
        count++;
    }
    *ptr = '\0';
    
    // Si hay caracteres adicionales en el buffer, limpiarlos
    if (count == maxLength - 1 && c != '\n') {
        limpiarBuffer();
    }
    
    return buffer;
}

int main() {
    // Crear una lista de caracteres
    Lista<char> listaPersonas;
    int opcion = 0;
    
    do {
        std::cout << "1. Insertar persona al inicio" << std::endl;
        std::cout << "2. Insertar persona al final" << std::endl;
        std::cout << "3. Insertar persona en posicion especifica" << std::endl;
        std::cout << "4. Eliminar primera persona" << std::endl;
        std::cout << "5. Eliminar ultima persona" << std::endl;
        std::cout << "6. Eliminar persona en posicion especifica" << std::endl;
        std::cout << "7. Buscar persona por cedula" << std::endl;
        std::cout << "8. Mostrar lista de personas" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Ingrese su opcion: ";
        
        opcion= ingresar_entero("ingrese su opcion: ");
        
        // Variables para almacenar datos temporalmente
        char* nombre;
        char* apellido;
        char* cedula;
        int posicion;
        
        switch(opcion) {
            case 1: // Insertar al inicio
              std::cout << "\nIngresando persona al inicio de la lista" << std::endl;

            std:: string nombreStr = ingresar_string("Nombre:");
            nombre= new char[nombreStr.length() + 1];
            strcpy(nombre, nombreStr.c_str());

            std:: string apellidoStr= ingresar_string("Apellido:");
            apellido= new char[apellidoStr.length()+1];
            strcpy(apellido, apellidoStr.c_str());

            std:: string cedulaStr= ingresar_cedula("Cedula:");
            cedula= new char[cedulaStr.length()+1];
            strcpy(cedula,cedulaStr.c_str());

            listaPersonas.insertarAlInicio(nombre,apellido,cedula);
            std:: cout <<"Persona insertada correctamente al inicio." << std:: endl;

                delete[] nombre;
                delete[] apellido;
                delete[] cedula;
                break;
                
            case 2: // Insertar al final
                std::cout << "\nIngresando persona al final de la lista" << std::endl;
                
                std::cout << "Nombre: ";
                nombre = leerEntrada(100);
                
                std::cout << "Apellido: ";
                apellido = leerEntrada(100);
                
                std::cout << "Cedula: ";
                cedula = leerEntrada(20);
                
                listaPersonas.insertarAlFinal(nombre, apellido, cedula);
                std::cout << "Persona insertada correctamente al final." << std::endl;
                
                delete[] nombre;
                delete[] apellido;
                delete[] cedula;
                break;
                
            case 3: // Insertar en posición
                std::cout << "\nIngresando persona en posicion especifica" << std::endl;
                
                std::cout << "Posicion (0 es al inicio): ";
                std::cin >> posicion;
                limpiarBuffer();
                
                std::cout << "Nombre: ";
                nombre = leerEntrada(100);
                
                std::cout << "Apellido: ";
                apellido = leerEntrada(100);
                
                std::cout << "Cedula: ";
                cedula = leerEntrada(20);
                
                listaPersonas.insertarEnPosicion(posicion, nombre, apellido, cedula);
                std::cout << "Persona insertada correctamente en la posicion " << posicion << "." << std::endl;
                
                delete[] nombre;
                delete[] apellido;
                delete[] cedula;
                break;
                
            case 4: // Eliminar primero
                if (!listaPersonas.estaVacia()) {
                    listaPersonas.eliminarPrimero();
                    std::cout << "Primera persona eliminada correctamente." << std::endl;
                } else {
                    std::cout << "La lista esta vacia." << std::endl;
                }
                break;
                
            case 5: // Eliminar último
                if (!listaPersonas.estaVacia()) {
                    listaPersonas.eliminarUltimo();
                    std::cout << "Ultima persona eliminada correctamente." << std::endl;
                } else {
                    std::cout << "La lista esta vacia." << std::endl;
                }
                break;
                
            case 6: // Eliminar en posicion
                if (!listaPersonas.estaVacia()) {
                    std::cout << "Posicion a eliminar: ";
                    std::cin >> posicion;
                    limpiarBuffer();
                    
                    listaPersonas.eliminarEnPosicion(posicion);
                } else {
                    std::cout << "La lista esta vacia." << std::endl;
                }
                break;
                
            case 7: // Buscar por cedula
                std::cout << "Ingrese la cedula a buscar: ";
                cedula = leerEntrada(20);
                
                if (listaPersonas.buscarPorCedula(cedula)) {
                    std::cout << "La persona con cedula " << cedula << " esta en la lista." << std::endl;
                } else {
                    std::cout << "No se encontro la persona con cedula " << cedula << "." << std::endl;
                }
                
                delete[] cedula;
                break;
                
            case 8: // Mostrar lista
                listaPersonas.mostrarLista();
                break;
                
            case 0: // Salir
                std::cout << "Saliendo del programa..." << std::endl;
                break;
                
            default:
                std::cout << "Opcion invalida. Intente nuevamente." << std::endl;
        }
        
    } while (opcion != 0);
    
    return 0;
}