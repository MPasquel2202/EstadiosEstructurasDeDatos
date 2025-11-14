/***********************************************************************
 * Module:  TrianguloPascal.h
 * Author:  Programador
 * Modified: martes, 29 de abril de 2025 12:00:00
 * Purpose: Declaration of the class TrianguloPascal
 ***********************************************************************/

 #if !defined(__Pascal_TrianguloPascal_h)
 #define __Pascal_TrianguloPascal_h
 
 #include "Fila.h"
 #include <vector>
 
 class TrianguloPascal
 {
 public:
    int getNumeroFilas(void);
    void setNumeroFilas(int newNumeroFilas);
    std::vector<Fila> getFilas(void);
    Fila getFila(int numeroFila);
    void generarTriangulo(void);
    TrianguloPascal();
    TrianguloPascal(int numeroFilas);
    ~TrianguloPascal();
 
 protected:
 private:
    int numeroFilas;
    std::vector<Fila> filas;
 };
 
 #endif