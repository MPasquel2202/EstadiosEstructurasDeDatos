/***********************************************************************
 * Module:  Fila.cpp
 * Author:  Programador
 * Modified: martes, 29 de abril de 2025 12:00:00
 * Purpose: Implementation of the class Fila (con recursividad)
 ***********************************************************************/

 #include "Fila.h"

 ////////////////////////////////////////////////////////////////////////
 // Name:       Fila::getElementos()
 // Purpose:    Implementation of Fila::getElementos()
 // Return:     std::vector<int>
 ////////////////////////////////////////////////////////////////////////
 
 std::vector<int> Fila::getElementos(void)
 {
    return elementos;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Fila::setElementos(std::vector<int> newElementos)
 // Purpose:    Implementation of Fila::setElementos()
 // Parameters:
 // - newElementos
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void Fila::setElementos(std::vector<int> newElementos)
 {
    elementos = newElementos;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Fila::getNumeroFila()
 // Purpose:    Implementation of Fila::getNumeroFila()
 // Return:     int
 ////////////////////////////////////////////////////////////////////////
 
 int Fila::getNumeroFila(void)
 {
    return numeroFila;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Fila::setNumeroFila(int newNumeroFila)
 // Purpose:    Implementation of Fila::setNumeroFila()
 // Parameters:
 // - newNumeroFila
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void Fila::setNumeroFila(int newNumeroFila)
 {
    numeroFila = newNumeroFila;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Fila::coeficienteBinomialRecursivo(int n, int k)
 // Purpose:    Calcula el coeficiente binomial C(n,k) de forma recursiva
 // Parameters:
 // - n: Fila del triángulo (comenzando en 0)
 // - k: Posición en la fila (comenzando en 0)
 // Return:     int
 ////////////////////////////////////////////////////////////////////////
 
 int Fila::coeficienteBinomialRecursivo(int n, int k)
 {
    // Casos base
    if (k == 0 || k == n)
       return 1;
    
    // Caso recursivo: C(n,k) = C(n-1,k-1) + C(n-1,k)
    return coeficienteBinomialRecursivo(n - 1, k - 1) + coeficienteBinomialRecursivo(n - 1, k);
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Fila::generarElementos()
 // Purpose:    Genera los elementos de una fila del Triángulo de Pascal
 //             usando recursividad
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void Fila::generarElementos(void)
 {
    elementos.clear();
    
    // Generamos cada elemento de la fila usando el método recursivo
    for (int k = 0; k <= numeroFila; k++) {
       int valor = coeficienteBinomialRecursivo(numeroFila, k);
       elementos.push_back(valor);
    }
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Fila::Fila()
 // Purpose:    Implementation of Fila::Fila()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 Fila::Fila()
 {
    numeroFila = 0;
    generarElementos();
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Fila::Fila(int numeroFila)
 // Purpose:    Implementation of Fila::Fila()
 // Parameters:
 // - numeroFila: Número de fila (comenzando en 0)
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 Fila::Fila(int newNumeroFila)
 {
    numeroFila = newNumeroFila;
    generarElementos();
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Fila::~Fila()
 // Purpose:    Implementation of Fila::~Fila()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 Fila::~Fila()
 {
    // No hay recursos que liberar explícitamente
 }