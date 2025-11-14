/***********************************************************************
 * Module:  Anio.h
 * Author:  USUARIO
 * Modified: domingo, 27 de abril de 2025 10:41:53
 * Purpose: Declaration of the class Anio
 ***********************************************************************/

#if !defined(__Fecha2_Anio_h)
#define __Fecha2_Anio_h

class Anio
{
public:
   bool getAnioBisiesto(void);
   void setAnioBisiesto(bool newAnioBisiesto);
   int getAnio(void);
   void setAnio(int newAnio);
   Anio();
   ~Anio();

protected:
private:
   bool anioBisiesto;
   int anio;


};

#endif