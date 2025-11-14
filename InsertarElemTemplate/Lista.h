// Lista.h
#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"
#include <iostream>

template <class T>
class Lista {
private:
    Nodo<T>* primero;
    int tamanio;

public:
    // Constructores y destructor
    Lista();
    ~Lista();

    // Métodos básicos
    bool estaVacia() const;
    int getTamanio() const;
    
    // Operaciones de la lista
    void insertarAlInicio(const T* nombre, const T* apellido, const T* cedula);
    void insertarAlFinal(const T* nombre, const T* apellido, const T* cedula);
    void insertarEnPosicion(int posicion, const T* nombre, const T* apellido, const T* cedula);
    
    // Eliminación de elementos
    void eliminarPrimero();
    void eliminarUltimo();
    void eliminarEnPosicion(int posicion);
    
    // Búsqueda por cédula
    bool buscarPorCedula(const T* cedula) const;
    
    // Mostrar lista
    void mostrarLista() const;
    
    // Método auxiliar para comparar cadenas usando aritmética de punteros
    int compararCadenas(const T* str1, const T* str2) const;
};

#include "Lista.cpp"
#endif // LISTA_H