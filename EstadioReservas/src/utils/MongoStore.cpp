#include "utils/MongoStore.hpp"

#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/collection.hpp>
#include <mongocxx/cursor.hpp>
#include <mongocxx/exception/exception.hpp>

#include <unordered_map>
#include <unordered_set>

namespace {

std::string getString(const bsoncxx::document::view& doc, const char* key, const std::string& fallback) {
    auto it = doc[key];
    if (!it) return fallback;
    if (it.type() != bsoncxx::type::k_utf8) return fallback;
    return std::string(it.get_utf8().value);
}

int getInt(const bsoncxx::document::view& doc, const char* key, int fallback) {
    auto it = doc[key];
    if (!it) return fallback;
    switch (it.type()) {
        case bsoncxx::type::k_int32:
            return it.get_int32().value;
        case bsoncxx::type::k_int64:
            return static_cast<int>(it.get_int64().value);
        case bsoncxx::type::k_double:
            return static_cast<int>(it.get_double().value);
        default:
            return fallback;
    }
}

} // namespace

namespace MongoStore {

Store::Store(MongoConnection::Config config)
    : client_(MongoConnection::createClient(config)),
      dbUsuarios_(client_[config.databaseUsuarios]),
      dbEventos_(client_[config.databaseEventos]),
      dbBoletos_(client_[config.databaseBoletos]),
      collection_(config.collection) {}

void Store::loadUsuarios(LinkedList<Usuario>& out) const {
    auto collection = dbUsuarios_[collection_];
    auto cursor = collection.find({});
    for (const auto& doc : cursor) {
        Usuario u;
        u.cedula = getString(doc, "cedula", "");
        u.nombre = getString(doc, "nombre", "");

        auto reservasElem = doc["reservas"];
        if (reservasElem && reservasElem.type() == bsoncxx::type::k_array) {
            for (const auto& entry : reservasElem.get_array().value) {
                if (entry.type() != bsoncxx::type::k_document) continue;
                auto rdoc = entry.get_document().view();
                Reserva r;
                r.eventoId = getString(rdoc, "eventoId", "");
                r.general = getInt(rdoc, "GENERAL", 0);
                r.tribuna = getInt(rdoc, "TRIBUNA", 0);
                r.palco = getInt(rdoc, "PALCO", 0);
                u.reservas.push_back(r);
            }
        }

        out.push_back(std::move(u));
    }
}

void Store::saveUsuarios(const LinkedList<Usuario>& in) const {
    auto collection = dbUsuarios_[collection_];
    collection.delete_many({});

    in.for_each([&](const Usuario& u) {
        bsoncxx::builder::stream::document doc;
        doc << "cedula" << u.cedula
            << "nombre" << u.nombre
            << "reservas" << bsoncxx::builder::stream::open_array;

        u.reservas.for_each([&](const Reserva& r) {
            doc << bsoncxx::builder::stream::open_document
                << "eventoId" << r.eventoId
                << "GENERAL" << r.general
                << "TRIBUNA" << r.tribuna
                << "PALCO" << r.palco
                << bsoncxx::builder::stream::close_document;
        });

        doc << bsoncxx::builder::stream::close_array;
        collection.insert_one(doc.view());
    });
}

void Store::loadEventos(LinkedList<Evento>& out, BinarySearchTree<Evento>& indice) const {
    auto collection = dbEventos_[collection_];
    auto cursor = collection.find({});
    for (const auto& doc : cursor) {
        Evento e;
        std::string id = getString(doc, "id", "");
        e.id = id;
        e.nombre = getString(doc, "nombre", "");
        e.fecha = Fecha::parseISO(getString(doc, "fecha", "1970-01-01"));

        out.push_back(std::move(e));

        Evento* almacenado = out.find([&](const Evento& ev) { return ev.id == id; });
        if (almacenado) {
            indice.insert(almacenado->id, almacenado);
        }
    }
}

void Store::loadInventarios(LinkedList<InventarioEvento>& out) const {
    auto collection = dbBoletos_[collection_];
    auto cursor = collection.find({});
    for (const auto& doc : cursor) {
        InventarioEvento inv;
        inv.eventoId = getString(doc, "eventoId", "");
        inv.limitePorUsuario = getInt(doc, "limitePorUsuario", 0);

        auto capElem = doc["capacidad"];
        if (capElem && capElem.type() == bsoncxx::type::k_document) {
            auto cap = capElem.get_document().view();
            inv.capGeneral = getInt(cap, "GENERAL", 0);
            inv.capTribuna = getInt(cap, "TRIBUNA", 0);
            inv.capPalco = getInt(cap, "PALCO", 0);
        }

        auto occElem = doc["ocupados"];
        if (occElem && occElem.type() == bsoncxx::type::k_document) {
            auto occ = occElem.get_document().view();
            inv.occGeneral = getInt(occ, "GENERAL", 0);
            inv.occTribuna = getInt(occ, "TRIBUNA", 0);
            inv.occPalco = getInt(occ, "PALCO", 0);
        }

        out.push_back(std::move(inv));
    }
}

void Store::saveInventarios(const LinkedList<InventarioEvento>& in) const {
    auto collection = dbBoletos_[collection_];
    collection.delete_many({});

    in.for_each([&](const InventarioEvento& inv) {
        bsoncxx::builder::stream::document doc;
        doc << "eventoId" << inv.eventoId
            << "limitePorUsuario" << inv.limitePorUsuario
            << "capacidad" << bsoncxx::builder::stream::open_document
            << "GENERAL" << inv.capGeneral
            << "TRIBUNA" << inv.capTribuna
            << "PALCO" << inv.capPalco
            << bsoncxx::builder::stream::close_document
            << "ocupados" << bsoncxx::builder::stream::open_document
            << "GENERAL" << inv.occGeneral
            << "TRIBUNA" << inv.occTribuna
            << "PALCO" << inv.occPalco
            << bsoncxx::builder::stream::close_document;
        collection.insert_one(doc.view());
    });
}

Store& defaultStore() {
    static Store store{};
    return store;
}

void loadUsuarios(LinkedList<Usuario>& out) {
    defaultStore().loadUsuarios(out);
}

void saveUsuarios(const LinkedList<Usuario>& in) {
    defaultStore().saveUsuarios(in);
}

void loadEventos(LinkedList<Evento>& out, BinarySearchTree<Evento>& indice) {
    defaultStore().loadEventos(out, indice);
}

void loadInventarios(LinkedList<InventarioEvento>& out) {
    defaultStore().loadInventarios(out);
}

void saveInventarios(const LinkedList<InventarioEvento>& in) {
    defaultStore().saveInventarios(in);
}

std::vector<std::string> validarIntegridad(const LinkedList<Usuario>& usuarios,
                                           const LinkedList<Evento>& eventos,
                                           const LinkedList<InventarioEvento>& inventarios) {
    std::vector<std::string> alertas;
    std::unordered_set<std::string> eventosIds;
    std::unordered_map<std::string, const InventarioEvento*> invMap;

    eventos.for_each([&](const Evento& e) {
        if (!e.id.empty()) {
            eventosIds.insert(e.id);
        }
    });

    inventarios.for_each([&](const InventarioEvento& inv) {
        invMap[inv.eventoId] = &inv;
        if (!eventosIds.count(inv.eventoId)) {
            alertas.push_back("Inventario sin evento asociado: " + inv.eventoId);
        }
        if (inv.capGeneral < inv.occGeneral || inv.capTribuna < inv.occTribuna || inv.capPalco < inv.occPalco) {
            alertas.push_back("Inventario con ocupados mayores a la capacidad: " + inv.eventoId);
        }
        if (inv.limitePorUsuario < 0) {
            alertas.push_back("Inventario con limite por usuario negativo: " + inv.eventoId);
        }
    });

    eventos.for_each([&](const Evento& e) {
        if (!invMap.count(e.id)) {
            alertas.push_back("Evento sin inventario asociado: " + e.id);
        }
    });

    usuarios.for_each([&](const Usuario& u) {
        u.reservas.for_each([&](const Reserva& r) {
            if (!eventosIds.count(r.eventoId)) {
                alertas.push_back("Reserva con evento inexistente para usuario " + u.cedula + ": " + r.eventoId);
                return;
            }
            auto it = invMap.find(r.eventoId);
            if (it == invMap.end()) {
                alertas.push_back("Reserva sin inventario para usuario " + u.cedula + ": " + r.eventoId);
                return;
            }
            const InventarioEvento* inv = it->second;
            if (r.general < 0 || r.tribuna < 0 || r.palco < 0) {
                alertas.push_back("Reserva con valores negativos para usuario " + u.cedula + ": " + r.eventoId);
            }
            if (inv->limitePorUsuario > 0 && r.total() > inv->limitePorUsuario) {
                alertas.push_back("Reserva supera limite por usuario para usuario " + u.cedula + ": " + r.eventoId);
            }
        });
    });

    return alertas;
}

} // namespace MongoStore
