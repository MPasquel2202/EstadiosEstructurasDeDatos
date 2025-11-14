#include "IngresoDatos.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>



int IngresoDatos::getValor(void)
{
   return valor;
}

void IngresoDatos::setValor(int newValor)
{
   valor = newValor;
}

int IngresoDatos::pedirNumero(const char* msj)
{
    char c;
    int valor, i = 0;
    char dato[10];
    bool negativo = false;

    printf("\n%s", msj);
    while ((c = getch()) != 13) { // 13 = tecla Enter
        // Permitir el signo negativo solo al inicio
        if (c == '-' && i == 0) {
            negativo = true;
            dato[i++] = c;
            printf("%c", c);
        }
        else if (c >= '0' && c <= '9') {
            dato[i++] = c;
            printf("%c", c);
        }
    }
    dato[i] = '\0';
    valor = atoi(dato);
    return valor;
}


IngresoDatos::IngresoDatos()
{
    valor = 0;
}

IngresoDatos::~IngresoDatos()
{
   // TODO : implement
}