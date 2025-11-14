/***********************************************************************
 * Module:  main.cpp
 * Author:  USUARIO
 * Modified: martes, 29 de abril de 2025
 * Purpose: Programa principal para calcular series de potencias de 2
 ***********************************************************************/

 #include "IngresoDatos.h"
 #include "ValidarLimite.h"
 #include "SeriePotencia.h"
 #include <iostream>
 
 using namespace std;
 
 int main()
 {
     IngresoDatos ingreso;
     ValidarLimite validarLimite;
     SeriePotencia serie;
     
     int limite;
     
     cout << "PROGRAMA PARA CALCULAR SERIES DE POTENCIAS DE 2" << endl;
     cout << "================================================" << endl;
     cout << "La formula general es: Suma(2^i) desde i=0 hasta k = 2^(k+1) - 1" << endl;
     cout << "Tambien se puede interpretar como un numero binario de k+1 digitos donde todos son 1" << endl;
     cout << endl;
     cout << "*** Implementacion con metodos recursivos ***" << endl;
     cout << endl;
     
     // Pedimos el límite
     do {
         limite = ingreso.pedirNumero((char*)"Ingrese el limite superior (k) de la serie (0-30): ");
         if (!validarLimite.validarLimite(limite)) {
             cout << "Limite invalido. Debe ser un número entre 0 y 30." << endl;
             cout << "Nota: Limitado a 30 para evitar desbordamiento en la recursividad." << endl;
         }
     } while (!validarLimite.validarLimite(limite));
     
     // Establecemos el limite en la serie
     serie.setLimite(limite);
     
     // Mostramos la serie
     serie.imprimirSerie();
     
     return 0;
 }