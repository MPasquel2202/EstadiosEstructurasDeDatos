#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H

#include <iostream>
#include <functional>
#include "Nodo.h"

template<typename T>
class ListaDoble {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    int tamano;

public:
    ListaDoble();
    ~ListaDoble();
    
    // Métodos principales solicitados
    void crear(const T& dato);  // Agrega un nuevo elemento
    bool eliminar(const T& dato);  // Elimina un elemento
    Nodo<T>* buscar(const T& dato);  // Busca un elemento
    void imprimir() const;  // Imprime la lista
    
    // Métodos adicionales útiles
    bool estaVacia() const;
    int getTamano() const;
    void limpiar();
};

// Implementación de la clase ListaDoble

template<typename T>
ListaDoble<T>::ListaDoble() : cabeza(nullptr), cola(nullptr), tamano(0) {}

template<typename T>
ListaDoble<T>::~ListaDoble() {
    limpiar();
}

template<typename T>
void ListaDoble<T>::crear(const T& dato) {
    Nodo<T>* nuevoNodo = new Nodo<T>(dato);
    
    if (estaVacia()) {
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    } else {
        nuevoNodo->setAnterior(cola);
        cola->setSiguiente(nuevoNodo);
        cola = nuevoNodo;
    }
    
    tamano++;
}

template<typename T>
bool ListaDoble<T>::eliminar(const T& dato) {
    if (estaVacia()) {
        return false;
    }
    
    Nodo<T>* actual = cabeza;
    
    while (actual != nullptr) {
        if (actual->getDato() == dato) {
            // Caso: es el primer nodo
            if (actual == cabeza) {
                cabeza = actual->getSiguiente();
                if (cabeza != nullptr) {
                    cabeza->setAnterior(nullptr);
                } else {
                    cola = nullptr; // La lista quedó vacía
                }
            }
            // Caso: es el último nodo
            else if (actual == cola) {
                cola = actual->getAnterior();
                cola->setSiguiente(nullptr);
            }
            // Caso: es un nodo intermedio
            else {
                actual->getAnterior()->setSiguiente(actual->getSiguiente());
                actual->getSiguiente()->setAnterior(actual->getAnterior());
            }
            
            delete actual;
            tamano--;
            return true;
        }
        
        actual = actual->getSiguiente();
    }
    
    return false; // No se encontró el elemento
}

template<typename T>
Nodo<T>* ListaDoble<T>::buscar(const T& dato) {
    Nodo<T>* actual = cabeza;
    
    while (actual != nullptr) {
        if (actual->getDato() == dato) {
            return actual;
        }
        actual = actual->getSiguiente();
    }
    
    return nullptr; // No se encontró el elemento
}

template<typename T>
void ListaDoble<T>::imprimir() const {
    if (estaVacia()) {
        std::cout << "La lista está vacía." << std::endl;
        return;
    }
    
    Nodo<T>* actual = cabeza;
    int posicion = 0;
    
    std::cout << "Lista doblemente enlazada (Tamaño: " << tamano << "):" << std::endl;
    
    while (actual != nullptr) {
        std::cout << "Posición " << posicion << ": " << std::endl;
        // Se asume que el tipo T tiene una forma de ser impreso
        std::cout << "  Dato: " << actual->getDato() << std::endl;
        actual = actual->getSiguiente();
        posicion++;
    }
}

template<typename T>
bool ListaDoble<T>::estaVacia() const {
    return cabeza == nullptr;
}

template<typename T>
int ListaDoble<T>::getTamano() const {
    return tamano;
}

template<typename T>
void ListaDoble<T>::limpiar() {
    while (cabeza != nullptr) {
        Nodo<T>* temp = cabeza;
        cabeza = cabeza->getSiguiente();
        delete temp;
    }
    cabeza = nullptr;
    cola = nullptr;
    tamano = 0;
}

#endif // LISTA_DOBLE_H