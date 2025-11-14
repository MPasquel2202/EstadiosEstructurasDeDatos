/***********************************************************************
 * Module:  ValidarDiscos.cpp
 * Author:  Claude
 * Modified: martes, 29 de abril de 2025
 * Purpose: Implementation of the class ValidarDiscos
 ***********************************************************************/

 #include "ValidarDiscos.h"

 ////////////////////////////////////////////////////////////////////////
 // Name:       ValidarDiscos::validarNumDiscos(int numDiscos)
 // Purpose:    Implementation of ValidarDiscos::validarNumDiscos()
 // Parameters:
 // - numDiscos
 // Return:     bool
 ////////////////////////////////////////////////////////////////////////
 
 bool ValidarDiscos::validarNumDiscos(int numDiscos)
 {
    // Establecemos un límite mínimo de 1 y máximo de 10
    // (más de 10 discos haría el juego muy largo)
    return numDiscos >= 1 && numDiscos <= 10;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       ValidarDiscos::ValidarDiscos()
 // Purpose:    Implementation of ValidarDiscos::ValidarDiscos()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 ValidarDiscos::ValidarDiscos()
 {
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       ValidarDiscos::~ValidarDiscos()
 // Purpose:    Implementation of ValidarDiscos::~ValidarDiscos()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 ValidarDiscos::~ValidarDiscos()
 {
    // No hay recursos que liberar
 }