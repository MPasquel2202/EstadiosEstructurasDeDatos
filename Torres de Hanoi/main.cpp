/***********************************************************************
 * Module:  main.cpp
 * Author:  Claude
 * Modified: martes, 29 de abril de 2025
 * Purpose: Implementación del programa principal para las Torres de Hanoi
 ***********************************************************************/

 #include "IngresoDatos.h"
 #include "ValidarDiscos.h"
 #include "Hanoi.h"
 #include <iostream>
 #include <stdio.h>
 
 using namespace std;
 
 int main()
 {
     IngresoDatos ingreso;
     ValidarDiscos validar;
     Hanoi hanoi;
     
     int numDiscos;
     
     cout << "=====================================" << endl;
     cout << "       TORRES DE HANOI" << endl;
     cout << "=====================================" << endl;
     cout << "El objetivo es mover todos los discos de la Torre A a la Torre C" << endl;
     cout << "siguiendo las reglas:" << endl;
     cout << "1. Solo se puede mover un disco a la vez" << endl;
     cout << "2. Un disco solo puede colocarse sobre otro de mayor tamano" << endl;
     cout << "=====================================" << endl;
     
     // Pedimos el número de discos
     do {
         numDiscos = ingreso.pedirNumero((char *)"Ingrese el numero de discos (1-10): ");
         if (!validar.validarNumDiscos(numDiscos)) {
             printf("\nNumero de discos invalido. Debe estar entre 1 y 10.\n");
         }
     } while (!validar.validarNumDiscos(numDiscos));
     
     // Inicializamos el juego
     hanoi.inicializar(numDiscos);
     
     // Mostramos el estado inicial
     cout << "\nEstado inicial:" << endl;
     hanoi.mostrarEstado();
     
     // Resolvemos el problema
     cout << "\nResolviendo Torres de Hanoi con " << numDiscos << " discos...\n" << endl;
     hanoi.resolver(numDiscos, hanoi.getTorreOrigen(), hanoi.getTorreAuxiliar(), hanoi.getTorreDestino());
     
     // Mostramos el resultado final
     cout << "\n=====================================" << endl;
     cout << "Problema resuelto en " << hanoi.getMovimientos() << " movimientos!" << endl;
     cout << "=====================================" << endl;
     
     return 0;
 }