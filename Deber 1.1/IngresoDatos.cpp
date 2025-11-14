/***********************************************************************
 * Module:  IngresoDatos.cpp
 * Author:  USUARIO
 * Modified: domingo, 27 de abril de 2025 11:56:42
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
// Name:       IngresoDatos::pedirNumero(char[20] msj)
// Purpose:    Implementation of IngresoDatos::pedirNumero()
// Parameters:
// - msj
// Return:     int
////////////////////////////////////////////////////////////////////////

int IngresoDatos::pedirNumero(char msj[20])
{
   // TODO : implement
   char c;
    int valor, i = 0;
    char dato[10];

    printf("\n!!!%s", msj);
    while ((c = getch()) != 13) { // 13 = tecla Enter
        if (c >= '0' && c <= '9') {
            dato[i++] = c;
            printf("%c", c);
        }
    }
    dato[i] = '\0';
    valor = atoi(dato);
    return valor;
}

////////////////////////////////////////////////////////////////////////
// Name:       IngresoDatos::IngresoDatos()
// Purpose:    Implementation of IngresoDatos::IngresoDatos()
// Return:     
////////////////////////////////////////////////////////////////////////

IngresoDatos::IngresoDatos()
{
}

////////////////////////////////////////////////////////////////////////
// Name:       IngresoDatos::~IngresoDatos()
// Purpose:    Implementation of IngresoDatos::~IngresoDatos()
// Return:     
////////////////////////////////////////////////////////////////////////

IngresoDatos::~IngresoDatos()
{
   // TODO : implement
}