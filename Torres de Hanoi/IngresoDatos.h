/***********************************************************************
 * Module:  IngresoDatos.h
 * Author:  Claude
 * Modified: martes, 29 de abril de 2025
 * Purpose: Declaration of the class IngresoDatos
 ***********************************************************************/

 #if !defined(__Hanoi_IngresoDatos_h)
 #define __Hanoi_IngresoDatos_h
 
 class IngresoDatos
 {
 public:
     int getValor(void);
     void setValor(int newValor);
     int pedirNumero(char msj[50]);
     IngresoDatos();
     ~IngresoDatos();
 
 protected:
 private:
     int valor;
 };
 
 #endif