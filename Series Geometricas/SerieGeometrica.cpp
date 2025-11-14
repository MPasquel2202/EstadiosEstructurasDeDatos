/***********************************************************************
 * Module:  SerieGeometrica.cpp
 * Author:  Usuario
 * Modified: martes, 29 de abril de 2025
 * Purpose: Implementation of the class SerieGeometrica
 ***********************************************************************/

 #include "SerieGeometrica.h"
 #include <cmath>   // Para fabs, pow, isnan, isinf
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       SerieGeometrica::getA()
 // Purpose:    Implementation of SerieGeometrica::getA()
 // Return:     double
 ////////////////////////////////////////////////////////////////////////
 
 double SerieGeometrica::getA(void)
 {
     return a;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       SerieGeometrica::setA(double newA)
 // Purpose:    Implementation of SerieGeometrica::setA()
 // Parameters:
 // - newA
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void SerieGeometrica::setA(double newA)
 {
     a = newA;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       SerieGeometrica::getR()
 // Purpose:    Implementation of SerieGeometrica::getR()
 // Return:     double
 ////////////////////////////////////////////////////////////////////////
 
 double SerieGeometrica::getR(void)
 {
     return r;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       SerieGeometrica::setR(double newR)
 // Purpose:    Implementation of SerieGeometrica::setR()
 // Parameters:
 // - newR
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void SerieGeometrica::setR(double newR)
 {
     r = newR;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       SerieGeometrica::getN()
 // Purpose:    Implementation of SerieGeometrica::getN()
 // Return:     int
 ////////////////////////////////////////////////////////////////////////
 
 int SerieGeometrica::getN(void)
 {
     return n;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       SerieGeometrica::setN(int newN)
 // Purpose:    Implementation of SerieGeometrica::setN()
 // Parameters:
 // - newN
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void SerieGeometrica::setN(int newN)
 {
     n = newN;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       SerieGeometrica::calcularTermino(int i)
 // Purpose:    Implementation of SerieGeometrica::calcularTermino()
 // Parameters:
 // - i: índice del término
 // Return:     double
 ////////////////////////////////////////////////////////////////////////
 
 double SerieGeometrica::calcularTermino(int i)
 {
     // a * r^i
     return a * pow(r, i);
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       SerieGeometrica::calcularSerie(int i)
 // Purpose:    Implementation of SerieGeometrica::calcularSerie()
 // Parameters:
 // - i: número de términos a calcular
 // Return:     double
 ////////////////////////////////////////////////////////////////////////
 
 double SerieGeometrica::calcularSerie(int i)
 {
     // Caso base
     if (i == 0) {
         return calcularTermino(0);
     }
     
     // Caso recursivo
     return calcularTermino(i) + calcularSerie(i - 1);
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       SerieGeometrica::SerieGeometrica()
 // Purpose:    Implementation of SerieGeometrica::SerieGeometrica()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 SerieGeometrica::SerieGeometrica()
 {
     a = 1.0;
     r = 0.5;
     n = 5;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       SerieGeometrica::~SerieGeometrica()
 // Purpose:    Implementation of SerieGeometrica::~SerieGeometrica()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 SerieGeometrica::~SerieGeometrica()
 {
     // TODO : implement
 } 