/***********************************************************************
 * Module:  IngresoDatos.h
 * Author:  Programador
 * Modified: martes, 29 de abril de 2025 12:00:00
 * Purpose: Declaration of the class IngresoDatos
 ***********************************************************************/

 #if !defined(__Pascal_IngresoDatos_h)
 #define __Pascal_IngresoDatos_h
 
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