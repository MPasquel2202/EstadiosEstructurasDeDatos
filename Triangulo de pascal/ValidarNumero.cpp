/***********************************************************************
 * Module:  ValidarNumero.cpp
 * Author:  Programador
 * Modified: martes, 29 de abril de 2025 12:00:00
 * Purpose: Implementation of the class ValidarNumero
 ***********************************************************************/

 #include "ValidarNumero.h"

 ////////////////////////////////////////////////////////////////////////
 // Name:       ValidarNumero::validarNumero(int numero)
 // Purpose:    Implementation of ValidarNumero::validarNumero()
 // Parameters:
 // - numero
 // Return:     bool
 ////////////////////////////////////////////////////////////////////////
 
 bool ValidarNumero::validarNumero(int numero)
 {
    // Validamos que el número sea positivo para el triángulo de Pascal
    return numero > 0;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       ValidarNumero::validarRango(int numero, int minimo, int maximo)
 // Purpose:    Implementation of ValidarNumero::validarRango()
 // Parameters:
 // - numero
 // - minimo
 // - maximo
 // Return:     bool
 ////////////////////////////////////////////////////////////////////////
 
 bool ValidarNumero::validarRango(int numero, int minimo, int maximo)
 {
    return numero >= minimo && numero <= maximo;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       ValidarNumero::ValidarNumero()
 // Purpose:    Implementation of ValidarNumero::ValidarNumero()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 ValidarNumero::ValidarNumero()
 {
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       ValidarNumero::~ValidarNumero()
 // Purpose:    Implementation of ValidarNumero::~ValidarNumero()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 ValidarNumero::~ValidarNumero()
 {
    // No hay recursos que liberar
 }