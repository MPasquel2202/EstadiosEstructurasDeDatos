/***********************************************************************
 * Module:  IngresoDatos.h
 * Author:  USUARIO
 * Modified: domingo, 27 de abril de 2025 11:56:42
 * Purpose: Declaration of the class IngresoDatos
 ***********************************************************************/

#if !defined(__Fecha2_IngresoDatos_h)
#define __Fecha2_IngresoDatos_h

class IngresoDatos
{
public:
    int getValor(void);
    void setValor(int newValor);
    int pedirNumero(char msj[20]);
    IngresoDatos();
    ~IngresoDatos();

protected:
private:
    int valor;
};

#endif