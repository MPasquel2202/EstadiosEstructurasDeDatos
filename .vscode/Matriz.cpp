#pragma once
#include <iostream>
#include <functional>
#include <stdexcept>
#include <type_traits>
using namespace std;

class Matriz {
private:
    int filas;
    int columnas;
    double** datos;

    // Función auxiliar para copiar datos
    void copiarDatos(const Matriz& otra) {
        for (int i = 0; i < filas; i++)
            for (int j = 0; j < columnas; j++)
                datos[i][j] = otra.datos[i][j];
    }

public:
    Matriz(int f, int c) : filas(f), columnas(c) {
        if (f <= 0 || c <= 0)
            throw invalid_argument("Las dimensiones deben ser positivas");

        datos = new double*[filas];
        for (int i = 0; i < filas; i++) {
            datos[i] = new double[columnas](); // Inicializar a 0
        }
    }

    // Constructor de copia
    Matriz(const Matriz& otra) : filas(otra.filas), columnas(otra.columnas) {
        datos = new double*[filas];
        for (int i = 0; i < filas; i++) {
            datos[i] = new double[columnas];
            for (int j = 0; j < columnas; j++) {
                datos[i][j] = otra.datos[i][j];
            }
        }
    }

    // Operador de asignación
    Matriz& operator=(const Matriz& otra) {
        if (this != &otra) {
            // Liberar memoria actual
            for (int i = 0; i < filas; i++)
                delete[] datos[i];
            delete[] datos;

            // Asignar nuevas dimensiones
            filas = otra.filas;
            columnas = otra.columnas;

            // Copiar datos
            datos = new double*[filas];
            for (int i = 0; i < filas; i++) {
                datos[i] = new double[columnas];
                for (int j = 0; j < columnas; j++) {
                    datos[i][j] = otra.datos[i][j];
                }
            }
        }
        return *this;
    }

    ~Matriz() {
        for (int i = 0; i < filas; i++)
            delete[] datos[i];
        delete[] datos;
    }

    // Llenar manual o programáticamente
    void set(int i, int j, double valor) {
        if (i < 0 || i >= filas || j < 0 || j >= columnas)
            throw out_of_range("Índice fuera de rango");
        datos[i][j] = valor;
    }

    double get(int i, int j) const {
        if (i < 0 || i >= filas || j < 0 || j >= columnas)
            throw out_of_range("Índice fuera de rango");
        return datos[i][j];
    }

    Matriz operator*(const Matriz& otra) const {
        if (columnas != otra.filas)
            throw invalid_argument("No se pueden multiplicar: dimensiones incompatibles");

        Matriz resultado(filas, otra.columnas);
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < otra.columnas; j++) {
                double suma = 0;
                for (int k = 0; k < columnas; k++) {
                    suma += datos[i][k] * otra.datos[k][j];
                }
                resultado.set(i, j, suma);
            }
        }
        return resultado;
    }

    int getFilas() const { return filas; }
    int getColumnas() const { return columnas; }
};