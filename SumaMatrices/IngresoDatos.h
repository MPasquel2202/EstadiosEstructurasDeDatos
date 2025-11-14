#if !defined(__Matriz_IngresoDatos_h)
#define __Matriz_IngresoDatos_h

class IngresoDatos
{
public:
    int getValor(void);
    void setValor(int newValor);
    int pedirNumero(const char* msj);
    IngresoDatos();
    ~IngresoDatos();

protected:
private:
    int valor;
};

#endif