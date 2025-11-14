/***********************************************************************
 * Module:  Torre.cpp
 * Author:  Claude
 * Modified: martes, 29 de abril de 2025
 * Purpose: Implementation of the class Torre
 ***********************************************************************/

 #include "Torre.h"
 #include <iostream>
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Torre::getDiscos()
 // Purpose:    Implementation of Torre::getDiscos()
 // Return:     std::vector<int>
 ////////////////////////////////////////////////////////////////////////
 
 std::vector<int> Torre::getDiscos(void)
 {
    return discos;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Torre::setDiscos(std::vector<int> newDiscos)
 // Purpose:    Implementation of Torre::setDiscos()
 // Parameters:
 // - newDiscos
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void Torre::setDiscos(std::vector<int> newDiscos)
 {
    discos = newDiscos;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Torre::getNombre()
 // Purpose:    Implementation of Torre::getNombre()
 // Return:     std::string
 ////////////////////////////////////////////////////////////////////////
 
 std::string Torre::getNombre(void)
 {
    return nombre;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Torre::setNombre(std::string newNombre)
 // Purpose:    Implementation of Torre::setNombre()
 // Parameters:
 // - newNombre
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void Torre::setNombre(std::string newNombre)
 {
    nombre = newNombre;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Torre::agregarDisco(int tamano)
 // Purpose:    Implementation of Torre::agregarDisco()
 // Parameters:
 // - tamano
 // Return:     bool
 ////////////////////////////////////////////////////////////////////////
 
 bool Torre::agregarDisco(int tamano)
 {
    // Verificar si podemos colocar el disco (debe ser menor que el que está encima)
    if (!discos.empty() && discos.back() < tamano) {
       return false;
    }
    
    discos.push_back(tamano);
    return true;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Torre::removerDisco()
 // Purpose:    Implementation of Torre::removerDisco()
 // Return:     int
 ////////////////////////////////////////////////////////////////////////
 
 int Torre::removerDisco(void)
 {
    if (discos.empty()) {
       return -1; // Indicar que no hay discos
    }
    
    int disco = discos.back();
    discos.pop_back();
    return disco;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Torre::mostrar()
 // Purpose:    Implementation of Torre::mostrar()
 // Return:     void
 ////////////////////////////////////////////////////////////////////////
 
 void Torre::mostrar(void)
 {
    std::cout << "Torre " << nombre << ": ";
    
    if (discos.empty()) {
       std::cout << "vacia";
    } else {
       for (int disco : discos) {
          std::cout << disco << " ";
       }
    }
    
    std::cout << std::endl;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Torre::Torre(std::string nombre)
 // Purpose:    Implementation of Torre::Torre()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 Torre::Torre(std::string nombre)
 {
    this->nombre = nombre;
 }
 
 ////////////////////////////////////////////////////////////////////////
 // Name:       Torre::~Torre()
 // Purpose:    Implementation of Torre::~Torre()
 // Return:     
 ////////////////////////////////////////////////////////////////////////
 
 Torre::~Torre()
 {
    // No hay recursos que liberar
 }