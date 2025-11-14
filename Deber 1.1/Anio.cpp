/***********************************************************************
 * Module:  Anio.cpp
 * Author:  USUARIO
 * Modified: domingo, 27 de abril de 2025 10:41:53
 * Purpose: Implementation of the class Anio
 ***********************************************************************/

#include "Anio.h"

////////////////////////////////////////////////////////////////////////
// Name:       Anio::getAnioBisiesto()
// Purpose:    Implementation of Anio::getAnioBisiesto()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Anio::getAnioBisiesto(void)
{
   return anioBisiesto;
}

////////////////////////////////////////////////////////////////////////
// Name:       Anio::setAnioBisiesto(bool newAnioBisiesto)
// Purpose:    Implementation of Anio::setAnioBisiesto()
// Parameters:
// - newAnioBisiesto
// Return:     void
////////////////////////////////////////////////////////////////////////

void Anio::setAnioBisiesto(bool newAnioBisiesto)
{
   anioBisiesto = newAnioBisiesto;
}

////////////////////////////////////////////////////////////////////////
// Name:       Anio::getAnio()
// Purpose:    Implementation of Anio::getAnio()
// Return:     int
////////////////////////////////////////////////////////////////////////

int Anio::getAnio(void)
{
   return anio;
}

////////////////////////////////////////////////////////////////////////
// Name:       Anio::setAnio(int newAnio)
// Purpose:    Implementation of Anio::setAnio()
// Parameters:
// - newAnio
// Return:     void
////////////////////////////////////////////////////////////////////////

void Anio::setAnio(int newAnio)
{
   anio = newAnio;
}

////////////////////////////////////////////////////////////////////////
// Name:       Anio::Anio()
// Purpose:    Implementation of Anio::Anio()
// Return:     
////////////////////////////////////////////////////////////////////////

Anio::Anio()
{
}

////////////////////////////////////////////////////////////////////////
// Name:       Anio::~Anio()
// Purpose:    Implementation of Anio::~Anio()
// Return:     
////////////////////////////////////////////////////////////////////////

Anio::~Anio()
{
   // TODO : implement
}