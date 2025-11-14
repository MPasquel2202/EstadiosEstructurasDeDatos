/***********************************************************************
 * Module:  main.cpp
 * Author:  Programador
 * Modified: martes, 29 de abril de 2025 12:00:00
 * Purpose: Programa principal para generar el Triángulo de Pascal
 ***********************************************************************/

 /***********************************************************************
 * Module:  main.cpp
 * Author:  Programador
 * Modified: martes, 29 de abril de 2025 12:00:00
 * Purpose: Programa principal para generar el Triángulo de Pascal
 ***********************************************************************/

 #include "IngresoDatos.h"
 #include "ValidarNumero.h"
 #include "TrianguloPascal.h"
 #include "MostrarTriangulo.h"
 #include <iostream>
 #include <stdio.h>
 #include <string.h>  // Para usar sprintf

 using namespace std;
 
 int main()
 {
     IngresoDatos ingreso;
     ValidarNumero validarNumero;
     MostrarTriangulo mostrarTriangulo;
     
     int numFilas;
     const int MIN_FILAS = 1;
     const int MAX_FILAS = 20; // Limitamos para evitar problemas de visualización
     char mensaje[50];  // Buffer para almacenar los mensajes
     
     // Pedimos el número de filas
     do {
         strcpy(mensaje, "Ingrese el numero de filas para el Triangulo de Pascal (1-20): ");
         numFilas = ingreso.pedirNumero(mensaje);
         if (!validarNumero.validarRango(numFilas, MIN_FILAS, MAX_FILAS)) {
             printf("\nNumero invalido. Debe estar entre %d y %d.\n", MIN_FILAS, MAX_FILAS);
         }
     } while (!validarNumero.validarRango(numFilas, MIN_FILAS, MAX_FILAS));
     
     // Creamos el Triángulo de Pascal
     TrianguloPascal triangulo(numFilas);
     
     // Mostramos el triángulo
     mostrarTriangulo.mostrarCentrado(triangulo);
     mostrarTriangulo.mostrarAlineadoIzquierda(triangulo);
     
     // Opciones para el usuario
     int opcion = 0;
     do {
         printf("\n\nOpciones:");
         printf("\n1. Ver valor en una posicion especifica");
         printf("\n2. Cambiar numero de filas");
         printf("\n3. Salir");
         strcpy(mensaje, "\nSeleccione una opcion: ");
         opcion = ingreso.pedirNumero(mensaje);
         
         switch (opcion) {
             case 1: {
                 int fila, columna;
                 do {
                     sprintf(mensaje, "Ingrese el numero de fila (0-%d): ", numFilas - 1);
                     fila = ingreso.pedirNumero(mensaje);
                 } while (!validarNumero.validarRango(fila, 0, numFilas - 1));
                 
                 int maxColumna = fila;
                 do {
                     sprintf(mensaje, "Ingrese el numero de columna (0-%d): ", maxColumna);
                     columna = ingreso.pedirNumero(mensaje);
                 } while (!validarNumero.validarRango(columna, 0, maxColumna));
                 
                 int valor = triangulo.getFila(fila).getElementos()[columna];
                 printf("\nEl valor en la posicion (%d,%d) es: %d", fila, columna, valor);
                 break;
             }
             case 2: {
                 do {
                     strcpy(mensaje, "Ingrese el nuevo numero de filas para el Triangulo de Pascal (1-20): ");
                     numFilas = ingreso.pedirNumero(mensaje);
                     if (!validarNumero.validarRango(numFilas, MIN_FILAS, MAX_FILAS)) {
                         printf("\nNumero invalido. Debe estar entre %d y %d.\n", MIN_FILAS, MAX_FILAS);
                     }
                 } while (!validarNumero.validarRango(numFilas, MIN_FILAS, MAX_FILAS));
                 
                 triangulo.setNumeroFilas(numFilas);
                 mostrarTriangulo.mostrarCentrado(triangulo);
                 break;
             }
             case 3:
                 printf("\nGracias por usar el programa del Triangulo de Pascal!\n");
                 break;
             default:
                 printf("\nOpcion invalida. Intente de nuevo.\n");
         }
     } while (opcion != 3);
     
     return 0;
 }