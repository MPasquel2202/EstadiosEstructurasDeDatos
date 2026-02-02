#pragma once

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <string>

namespace MongoConnection {

struct Config {
    std::string uri;
    std::string database;
};

Config fromEnvironment();

mongocxx::instance& instance();

mongocxx::client createClient(const Config& config);

} // namespace MongoConnection
