/***********************************************************************
 * Module:  ValidarLimite.cpp
 * Author:  USUARIO
 * Modified: martes, 29 de abril de 2025
 * Purpose: Implementation of the class ValidarLimite
 ***********************************************************************/

 #include "ValidarLimite.h"

 ////////////////////////////////////////////////////////////////////////
 // Name:       ValidarLimite::validarLimite(int limite)
 // Purpose:    Implementation of ValidarLimite::validarLimite()
 // Parameters:
 // - limite
 // Return:     bool
 ////////////////////////////////////////////////////////////////////////
 
 bool ValidarLimite::validarLimite(int limite)
 {
    // Validamos que el límite sea un número positivo
    // y no sea demasiado grande para evitar desbordamiento en la recursividad
    return limite >= 0 && limite <= 30;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       ValidarLimite::ValidarLimite()
 // Purpose:    Implementation of ValidarLimite::ValidarLimite()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 ValidarLimite::ValidarLimite()
 {
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       ValidarLimite::~ValidarLimite()
 // Purpose:    Implementation of ValidarLimite::~ValidarLimite()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 ValidarLimite::~ValidarLimite()
 {
    // TODO : implement
 }