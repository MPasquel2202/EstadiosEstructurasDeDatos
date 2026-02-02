#include "utils/MongoConnection.hpp"

#include <cstdlib>

namespace MongoConnection {

Config fromEnvironment() {
    const char* uri = std::getenv("MONGO_URI");
    const char* db = std::getenv("MONGO_DB");
    Config config;
    config.uri = uri ? uri : "mongodb://localhost:27017";
    config.database = db ? db : "estadio_reservas";
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
