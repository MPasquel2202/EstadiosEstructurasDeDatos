/***********************************************************************
 * Module:  Potencia.cpp
 * Author:  USUARIO
 * Modified: martes, 29 de abril de 2025
 * Purpose: Implementation of the class Potencia
 ***********************************************************************/

 #include "Potencia.h"
 #include <cmath>
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Potencia::getValor()
 // Purpose:    Implementation of Potencia::getValor()
 // Return:     int
 ////////////////////////////////////////////////////////////////////////
 
 int Potencia::getValor(void)
 {
    return valor;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Potencia::setValor(int newValor)
 // Purpose:    Implementation of Potencia::setValor()
 // Parameters:
 // - newValor
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void Potencia::setValor(int newValor)
 {
    valor = newValor;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Potencia::getExponente()
 // Purpose:    Implementation of Potencia::getExponente()
 // Return:     int
 ////////////////////////////////////////////////////////////////////////
 
 int Potencia::getExponente(void)
 {
    return exponente;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Potencia::setExponente(int newExponente)
 // Purpose:    Implementation of Potencia::setExponente()
 // Parameters:
 // - newExponente
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void Potencia::setExponente(int newExponente)
 {
    exponente = newExponente;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Potencia::calcularPotencia()
 // Purpose:    Implementation of Potencia::calcularPotencia()
 // Return:     int
 ////////////////////////////////////////////////////////////////////////
 
 int Potencia::calcularPotencia()
 {
    // Utiliza el método recursivo para calcular la potencia
    return calcularPotenciaRecursiva(valor, exponente);
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Potencia::calcularPotenciaRecursiva(int base, int exponente)
 // Purpose:    Implementation of Potencia::calcularPotenciaRecursiva()
 // Parameters:
 // - base
 // - exponente
 // Return:     long long
 ////////////////////////////////////////////////////////////////////////
 
 long long Potencia::calcularPotenciaRecursiva(int base, int exponente)
 {
    // Caso base
    if (exponente == 0)
       return 1;
    
    // Caso recursivo
    if (exponente % 2 == 0) {
       // Si el exponente es par, calculamos la mitad y luego multiplicamos por sí mismo
       long long mitad = calcularPotenciaRecursiva(base, exponente / 2);
       return mitad * mitad;
    } else {
       // Si el exponente es impar, calculamos base * base^(exponente-1)
       return base * calcularPotenciaRecursiva(base, exponente - 1);
    }
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Potencia::Potencia()
 // Purpose:    Implementation of Potencia::Potencia()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 Potencia::Potencia()
 {
    valor = 2; // Por defecto es base 2
    exponente = 0;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Potencia::~Potencia()
 // Purpose:    Implementation of Potencia::~Potencia()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 Potencia::~Potencia()
 {
    // TODO : implement
 }