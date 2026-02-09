#pragma once
#include "utils/OrdenadorEventos.hpp"
#include "utils/Comparadores.hpp"
#include "model/Evento.hpp"
#include "model/InventarioEvento.hpp"
#include "model/Usuario.hpp"
#include "ds/LinkedList.hpp"

class OrdenamientoController {
public:
    static void mostrarMenuOrdenamiento(LinkedList<Evento>& eventos, 
                                      LinkedList<InventarioEvento>& inventarios);
    
    static void mostrarMenuOrdenamientoReservas(Usuario& usuario,
                                               const LinkedList<Evento>& eventos);

    static void ordenarLetrasNombresUsuarios();
    
private:
    static void aplicarOrdenamiento(OrdenadorEventos<Evento>& ordenador,
                                  int criterio, int algoritmo, bool ascendente);
    
    static std::string obtenerNombreAlgoritmo(int algoritmo);
    static std::string obtenerNombreCriterio(int criterio);
    
    // FUNCIÓN AUXILIAR PARA ORDENAR LETRAS DE UN NOMBRE
    static std::string ordenarLetrasNombre(const std::string& nombre);
};
