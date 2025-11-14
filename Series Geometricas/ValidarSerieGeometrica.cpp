/***********************************************************************
 * Module:  ValidarSerieGeometrica.cpp
 * Author:  Usuario
 * Modified: martes, 29 de abril de 2025
 * Purpose: Implementation of the class ValidarSerieGeometrica
 ***********************************************************************/

 #include "ValidarSerieGeometrica.h"
 #include <cmath>   // Para fabs, pow, isnan, isinf
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       ValidarSerieGeometrica::validarA(double a)
 // Purpose:    Implementation of ValidarSerieGeometrica::validarA()
 // Parameters:
 // - a
 // Return:     bool
 ////////////////////////////////////////////////////////////////////////
 
 bool ValidarSerieGeometrica::validarA(double a)
 {
     // Evitar valores extremos o no válidos
     return !std::isnan(a) && !std::isinf(a) && fabs(a) < 1e10;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       ValidarSerieGeometrica::validarR(double r)
 // Purpose:    Implementation of ValidarSerieGeometrica::validarR()
 // Parameters:
 // - r
 // Return:     bool
 ////////////////////////////////////////////////////////////////////////
 
 bool ValidarSerieGeometrica::validarR(double r)
 {
     // Razón válida: debe ser un número real y no 0
     // Para convergencia |r| < 1, pero podemos permitir otros valores
     return !std::isnan(r) && !std::isinf(r) && fabs(r) < 10 && r != 0;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       ValidarSerieGeometrica::validarN(int n)
 // Purpose:    Implementation of ValidarSerieGeometrica::validarN()
 // Parameters:
 // - n
 // Return:     bool
 ////////////////////////////////////////////////////////////////////////
 
 bool ValidarSerieGeometrica::validarN(int n)
 {
     // Número de términos debe ser positivo y no excesivo
     return n > 0 && n <= 100;
 }