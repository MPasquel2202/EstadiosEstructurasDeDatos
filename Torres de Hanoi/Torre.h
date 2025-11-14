/***********************************************************************
 * Module:  Torre.h
 * Author:  Claude
 * Modified: martes, 29 de abril de 2025 
 * Purpose: Declaration of the class Torre
 ***********************************************************************/

 #if !defined(__Hanoi_Torre_h)
 #define __Hanoi_Torre_h
 
 #include <vector>
 #include <string>
 
 class Torre
 {
 public:
    std::vector<int> getDiscos(void);
    void setDiscos(std::vector<int> newDiscos);
    std::string getNombre(void);
    void setNombre(std::string newNombre);
    bool agregarDisco(int tamano);
    int removerDisco(void);
    void mostrar(void);
    Torre(std::string nombre);
    ~Torre();
 
 protected:
 private:
    std::vector<int> discos;
    std::string nombre;
 };
 
 #endif