/***********************************************************************
 * Module:  ValidarMes.cpp
 * Author:  USUARIO
 * Modified: domingo, 27 de abril de 2025 11:56:42
 * Purpose: Implementation of the class ValidarMes
 ***********************************************************************/

#include "ValidarMes.h"

////////////////////////////////////////////////////////////////////////
// Name:       ValidarMes::validarMes(int mes)
// Purpose:    Implementation of ValidarMes::validarMes()
// Parameters:
// - mes
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool ValidarMes::validarMes(int mes)
{
   // TODO : implement
   return mes >= 1 && mes <= 12;
}