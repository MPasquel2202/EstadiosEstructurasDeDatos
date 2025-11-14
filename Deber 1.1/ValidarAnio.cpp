/***********************************************************************
 * Module:  ValidarAnio.cpp
 * Author:  USUARIO
 * Modified: domingo, 27 de abril de 2025 11:56:42
 * Purpose: Implementation of the class ValidarAnio
 ***********************************************************************/

#include "ValidarAnio.h"

////////////////////////////////////////////////////////////////////////
// Name:       ValidarAnio::esBisiesto(int anio)
// Purpose:    Implementation of ValidarAnio::esBisiesto()
// Parameters:
// - anio
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool ValidarAnio::esBisiesto(int anio)
{
   // TODO : implement
   // Un año es bisiesto si es divisible entre 4,
   // pero no si es divisible entre 100, salvo que también sea divisible entre 400.
   if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {
      return true;
   }
   return false;
}

////////////////////////////////////////////////////////////////////////
// Name:       ValidarAnio::validarAnio(int anio)
// Purpose:    Implementation of ValidarAnio::validarAnio()
// Parameters:
// - anio
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool ValidarAnio::validarAnio(int anio)
{
   // TODO : implement
   // Podemos definir un rango razonable: por ejemplo, mayores a 0.
   return anio > 0;
}