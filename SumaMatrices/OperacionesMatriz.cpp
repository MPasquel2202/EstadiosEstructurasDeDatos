#include "OperacionesMatriz.h"
#include <iostream>

using namespace std;

Matriz OperacionesMatriz::sumarMatrices(Matriz matriz1, Matriz matriz2)
{
   // Verificar si las dimensiones son compatibles para la suma
   if (matriz1.getFilas() != matriz2.getFilas() || 
       matriz1.getColumnas() != matriz2.getColumnas()) {
       
       cout << "Error: Las matrices no tienen dimensiones compatibles para la suma." << endl;
       return Matriz(); // Retorna una matriz vacía
   }
   
   int filas = matriz1.getFilas();
   int columnas = matriz1.getColumnas();
   
   // Crear la matriz resultado con las mismas dimensiones
   Matriz resultado(filas, columnas);
   
   // Realizar la suma elemento a elemento
   for (int i = 0; i < filas; i++) {
      for (int j = 0; j < columnas; j++) {
         resultado.getMatriz()[i][j] = matriz1.getMatriz()[i][j] + matriz2.getMatriz()[i][j];
      }
   }
   
   return resultado;
}

OperacionesMatriz::OperacionesMatriz()
{
}

OperacionesMatriz::~OperacionesMatriz()
{
   // TODO : implement
}
