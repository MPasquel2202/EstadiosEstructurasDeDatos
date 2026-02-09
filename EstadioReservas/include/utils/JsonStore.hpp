
#pragma once
#include <string>
#include "ds/LinkedList.hpp"
#include "structures/BinarySearchTree.h"
#include "model/Usuario.hpp"
#include "model/Evento.hpp"
#include "model/InventarioEvento.hpp"

namespace JsonStore{
    bool validarUsuarios(const std::string& ruta, std::string& error);
    bool validarEventos(const std::string& ruta, std::string& error);
    bool validarInventarios(const std::string& ruta, std::string& error);
    bool validarDatos(const std::string& rutaUsuarios,
                      const std::string& rutaEventos,
                      const std::string& rutaInventarios,
                      std::string& error);
    void loadUsuarios(LinkedList<Usuario>& out, const std::string& ruta);
    void saveUsuarios(const LinkedList<Usuario>& in, const std::string& ruta);
    void loadEventos(LinkedList<Evento>& out, const std::string& ruta);
    void loadEventos(LinkedList<Evento>& out, BinarySearchTree<Evento>& indice, const std::string& ruta);
    void loadInventarios(LinkedList<InventarioEvento>& out, const std::string& ruta);
    void saveInventarios(const LinkedList<InventarioEvento>& in, const std::string& ruta);
}
