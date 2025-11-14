/***********************************************************************
 * Module:  IngresoSerieGeometrica.cpp
 * Author:  Usuario
 * Modified: martes, 29 de abril de 2025
 * Purpose: Implementation of the class IngresoSerieGeometrica
 ***********************************************************************/

 #include "IngresoSerieGeometrica.h"
 #include <stdio.h>
 #include <conio.h>
 #include <stdlib.h>
 #include <iostream>
 #include <string>
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       IngresoSerieGeometrica::pedirNumeroDouble(char msj[40])
 // Purpose:    Implementation of IngresoSerieGeometrica::pedirNumeroDouble()
 // Parameters:
 // - msj
 // Return:     double
 ////////////////////////////////////////////////////////////////////////
 
 double IngresoSerieGeometrica::pedirNumeroDouble(char msj[40])
 {
     char c;
     double valor;
     int i = 0;
     bool punto = false;
     char dato[20];
 
     printf("\n%s", msj);
     while ((c = getch()) != 13) { // 13 = tecla Enter
         if ((c >= '0' && c <= '9') || (c == '.' && !punto) || (c == '-' && i == 0)) {
             if (c == '.') punto = true;
             dato[i++] = c;
             printf("%c", c);
         }
     }
     dato[i] = '\0';
     valor = atof(dato);
     return valor;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       IngresoSerieGeometrica::pedirNumeroInt(char msj[40])
 // Purpose:    Implementation of IngresoSerieGeometrica::pedirNumeroInt()
 // Parameters:
 // - msj
 // Return:     int
 ////////////////////////////////////////////////////////////////////////
 
 int IngresoSerieGeometrica::pedirNumeroInt(char msj[40])
 {
     char c;
     int valor, i = 0;
     char dato[10];
 
     printf("\n%s", msj);
     while ((c = getch()) != 13) { // 13 = tecla Enter
         if ((c >= '0' && c <= '9') || (c == '-' && i == 0)) {
             dato[i++] = c;
             printf("%c", c);
         }
     }
     dato[i] = '\0';
     valor = atoi(dato);
     return valor;
 }