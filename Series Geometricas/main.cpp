/***********************************************************************
 * Module:  main.cpp
 * Author:  Usuario
 * Modified: martes, 29 de abril de 2025
 * Purpose: Main program for Serie Geometrica
 ***********************************************************************/

 #include "SerieGeometrica.h"
 #include "ValidarSerieGeometrica.h"
 #include "IngresoSerieGeometrica.h"
 #include <iostream>
 #include <iomanip>
 #include <cmath>    // Para fabs, pow
 
 using namespace std;
 
 int main()
 {
     SerieGeometrica serie;
     ValidarSerieGeometrica validar;
     IngresoSerieGeometrica ingreso;
     
     double a, r;
     int n;
     
     // Pedimos el primer término (a)
     do {
         a = ingreso.pedirNumeroDouble((char *)"Ingrese el primer termino (a): ");
         if (!validar.validarA(a)) {
             printf("\nValor invalido. Por favor ingrese un numero real valido.\n");
         }
     } while (!validar.validarA(a));
     serie.setA(a);
     
     // Pedimos la razón (r)
     do {
         r = ingreso.pedirNumeroDouble((char *)"Ingrese la razon (r): ");
         if (!validar.validarR(r)) {
             printf("\nValor invalido. La razon debe ser diferente de cero.\n");
         }
     } while (!validar.validarR(r));
     serie.setR(r);
     
     // Pedimos la cantidad de términos (n)
     do {
         n = ingreso.pedirNumeroInt((char *)"Ingrese la cantidad de terminos (n): ");
         if (!validar.validarN(n)) {
             printf("\nValor invalido. La cantidad debe ser un entero positivo (1-100).\n");
         }
     } while (!validar.validarN(n));
     serie.setN(n);
     
     // Calculamos y mostramos los términos de la serie
     printf("\nTérminos de la serie geométrica:\n");
     for (int i = 0; i < n; i++) {
         printf("a[%d] = %.4f\n", i, serie.calcularTermino(i));
     }
     
     // Calculamos y mostramos la suma usando recursividad
     double suma = serie.calcularSerie(n - 1);
     printf("\nLa suma de los %d terminos es: %.4f\n", n, suma);
     
     // Verificamos con la formula directa cuando |r| < 1
     if (fabs(r) < 1) {
         double sumaDirecta = a * (1 - pow(r, n)) / (1 - r);
         printf("\nVerificacion con formula directa: %.4f\n", sumaDirecta);
     }
     
     return 0;
    }