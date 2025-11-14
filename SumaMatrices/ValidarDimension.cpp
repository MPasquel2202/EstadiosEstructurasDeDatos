#include "ValidarDimension.h"

bool ValidarDimension::validarDimension(int dimension)
{
   // Una dimensión válida debe ser mayor que 0
   return dimension > 0;
}

bool ValidarDimension::dimensionesIguales(int filas1, int columnas1, int filas2, int columnas2)
{
   // Para poder sumar matrices, sus dimensiones deben ser iguales
   return (filas1 == filas2) && (columnas1 == columnas2);
}

ValidarDimension::ValidarDimension()
{
}

ValidarDimension::~ValidarDimension()
{
   // TODO : implement
}