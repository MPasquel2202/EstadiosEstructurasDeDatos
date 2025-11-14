#include "IngresoDatos.h"
#include "ValidarAnio.h"
#include "ValidarMes.h"
#include "ValidarDia.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    IngresoDatos ingreso;
    ValidarAnio validarAnio;
    ValidarMes validarMes;
    ValidarDia validarDia;

    int dia, mes, anio;

    // Pedimos el año
    do {
        anio = ingreso.pedirNumero((char *)"Ingrese el anio: ");
        if (!validarAnio.validarAnio(anio)) {
            printf("\nAnio invalido. Debe ser mayor a 0.\n");
        }
    } while (!validarAnio.validarAnio(anio));

    // Pedimos el mes
    do {
        mes = ingreso.pedirNumero((char *)"Ingrese el mes: ");
        if (!validarMes.validarMes(mes)) {
            printf("\nMes invalido. Debe ser entre 1 y 12.\n");
        }
    } while (!validarMes.validarMes(mes));

    // Pedimos el dia
    do {
        dia = ingreso.pedirNumero((char *)"Ingrese el dia: ");
        if (!validarDia.validarDia(dia, mes, anio)) {
            printf("\nDia invalido para el mes/anio ingresado.\n");
        }
    } while (!validarDia.validarDia(dia, mes, anio));

    printf("\nFecha ingresada valida: %02d/%02d/%04d\n", dia, mes, anio);

    return 0;
}
