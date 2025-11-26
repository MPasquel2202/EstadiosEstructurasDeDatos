
#pragma once
#include <string>
#include "ds/LinkedList.hpp"
#include "model/Usuario.hpp"
#include "model/Evento.hpp"
#include "model/InventarioEvento.hpp"

namespace JsonStore{
    void loadUsuarios(LinkedList<Usuario>& out, const std::string& ruta);
    void saveUsuarios(const LinkedList<Usuario>& in, const std::string& ruta);
    void loadEventos(LinkedList<Evento>& out, const std::string& ruta);
    void loadInventarios(LinkedList<InventarioEvento>& out, const std::string& ruta);
    void saveInventarios(const LinkedList<InventarioEvento>& in, const std::string& ruta);
}
