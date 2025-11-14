/***********************************************************************
 * Module:  Hanoi.cpp
 * Author:  Claude
 * Modified: martes, 29 de abril de 2025
 * Purpose: Implementation of the class Hanoi
 ***********************************************************************/

 #include "Hanoi.h"
 #include <iostream>
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Hanoi::inicializar(int numDiscos)
 // Purpose:    Implementation of Hanoi::inicializar()
 // Parameters:
 // - numDiscos
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void Hanoi::inicializar(int numDiscos)
 {
    this->numDiscos = numDiscos;
    this->movimientos = 0;
    
    // Inicializar torres (limpiar discos existentes)
    torreOrigen.setDiscos(std::vector<int>());
    torreAuxiliar.setDiscos(std::vector<int>());
    torreDestino.setDiscos(std::vector<int>());
    
    // Colocar discos en la torre origen
    for (int i = numDiscos; i >= 1; i--) {
       torreOrigen.agregarDisco(i);
    }
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Hanoi::resolver(int numDiscos, Torre& origen, Torre& auxiliar, Torre& destino)
 // Purpose:    Implementation of Hanoi::resolver()
 // Parameters:
 // - numDiscos
 // - origen
 // - auxiliar
 // - destino
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void Hanoi::resolver(int numDiscos, Torre& origen, Torre& auxiliar, Torre& destino)
 {
    if (numDiscos == 1) {
       moverDisco(origen, destino);
       mostrarEstado();
    } else {
       resolver(numDiscos - 1, origen, destino, auxiliar);
       moverDisco(origen, destino);
       mostrarEstado();
       resolver(numDiscos - 1, auxiliar, origen, destino);
    }
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Hanoi::moverDisco(Torre& origen, Torre& destino)
 // Purpose:    Implementation of Hanoi::moverDisco()
 // Parameters:
 // - origen
 // - destino
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void Hanoi::moverDisco(Torre& origen, Torre& destino)
 {
    int disco = origen.removerDisco();
    if (disco != -1) {
       destino.agregarDisco(disco);
       movimientos++;
       std::cout << "Movimiento " << movimientos << ": ";
       std::cout << "Mover disco " << disco << " de Torre " << origen.getNombre() << " a Torre " << destino.getNombre() << std::endl;
    }
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Hanoi::mostrarEstado()
 // Purpose:    Implementation of Hanoi::mostrarEstado()
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void Hanoi::mostrarEstado()
 {
    std::cout << "\nEstado actual:" << std::endl;
    torreOrigen.mostrar();
    torreAuxiliar.mostrar();
    torreDestino.mostrar();
    std::cout << std::endl;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Hanoi::getNumDiscos()
 // Purpose:    Implementation of Hanoi::getNumDiscos()
 // Return:     int
 ////////////////////////////////////////////////////////////////////////
 
 int Hanoi::getNumDiscos(void)
 {
    return numDiscos;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Hanoi::setNumDiscos(int newNumDiscos)
 // Purpose:    Implementation of Hanoi::setNumDiscos()
 // Parameters:
 // - newNumDiscos
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void Hanoi::setNumDiscos(int newNumDiscos)
 {
    numDiscos = newNumDiscos;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Hanoi::getMovimientos()
 // Purpose:    Implementation of Hanoi::getMovimientos()
 // Return:     int
 ////////////////////////////////////////////////////////////////////////
 
 int Hanoi::getMovimientos(void)
 {
    return movimientos;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Hanoi::getTorreOrigen()
 // Purpose:    Implementation of Hanoi::getTorreOrigen()
 // Return:     Torre&
 ////////////////////////////////////////////////////////////////////////
 
 Torre& Hanoi::getTorreOrigen()
 {
    return torreOrigen;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Hanoi::getTorreAuxiliar()
 // Purpose:    Implementation of Hanoi::getTorreAuxiliar()
 // Return:     Torre&
 ////////////////////////////////////////////////////////////////////////
 
 Torre& Hanoi::getTorreAuxiliar()
 {
    return torreAuxiliar;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Hanoi::getTorreDestino()
 // Purpose:    Implementation of Hanoi::getTorreDestino()
 // Return:     Torre&
 ////////////////////////////////////////////////////////////////////////
 
 Torre& Hanoi::getTorreDestino()
 {
    return torreDestino;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Hanoi::Hanoi()
 // Purpose:    Implementation of Hanoi::Hanoi()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 Hanoi::Hanoi() : torreOrigen("A"), torreAuxiliar("B"), torreDestino("C")
 {
    numDiscos = 0;
    movimientos = 0;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Hanoi::~Hanoi()
 // Purpose:    Implementation of Hanoi::~Hanoi()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 Hanoi::~Hanoi()
 {
    // No hay recursos que liberar
 }