#include "structures/HashTable.h"

void HashTable::insert(const Key& key, Value value){
    table[key] = value;
}

HashTable::Value HashTable::get(const Key& key) const{
    auto it = table.find(key);
    if(it == table.end()) return nullptr;
    return it->second;
}

bool HashTable::contains(const Key& key) const{
    return table.find(key) != table.end();
}

std::size_t HashTable::size() const{
    return table.size();
}

void HashTable::clear(){
    table.clear();
}

std::vector<std::pair<HashTable::Key, HashTable::Value>> HashTable::entries() const{
    std::vector<std::pair<Key, Value>> items;
    items.reserve(table.size());
    for(const auto& kv : table){
        items.emplace_back(kv.first, kv.second);
    }
    return items;
}

HashTable construirTablaHashInventarios(const LinkedList<InventarioEvento>& inventarios){
    HashTable tabla;
    inventarios.for_each([&](const InventarioEvento& inv){
        tabla.insert(inv.eventoId, &inv);
    });
    return tabla;
}
