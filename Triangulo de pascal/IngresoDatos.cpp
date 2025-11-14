/***********************************************************************
 * Module:  IngresoDatos.cpp
 * Author:  Programador
 * Modified: martes, 29 de abril de 2025 12:00:00
 * Purpose: Implementation of the class IngresoDatos
 ***********************************************************************/

 #include "IngresoDatos.h"
 #include <stdio.h>
 #include <conio.h>
 #include <stdlib.h>
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       IngresoDatos::getValor()
 // Purpose:    Implementation of IngresoDatos::getValor()
 // Return:     int
 ////////////////////////////////////////////////////////////////////////
 
 int IngresoDatos::getValor(void)
 {
    return valor;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       IngresoDatos::setValor(int newValor)
 // Purpose:    Implementation of IngresoDatos::setValor()
 // Parameters:
 // - newValor
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void IngresoDatos::setValor(int newValor)
 {
    valor = newValor;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       IngresoDatos::pedirNumero(char msj[50])
 // Purpose:    Implementation of IngresoDatos::pedirNumero()
 // Parameters:
 // - msj
 // Return:     int
 ////////////////////////////////////////////////////////////////////////
 
 int IngresoDatos::pedirNumero(char msj[50])
 {
    char c;
    int valor, i = 0;
    char dato[10];
 
    printf("\n%s", msj);
    while ((c = getch()) != 13) { // 13 = tecla Enter
       if (c >= '0' && c <= '9') {
          dato[i++] = c;
          printf("%c", c);
       }
    }
    dato[i] = '\0';
    valor = atoi(dato);
    this->valor = valor;
    return valor;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       IngresoDatos::IngresoDatos()
 // Purpose:    Implementation of IngresoDatos::IngresoDatos()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 IngresoDatos::IngresoDatos()
 {
    valor = 0;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       IngresoDatos::~IngresoDatos()
 // Purpose:    Implementation of IngresoDatos::~IngresoDatos()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 IngresoDatos::~IngresoDatos()
 {
    // No hay recursos que liberar
 }
 