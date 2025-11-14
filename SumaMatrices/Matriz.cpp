#include "Matriz.h"
#include <iostream>

using namespace std;



int Matriz::getFilas(void)
{
   return filas;
}

void Matriz::setFilas(int newFilas)
{
   filas = newFilas;
}

int Matriz::getColumnas(void)
{
   return columnas;
}

void Matriz::setColumnas(int newColumnas)
{
   columnas = newColumnas;
}

int** Matriz::getMatriz(void)
{
   return matriz;
}

void Matriz::setMatriz(int** newMatriz)
{
   matriz = newMatriz;
}

void Matriz::crearMatriz(int filas, int columnas)
{
   this->filas = filas;
   this->columnas = columnas;
   
   // Asignación dinámica de memoria para la matriz
   matriz = new int*[filas];
   for (int i = 0; i < filas; i++) {
      matriz[i] = new int[columnas];
      // Inicializar con ceros
      for (int j = 0; j < columnas; j++) {
         matriz[i][j] = 0;
      }
   }
}

void Matriz::liberarMemoria(void)
{
   if (matriz != nullptr) {
      for (int i = 0; i < filas; i++) {
         delete[] matriz[i];
      }
      delete[] matriz;
      matriz = nullptr;
   }
}

void Matriz::imprimirMatriz(void)
{
   for (int i = 0; i < filas; i++) {
      for (int j = 0; j < columnas; j++) {
         cout << matriz[i][j] << "\t";
      }
      cout << endl;
   }
}


Matriz::Matriz()
{
   filas = 0;
   columnas = 0;
   matriz = nullptr;
}


Matriz::Matriz(int filas, int columnas)
{
   crearMatriz(filas, columnas);
}


Matriz::~Matriz()
{
   liberarMemoria();
}