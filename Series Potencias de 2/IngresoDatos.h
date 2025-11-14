/***********************************************************************
 * Module:  IngresoDatos.h
 * Author:  USUARIO
 * Modified: martes, 29 de abril de 2025
 * Purpose: Declaration of the class IngresoDatos
 ***********************************************************************/

 #if !defined(__IngresoDatos_h)
 #define __IngresoDatos_h
 
 #include <string> // Agregamos la inclusión para el tipo string
 
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