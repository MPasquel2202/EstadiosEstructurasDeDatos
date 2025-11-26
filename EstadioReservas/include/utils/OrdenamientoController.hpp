#pragma once
#include "OrdenadorEventos.hpp"
#include "Comparadores.hpp"
#include "../model/Evento.hpp"
#include "../model/InventarioEvento.hpp"
#include "../ds/LinkedList.hpp"

class OrdenamientoController {
public:
    static void mostrarMenuOrdenamiento(LinkedList<Evento>& eventos, 
                                      LinkedList<InventarioEvento>& inventarios);
    
private:
    static void aplicarOrdenamiento(OrdenadorEventos<Evento>& ordenador,
                                  int criterio, int algoritmo, bool ascendente);
    
    static std::string obtenerNombreAlgoritmo(int algoritmo);
    static std::string obtenerNombreCriterio(int criterio);
};