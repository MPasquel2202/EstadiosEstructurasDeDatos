#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "model/InventarioEvento.hpp"
#include "ds/LinkedList.hpp"

class HashTable {
public:
    using Key = std::string;
    using Value = const InventarioEvento*;

    void insert(const Key& key, Value value);
    Value get(const Key& key) const;
    bool contains(const Key& key) const;
    std::size_t size() const;
    void clear();
    std::vector<std::pair<Key, Value>> entries() const;

private:
    std::unordered_map<Key, Value> table;
};

HashTable construirTablaHashInventarios(const LinkedList<InventarioEvento>& inventarios);
