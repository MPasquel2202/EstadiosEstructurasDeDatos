/***********************************************************************
 * Module:  Fecha.h
 * Author:  USUARIO
 * Modified: domingo, 27 de abril de 2025 10:41:53
 * Purpose: Declaration of the class Fecha
 ***********************************************************************/

#if !defined(__Fecha2_Fecha_h)
#define __Fecha2_Fecha_h

#include "Anio.h"

class Fecha
{
public:
   Anio getAnio(void);
   void setAnio(Anio newAnio);
   int getMes(void);
   void setMes(int newMes);
   int getDia(void);
   void setDia(int newDia);
   Fecha();
   ~Fecha();

protected:
private:
   Anio anio;
   int mes;
   int dia;


};

#endif