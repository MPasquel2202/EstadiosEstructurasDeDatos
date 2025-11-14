/***********************************************************************
 * Module:  TrianguloPascal.cpp
 * Author:  Programador
 * Modified: martes, 29 de abril de 2025 12:00:00
 * Purpose: Implementation of the class TrianguloPascal
 ***********************************************************************/

 #include "TrianguloPascal.h"

 ////////////////////////////////////////////////////////////////////////
 // Name:       TrianguloPascal::getNumeroFilas()
 // Purpose:    Implementation of TrianguloPascal::getNumeroFilas()
 // Return:     int
 ////////////////////////////////////////////////////////////////////////
 
 int TrianguloPascal::getNumeroFilas(void)
 {
    return numeroFilas;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       TrianguloPascal::setNumeroFilas(int newNumeroFilas)
 // Purpose:    Implementation of TrianguloPascal::setNumeroFilas()
 // Parameters:
 // - newNumeroFilas
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void TrianguloPascal::setNumeroFilas(int newNumeroFilas)
 {
    numeroFilas = newNumeroFilas;
    generarTriangulo();
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       TrianguloPascal::getFilas()
 // Purpose:    Implementation of TrianguloPascal::getFilas()
 // Return:     std::vector<Fila>
 ////////////////////////////////////////////////////////////////////////
 
 std::vector<Fila> TrianguloPascal::getFilas(void)
 {
    return filas;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       TrianguloPascal::getFila(int numeroFila)
 // Purpose:    Implementation of TrianguloPascal::getFila()
 // Parameters:
 // - numeroFila
 // Return:     Fila
 ////////////////////////////////////////////////////////////////////////
 
 Fila TrianguloPascal::getFila(int numeroFila)
 {
    if (numeroFila >= 0 && numeroFila < numeroFilas) {
       return filas[numeroFila];
    }
    return Fila(); // Retorna una fila vacía si el índice es inválido
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       TrianguloPascal::generarTriangulo()
 // Purpose:    Genera todas las filas del Triángulo de Pascal
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void TrianguloPascal::generarTriangulo(void)
 {
    filas.clear();
    for (int i = 0; i < numeroFilas; i++) {
       filas.push_back(Fila(i));
    }
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       TrianguloPascal::TrianguloPascal()
 // Purpose:    Implementation of TrianguloPascal::TrianguloPascal()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 TrianguloPascal::TrianguloPascal()
 {
    numeroFilas = 0;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       TrianguloPascal::TrianguloPascal(int numeroFilas)
 // Purpose:    Implementation of TrianguloPascal::TrianguloPascal()
 // Parameters:
 // - numeroFilas
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 TrianguloPascal::TrianguloPascal(int newNumeroFilas)
 {
    numeroFilas = newNumeroFilas;
    generarTriangulo();
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       TrianguloPascal::~TrianguloPascal()
 // Purpose:    Implementation of TrianguloPascal::~TrianguloPascal()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 TrianguloPascal::~TrianguloPascal()
 {
    // No hay recursos que liberar explícitamente
 }