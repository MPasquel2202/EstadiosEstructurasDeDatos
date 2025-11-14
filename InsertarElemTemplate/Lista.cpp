// Lista.cpp
#ifndef LISTA_CPP
#define LISTA_CPP

#include "Lista.h"

template <class T>
Lista<T>::Lista() {
    primero = nullptr;
    tamanio = 0;
}

template <class T>
Lista<T>::~Lista() {
    // Eliminar todos los nodos
    while (!estaVacia()) {
        eliminarPrimero();
    }
}

template <class T>
bool Lista<T>::estaVacia() const {
    return primero == nullptr;
}

template <class T>
int Lista<T>::getTamanio() const {
    return tamanio;
}

template <class T>
void Lista<T>::insertarAlInicio(const T* nombre, const T* apellido, const T* cedula) {
    Nodo<T>* nuevo = new Nodo<T>(nombre, apellido, cedula);
    
    if (estaVacia()) {
        primero = nuevo;
    } else {
        nuevo->setSiguiente(primero);
        primero = nuevo;
    }
    
    tamanio++;
}

template <class T>
void Lista<T>::insertarAlFinal(const T* nombre, const T* apellido, const T* cedula) {
    Nodo<T>* nuevo = new Nodo<T>(nombre, apellido, cedula);
    
    if (estaVacia()) {
        primero = nuevo;
    } else {
        Nodo<T>* actual = primero;
        
        // Recorrer hasta el último nodo
        while (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        }
        
        actual->setSiguiente(nuevo);
    }
    
    tamanio++;
}

template <class T>
void Lista<T>::insertarEnPosicion(int posicion, const T* nombre, const T* apellido, const T* cedula) {
    // Validar posición
    if (posicion < 0 || posicion > tamanio) {
        std::cout << "Posicion invalida" << std::endl;
        return;
    }
    
    // Si es al inicio, usar método específico
    if (posicion == 0) {
        insertarAlInicio(nombre, apellido, cedula);
        return;
    }
    
    // Si es al final, usar método específico
    if (posicion == tamanio) {
        insertarAlFinal(nombre, apellido, cedula);
        return;
    }
    
    // Insertar en medio
    Nodo<T>* nuevo = new Nodo<T>(nombre, apellido, cedula);
    Nodo<T>* actual = primero;
    
    // Moverse hasta la posición anterior
    for (int i = 0; i < posicion - 1; i++) {
        actual = actual->getSiguiente();
    }
    
    nuevo->setSiguiente(actual->getSiguiente());
    actual->setSiguiente(nuevo);
    
    tamanio++;
}

template <class T>
void Lista<T>::eliminarPrimero() {
    if (estaVacia()) {
        std::cout << "La lista esta vacia" << std::endl;
        return;
    }
    
    Nodo<T>* temp = primero;
    primero = primero->getSiguiente();
    delete temp;
    
    tamanio--;
}

template <class T>
void Lista<T>::eliminarUltimo() {
    if (estaVacia()) {
        std::cout << "La lista está vacia" << std::endl;
        return;
    }
    
    // Si solo hay un nodo
    if (primero->getSiguiente() == nullptr) {
        delete primero;
        primero = nullptr;
        tamanio = 0;
        return;
    }
    
    // Recorrer hasta el penúltimo nodo
    Nodo<T>* actual = primero;
    while (actual->getSiguiente()->getSiguiente() != nullptr) {
        actual = actual->getSiguiente();
    }
    
    // Eliminar el último
    delete actual->getSiguiente();
    actual->setSiguiente(nullptr);
    
    tamanio--;
}

template <class T>
void Lista<T>::eliminarEnPosicion(int posicion) {
    // Validar posición
    if (posicion < 0 || posicion >= tamanio) {
        std::cout << "Posicion invalida" << std::endl;
        return;
    }
    
    // Si es el primero, usar método específico
    if (posicion == 0) {
        eliminarPrimero();
        return;
    }
    
    // Si es el último, usar método específico
    if (posicion == tamanio - 1) {
        eliminarUltimo();
        return;
    }
    
    // Eliminar en medio
    Nodo<T>* actual = primero;
    
    // Moverse hasta la posicion anterior
    for (int i = 0; i < posicion - 1; i++) {
        actual = actual->getSiguiente();
    }
    
    Nodo<T>* temp = actual->getSiguiente();
    actual->setSiguiente(temp->getSiguiente());
    delete temp;
    
    tamanio--;
}

// Método auxiliar para comparar cadenas usando aritmética de punteros
template <class T>
int Lista<T>::compararCadenas(const T* str1, const T* str2) const {
    const T* s1 = str1;
    const T* s2 = str2;
    
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

template <class T>
bool Lista<T>::buscarPorCedula(const T* cedula) const {
    if (estaVacia()) {
        return false;
    }
    
    Nodo<T>* actual = primero;
    
    while (actual != nullptr) {
        if (compararCadenas(actual->getCedula(), cedula) == 0) {
            return true;
        }
        actual = actual->getSiguiente();
    }
    
    return false;
}

template <class T>
void Lista<T>::mostrarLista() const {
    if (estaVacia()) {
        std::cout << "La lista está vacia" << std::endl;
        return;
    }
    
    Nodo<T>* actual = primero;
    int contador = 0;
    
    std::cout << "Contenido de la lista:" << std::endl;
    
    while (actual != nullptr) {
        std::cout << "Nodo " << contador << ": " << std::endl;
        std::cout << "  Nombre: " << actual->getNombre() << std::endl;
        std::cout << "  Apellido: " << actual->getApellido() << std::endl;
        std::cout << "  Cedula: " << actual->getCedula() << std::endl;
        
        actual = actual->getSiguiente();
        contador++;
    }
}

#endif // LISTA_CPP