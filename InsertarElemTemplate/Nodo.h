// Nodo.h
#ifndef NODO_H
#define NODO_H

#include <cstring>

template <class T>
class Nodo {
private:
    T* nombre;
    T* apellido;
    T* cedula;
    Nodo<T>* siguiente;

public:
    // Constructores y destructor
    Nodo();
    Nodo(const T* nombre, const T* apellido, const T* cedula);
    ~Nodo();

    // Métodos getters
    T* getNombre() const;
    T* getApellido() const;
    T* getCedula() const;
    Nodo<T>* getSiguiente() const;

    // Métodos setters
    void setNombre(const T* nombre);
    void setApellido(const T* apellido);
    void setCedula(const T* cedula);
    void setSiguiente(Nodo<T>* siguiente);
};

#include "Nodo.cpp"
#endif // NODO_H