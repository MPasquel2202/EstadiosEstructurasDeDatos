/***********************************************************************
 * Module:  SeriePotencia.h
 * Author:  USUARIO
 * Modified: martes, 29 de abril de 2025
 * Purpose: Declaration of the class SeriePotencia
 ***********************************************************************/

 #if !defined(__SeriePotencia_h)
 #define __SeriePotencia_h
 
 #include "Potencia.h"
 
 class SeriePotencia
 {
 public:
    int getLimite(void);
    void setLimite(int newLimite);
    long long calcularSumatoria();
    long long calcularSumatoriaRecursiva(int limite);
    long long calcularSumatoriaFormula();
    void imprimirSerie();
    SeriePotencia();
    ~SeriePotencia();
 
 protected:
 private:
    int limite;
    Potencia potencia;
 };
 
 #endif