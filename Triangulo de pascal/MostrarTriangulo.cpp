/***********************************************************************
 * Module:  MostrarTriangulo.cpp
 * Author:  Programador
 * Modified: martes, 29 de abril de 2025 12:00:00
 * Purpose: Implementation of the class MostrarTriangulo
 ***********************************************************************/

 #include "MostrarTriangulo.h"
 #include <iostream>
 #include <iomanip>
 #include <string>
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       MostrarTriangulo::mostrarCentrado(TrianguloPascal triangulo)
 // Purpose:    Implementation of MostrarTriangulo::mostrarCentrado()
 // Parameters:
 // - triangulo
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void MostrarTriangulo::mostrarCentrado(TrianguloPascal triangulo)
 {
    int numFilas = triangulo.getNumeroFilas();
    std::vector<Fila> filas = triangulo.getFilas();
    
    // Para centrar correctamente, calculamos el ancho máximo necesario
    int anchoMax = 0;
    for (int i = numFilas - 1; i < numFilas; i++) {
       std::vector<int> elementos = filas[i].getElementos();
       int anchoFila = 0;
       for (size_t j = 0; j < elementos.size(); j++) {
          // Estimamos el ancho de cada número + un espacio
          anchoFila += std::to_string(elementos[j]).length() + 1;
       }
       if (anchoFila > anchoMax) {
          anchoMax = anchoFila;
       }
    }
    
    std::cout << "\nTriangulo de Pascal (centrado):\n" << std::endl;
    
    for (int i = 0; i < numFilas; i++) {
       std::vector<int> elementos = filas[i].getElementos();
       
       // Calculamos el ancho de la fila actual para centrarla
       int anchoActual = 0;
       for (size_t j = 0; j < elementos.size(); j++) {
          anchoActual += std::to_string(elementos[j]).length() + 1;
       }
       
       // Calculamos el padding necesario para centrar
       int padding = (anchoMax - anchoActual) / 2;
       
       // Aplicamos el padding
       std::cout << std::string(padding, ' ');
       
       // Mostramos los elementos
       for (size_t j = 0; j < elementos.size(); j++) {
          std::cout << elementos[j] << " ";
       }
       
       std::cout << std::endl;
    }
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       MostrarTriangulo::mostrarAlineadoIzquierda(TrianguloPascal triangulo)
 // Purpose:    Implementation of MostrarTriangulo::mostrarAlineadoIzquierda()
 // Parameters:
 // - triangulo
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void MostrarTriangulo::mostrarAlineadoIzquierda(TrianguloPascal triangulo)
 {
    int numFilas = triangulo.getNumeroFilas();
    std::vector<Fila> filas = triangulo.getFilas();
    
    std::cout << "\nTriangulo de Pascal (alineado a la izquierda):\n" << std::endl;
    
    for (int i = 0; i < numFilas; i++) {
       std::vector<int> elementos = filas[i].getElementos();
       
       for (size_t j = 0; j < elementos.size(); j++) {
          std::cout << std::setw(4) << elementos[j];
       }
       
       std::cout << std::endl;
    }
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       MostrarTriangulo::MostrarTriangulo()
 // Purpose:    Implementation of MostrarTriangulo::MostrarTriangulo()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 MostrarTriangulo::MostrarTriangulo()
 {
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       MostrarTriangulo::~MostrarTriangulo()
 // Purpose:    Implementation of MostrarTriangulo::~MostrarTriangulo()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 MostrarTriangulo::~MostrarTriangulo()
 {
    // No hay recursos que liberar
 }