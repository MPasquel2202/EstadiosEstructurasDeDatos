#include <iostream>
#include "Matriz.h"
#include "OperacionesMatriz.h"
#include "IngresoDatos.h"
#include "ValidarDimension.h"

using namespace std;

// Función para llenar una matriz con datos ingresados por el usuario
void llenarMatriz(Matriz &matriz, const char* titulo) {
    IngresoDatos ingreso;
    
    cout << "\n===== " << titulo << " =====" << endl;
    
    for (int i = 0; i < matriz.getFilas(); i++) {
        for (int j = 0; j < matriz.getColumnas(); j++) {
            char mensaje[50];
            sprintf(mensaje, "Ingrese el valor para [%d][%d]: ", i+1, j+1);
            int valor = ingreso.pedirNumero(mensaje);
            matriz.getMatriz()[i][j] = valor;
        }
    }
}

int main() {
    IngresoDatos ingreso;
    ValidarDimension validar;
    OperacionesMatriz operaciones;
    
    int filas, columnas;
    
    // Pedir y validar las dimensiones de las matrices
    do {
        filas = ingreso.pedirNumero("Ingrese el numero de filas: ");
        if (!validar.validarDimension(filas)) {
            cout << "\nDimension invalida. Debe ser mayor a 0." << endl;
        }
    } while (!validar.validarDimension(filas));
    
    do {
        columnas = ingreso.pedirNumero("Ingrese el numero de columnas: ");
        if (!validar.validarDimension(columnas)) {
            cout << "\nDimension invalida. Debe ser mayor a 0." << endl;
        }
    } while (!validar.validarDimension(columnas));
    
    // Crear las matrices con las dimensiones especificadas
    Matriz matriz1(filas, columnas);
    Matriz matriz2(filas, columnas);
    
    // Llenar las matrices con valores ingresados por el usuario
    llenarMatriz(matriz1, "MATRIZ 1");
    llenarMatriz(matriz2, "MATRIZ 2");
    
    // Mostrar las matrices ingresadas
    cout << "\n===== MATRIZ 1 =====" << endl;
    matriz1.imprimirMatriz();
    
    cout << "\n===== MATRIZ 2 =====" << endl;
    matriz2.imprimirMatriz();
    
    // Sumar las matrices
    Matriz resultado = operaciones.sumarMatrices(matriz1, matriz2);
    
    // Mostrar el resultado de la suma
    cout << "\n===== RESULTADO DE LA SUMA =====" << endl;
    resultado.imprimirMatriz();
    
    return 0;
}