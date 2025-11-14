/***********************************************************************
 * Module:  IngresoDatos.cpp
 * Author:  USUARIO
 * Modified: martes, 29 de abril de 2025
 * Purpose: Implementation of the class IngresoDatos
 ***********************************************************************/

 #include "IngresoDatos.h"
 #include <iostream>
 #include <limits>
 #include <string>
 
 using namespace std;
 
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
    int valor;
    bool entradaValida = false;
    string entrada;
    
    do {
       cout << msj;
       cin >> entrada;
       
       // Validar que la entrada contenga solo dígitos
       bool esEntero = true;
       for(size_t i = 0; i < entrada.length(); i++) {
          // Permitir el signo negativo solo al principio
          if (i == 0 && entrada[i] == '-') {
             continue;
          }
          
          if (!isdigit(entrada[i])) {
             esEntero = false;
             break;
          }
       }
       
       if (esEntero && !entrada.empty()) {
          try {
             valor = stoi(entrada);
             entradaValida = true;
          } catch (const std::out_of_range& e) {
             cout << "Error: El numero es demasiado grande o pequeño para un entero." << endl;
             entradaValida = false;
          } catch (const std::invalid_argument& e) {
             cout << "Entrada invalida. Por favor ingrese un numero entero." << endl;
             entradaValida = false;
          }
       } else {
          cout << "Entrada invalida. Por favor ingrese solo numeros enteros." << endl;
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
       }
    } while (!entradaValida);
    
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
    // TODO : implement
 }