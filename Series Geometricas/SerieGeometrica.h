/***********************************************************************
 * Module:  SerieGeometrica.h
 * Author:  Usuario
 * Modified: martes, 29 de abril de 2025 
 * Purpose: Declaration of the class SerieGeometrica
 ***********************************************************************/

 #if !defined(__SerieGeometrica_h)
 #define __SerieGeometrica_h
 
 class SerieGeometrica 
 {
 public:
     double getA(void);
     void setA(double newA);
     double getR(void);
     void setR(double newR);
     int getN(void);
     void setN(int newN);
     double calcularTermino(int i);
     double calcularSerie(int i);
     SerieGeometrica();
     ~SerieGeometrica();
 
 protected:
 private:
     double a; // Primer término
     double r; // Razón
     int n;    // Número de términos
 };
 
 #endif