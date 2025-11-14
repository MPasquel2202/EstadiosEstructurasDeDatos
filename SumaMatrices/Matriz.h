#if !defined(__Matriz_Matriz_h)
#define __Matriz_Matriz_h

class Matriz
{
public:
   // Getters y setters
   int getFilas(void);
   void setFilas(int newFilas);
   int getColumnas(void);
   void setColumnas(int newColumnas);
   int** getMatriz(void);
   void setMatriz(int** newMatriz);
   
   // Funciones para manipular la matriz
   void crearMatriz(int filas, int columnas);
   void liberarMemoria(void);
   void imprimirMatriz(void);
   
   // Constructores y destructor
   Matriz();
   Matriz(int filas, int columnas);
   ~Matriz();

protected:
private:    
   int filas;
   int columnas;
   int** matriz; // Puntero a puntero para matriz dinámica
};

#endif