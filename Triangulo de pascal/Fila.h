/***********************************************************************
 * Module:  Fila.h
 * Author:  Programador
 * Modified: martes, 29 de abril de 2025 12:00:00
 * Purpose: Declaration of the class Fila (con recursividad)
 ***********************************************************************/

 #if !defined(__Pascal_Fila_h)
 #define __Pascal_Fila_h
 
 #include <vector>
 
 class Fila
 {
 public:
    std::vector<int> getElementos(void);
    void setElementos(std::vector<int> newElementos);
    int getNumeroFila(void);
    void setNumeroFila(int newNumeroFila);
    void generarElementos(void);
    Fila();
    Fila(int numeroFila);
    ~Fila();
 
 protected:
 private:
    std::vector<int> elementos;
    int numeroFila;
    
    // Nuevo método recursivo para calcular coeficientes binomiales
    int coeficienteBinomialRecursivo(int n, int k);
 };
 
 #endif