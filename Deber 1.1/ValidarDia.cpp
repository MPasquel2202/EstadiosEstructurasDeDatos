/***********************************************************************
 * Module:  ValidarDia.cpp
 * Author:  USUARIO
 * Modified: domingo, 27 de abril de 2025 11:56:42
 * Purpose: Implementation of the class ValidarDia
 ***********************************************************************/

#include "ValidarDia.h"
#include "ValidarAnio.h"

////////////////////////////////////////////////////////////////////////
// Name:       ValidarDia::validarDia(int dia, int mes, int anio)
// Purpose:    Implementation of ValidarDia::validarDia()
// Parameters:
// - dia
// - mes
// - anio
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool ValidarDia::validarDia(int dia, int mes, int anio)
{
   // TODO : implement
   if (dia < 1) {
      return false;
   }

   int diasEnMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   // Ajuste para febrero en años bisiestos
   ValidarAnio valAnio;
   if (valAnio.esBisiesto(anio)) {
      diasEnMes[1] = 29;
   }

   if (mes >= 1 && mes <= 12) {
      return dia <= diasEnMes[mes - 1];
   } else {
      return false;
   }
}