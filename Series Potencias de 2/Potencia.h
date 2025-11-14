/***********************************************************************
 * Module:  Potencia.h
 * Author:  USUARIO
 * Modified: martes, 29 de abril de 2025 
 * Purpose: Declaration of the class Potencia
 ***********************************************************************/

 #if !defined(__Potencia_h)
 #define __Potencia_h
 
 class Potencia
 {
 public:
    int getValor(void);
    void setValor(int newValor);
    int getExponente(void);
    void setExponente(int newExponente);
    int calcularPotencia();
    long long calcularPotenciaRecursiva(int base, int exponente);
    Potencia();
    ~Potencia();
 
 protected:
 private:
    int valor;
    int exponente;
 };
 
 #endif