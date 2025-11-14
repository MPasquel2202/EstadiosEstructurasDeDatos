/***********************************************************************
 * Module:  Hanoi.h
 * Author:  Claude
 * Modified: martes, 29 de abril de 2025
 * Purpose: Declaration of the class Hanoi
 ***********************************************************************/

 #if !defined(__Hanoi_Hanoi_h)
 #define __Hanoi_Hanoi_h
 
 #include "Torre.h"
 #include <vector>
 
 class Hanoi
 {
 public:
    void inicializar(int numDiscos);
    void resolver(int numDiscos, Torre& origen, Torre& auxiliar, Torre& destino);
    void moverDisco(Torre& origen, Torre& destino);
    void mostrarEstado();
    int getNumDiscos(void);
    void setNumDiscos(int newNumDiscos);
    int getMovimientos(void);
    Torre& getTorreOrigen();
    Torre& getTorreAuxiliar();
    Torre& getTorreDestino();
    Hanoi();
    ~Hanoi();
 
 protected:
 private:
    int numDiscos;
    int movimientos;
    Torre torreOrigen;
    Torre torreAuxiliar;
    Torre torreDestino;
 };
 
 #endif