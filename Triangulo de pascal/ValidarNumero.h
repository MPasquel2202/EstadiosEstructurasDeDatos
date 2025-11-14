/***********************************************************************
 * Module:  ValidarNumero.h
 * Author:  Programador
 * Modified: martes, 29 de abril de 2025 12:00:00
 * Purpose: Declaration of the class ValidarNumero
 ***********************************************************************/

 #if !defined(__Pascal_ValidarNumero_h)
 #define __Pascal_ValidarNumero_h
 
 class ValidarNumero
 {
 public:
    bool validarNumero(int numero);
    bool validarRango(int numero, int minimo, int maximo);
    ValidarNumero();
    ~ValidarNumero();
 
 protected:
 private:
 
 };
 
 #endif