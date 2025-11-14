/***********************************************************************
 * Module:  SeriePotencia.cpp
 * Author:  USUARIO
 * Modified: martes, 29 de abril de 2025
 * Purpose: Implementation of the class SeriePotencia
 ***********************************************************************/

 #include "SeriePotencia.h"
 #include <iostream>
 #include <cmath>
 #include <bitset>
 #include <string>
 
 using namespace std;
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       SeriePotencia::getLimite()
 // Purpose:    Implementation of SeriePotencia::getLimite()
 // Return:     int
 ////////////////////////////////////////////////////////////////////////
 
 int SeriePotencia::getLimite(void)
 {
    return limite;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       SeriePotencia::setLimite(int newLimite)
 // Purpose:    Implementation of SeriePotencia::setLimite()
 // Parameters:
 // - newLimite
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void SeriePotencia::setLimite(int newLimite)
 {
    limite = newLimite;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       SeriePotencia::calcularSumatoria()
 // Purpose:    Implementation of SeriePotencia::calcularSumatoria()
 // Return:     long long
 ////////////////////////////////////////////////////////////////////////
 
 long long SeriePotencia::calcularSumatoria()
 {
    // Llamamos al método recursivo con el límite actual
    return calcularSumatoriaRecursiva(limite);
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       SeriePotencia::calcularSumatoriaRecursiva(int limite)
 // Purpose:    Implementation of SeriePotencia::calcularSumatoriaRecursiva()
 // Parameters:
 // - limite
 // Return:     long long
 ////////////////////////////////////////////////////////////////////////
 
 long long SeriePotencia::calcularSumatoriaRecursiva(int limite)
 {
    // Caso base
    if (limite < 0)
       return 0;
    
    // Caso recursivo: 2^limite + sumatoria hasta limite-1
    potencia.setExponente(limite);
    return potencia.calcularPotenciaRecursiva(2, limite) + calcularSumatoriaRecursiva(limite - 1);
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       SeriePotencia::calcularSumatoriaFormula()
 // Purpose:    Implementation of SeriePotencia::calcularSumatoriaFormula()
 // Return:     long long
 ////////////////////////////////////////////////////////////////////////
 
 long long SeriePotencia::calcularSumatoriaFormula()
 {
    // Usando la formula: suma de 2^i desde i=0 hasta k = 2^(k+1) - 1
    // Usamos el metodo recursivo para calcular la potencia
    return potencia.calcularPotenciaRecursiva(2, limite + 1) - 1;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       SeriePotencia::imprimirSerie()
 // Purpose:    Implementation of SeriePotencia::imprimirSerie()
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void SeriePotencia::imprimirSerie()
 {
    cout << "Serie de potencias de 2 desde 0 hasta " << limite << ":" << endl;
    cout << "i\t2^i\tBinario" << endl;
    cout << "------------------------" << endl;
    
    for (int i = 0; i <= limite; i++) {
       // Usamos nuestro metodo recursivo para calcular la potencia
       potencia.setExponente(i);
       long long valorPotencia = potencia.calcularPotencia();
       
       // Convertir a representacion binaria
       string binario = bitset<32>(valorPotencia).to_string();
       // Eliminar ceros a la izquierda
       binario = binario.substr(binario.find('1'));
       
       cout << i << "\t" << valorPotencia << "\t" << binario << endl;
    }
    
    long long sumatoria = calcularSumatoria();
    long long sumatoriaFormula = calcularSumatoriaFormula();
    
    cout << "------------------------" << endl;
    cout << "Sumatoria calculada recursivamente: " << sumatoria << endl;
    cout << "Sumatoria por formula 2^(k+1)-1: " << sumatoriaFormula << endl;
    
    // Mostrar la representacion binaria (todos 1s)
    string binarioTotal = "";
    for (int i = 0; i <= limite; i++) {
       binarioTotal += "1";
    }
    
    cout << "Representacion binaria de la sumatoria: " << binarioTotal << " (base 2) = " << sumatoria << " (base 10)" << endl;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       SeriePotencia::SeriePotencia()
 // Purpose:    Implementation of SeriePotencia::SeriePotencia()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 SeriePotencia::SeriePotencia()
 {
    limite = 0;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       SeriePotencia::~SeriePotencia()
 // Purpose:    Implementation of SeriePotencia::~SeriePotencia()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 SeriePotencia::~SeriePotencia()
 {
    // TODO : implement
 }