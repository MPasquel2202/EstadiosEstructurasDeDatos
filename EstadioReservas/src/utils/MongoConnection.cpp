#include "utils/MongoConnection.hpp"

#include <cstdlib>

namespace MongoConnection {

Config fromEnvironment() {
    const char* uri = std::getenv("MONGO_URI");
    const char* dbUsuarios = std::getenv("MONGO_DB_USUARIOS");
    const char* dbEventos = std::getenv("MONGO_DB_EVENTOS");
    const char* dbBoletos = std::getenv("MONGO_DB_BOLETOS");
    const char* collection = std::getenv("MONGO_COLLECTION");
    Config config;
    config.uri = uri ? uri : "mongodb://localhost:27017";
    config.databaseUsuarios = dbUsuarios ? dbUsuarios : "usuarios";
    config.databaseEventos = dbEventos ? dbEventos : "eventos";
    config.databaseBoletos = dbBoletos ? dbBoletos : "boletos";
    config.collection = collection ? collection : "EstadioReservas";
    return config;
}

mongocxx::instance& instance() {
    static mongocxx::instance inst{};
    return inst;
}

mongocxx::client createClient(const Config& config) {
    instance();
    mongocxx::uri uri{config.uri};
    return mongocxx::client{uri};
}

} // namespace MongoConnection
