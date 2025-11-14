// Nodo.cpp
#ifndef NODO_CPP
#define NODO_CPP

#include "Nodo.h"

template <class T>
Nodo<T>::Nodo() {
    nombre = nullptr;
    apellido = nullptr;
    cedula = nullptr;
    siguiente = nullptr;
}

template <class T>
Nodo<T>::Nodo(const T* nombre, const T* apellido, const T* cedula) {
    // Asignación de memoria y copia de datos usando aritmética de punteros
    size_t nombreLen = 0;
    const T* ptrNombre = nombre;
    while (*ptrNombre != '\0') {
        nombreLen++;
        ptrNombre++;
    }
    
    this->nombre = new T[nombreLen + 1];
    T* destNombre = this->nombre;
    const T* srcNombre = nombre;
    while (*srcNombre != '\0') {
        *destNombre = *srcNombre;
        destNombre++;
        srcNombre++;
    }
    *destNombre = '\0';
    
    size_t apellidoLen = 0;
    const T* ptrApellido = apellido;
    while (*ptrApellido != '\0') {
        apellidoLen++;
        ptrApellido++;
    }
    
    this->apellido = new T[apellidoLen + 1];
    T* destApellido = this->apellido;
    const T* srcApellido = apellido;
    while (*srcApellido != '\0') {
        *destApellido = *srcApellido;
        destApellido++;
        srcApellido++;
    }
    *destApellido = '\0';
    
    size_t cedulaLen = 0;
    const T* ptrCedula = cedula;
    while (*ptrCedula != '\0') {
        cedulaLen++;
        ptrCedula++;
    }
    
    this->cedula = new T[cedulaLen + 1];
    T* destCedula = this->cedula;
    const T* srcCedula = cedula;
    while (*srcCedula != '\0') {
        *destCedula = *srcCedula;
        destCedula++;
        srcCedula++;
    }
    *destCedula = '\0';
    
    this->siguiente = nullptr;
}

template <class T>
Nodo<T>::~Nodo() {
    // Liberación de memoria
    if (nombre) delete[] nombre;
    if (apellido) delete[] apellido;
    if (cedula) delete[] cedula;
}

// Implementación de métodos getters
template <class T>
T* Nodo<T>::getNombre() const {
    return nombre;
}

template <class T>
T* Nodo<T>::getApellido() const {
    return apellido;
}

template <class T>
T* Nodo<T>::getCedula() const {
    return cedula;
}

template <class T>
Nodo<T>* Nodo<T>::getSiguiente() const {
    return siguiente;
}

// Implementación de métodos setters con aritmética de punteros
template <class T>
void Nodo<T>::setNombre(const T* nombre) {
    if (this->nombre) delete[] this->nombre;
    
    size_t nombreLen = 0;
    const T* ptrNombre = nombre;
    while (*ptrNombre != '\0') {
        nombreLen++;
        ptrNombre++;
    }
    
    this->nombre = new T[nombreLen + 1];
    T* destNombre = this->nombre;
    const T* srcNombre = nombre;
    while (*srcNombre != '\0') {
        *destNombre = *srcNombre;
        destNombre++;
        srcNombre++;
    }
    *destNombre = '\0';
}

template <class T>
void Nodo<T>::setApellido(const T* apellido) {
    if (this->apellido) delete[] this->apellido;
    
    size_t apellidoLen = 0;
    const T* ptrApellido = apellido;
    while (*ptrApellido != '\0') {
        apellidoLen++;
        ptrApellido++;
    }
    
    this->apellido = new T[apellidoLen + 1];
    T* destApellido = this->apellido;
    const T* srcApellido = apellido;
    while (*srcApellido != '\0') {
        *destApellido = *srcApellido;
        destApellido++;
        srcApellido++;
    }
    *destApellido = '\0';
}

template <class T>
void Nodo<T>::setCedula(const T* cedula) {
    if (this->cedula) delete[] this->cedula;
    
    size_t cedulaLen = 0;
    const T* ptrCedula = cedula;
    while (*ptrCedula != '\0') {
        cedulaLen++;
        ptrCedula++;
    }
    
    this->cedula = new T[cedulaLen + 1];
    T* destCedula = this->cedula;
    const T* srcCedula = cedula;
    while (*srcCedula != '\0') {
        *destCedula = *srcCedula;
        destCedula++;
        srcCedula++;
    }
    *destCedula = '\0';
}

template <class T>
void Nodo<T>::setSiguiente(Nodo<T>* siguiente) {
    this->siguiente = siguiente;
}

#endif // NODO_CPP