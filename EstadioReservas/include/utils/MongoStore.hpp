#pragma once

#include <string>
#include <vector>

#include "ds/LinkedList.hpp"
#include "model/Evento.hpp"
#include "model/InventarioEvento.hpp"
#include "model/Usuario.hpp"
#include "structures/BinarySearchTree.h"
#include "utils/MongoConnection.hpp"

namespace MongoStore {

class Store {
public:
    explicit Store(MongoConnection::Config config = MongoConnection::fromEnvironment());

    void loadUsuarios(LinkedList<Usuario>& out) const;
    void saveUsuarios(const LinkedList<Usuario>& in) const;

    void loadEventos(LinkedList<Evento>& out, BinarySearchTree<Evento>& indice) const;
    void loadInventarios(LinkedList<InventarioEvento>& out) const;
    void saveInventarios(const LinkedList<InventarioEvento>& in) const;

private:
    mongocxx::client client_;
    mongocxx::database dbUsuarios_;
    mongocxx::database dbEventos_;
    mongocxx::database dbBoletos_;
    std::string collection_;
};

Store& defaultStore();

void loadUsuarios(LinkedList<Usuario>& out);
void saveUsuarios(const LinkedList<Usuario>& in);
void loadEventos(LinkedList<Evento>& out, BinarySearchTree<Evento>& indice);
void loadInventarios(LinkedList<InventarioEvento>& out);
void saveInventarios(const LinkedList<InventarioEvento>& in);

std::vector<std::string> validarIntegridad(const LinkedList<Usuario>& usuarios,
                                           const LinkedList<Evento>& eventos,
                                           const LinkedList<InventarioEvento>& inventarios);

} // namespace MongoStore
