#pragma once
#include "model/Usuario.hpp"
#include "ds/LinkedList.hpp"
#include <string>

class FileManager {
public:
    static LinkedList<Usuario> cargarUsuarios();
    static bool guardarUsuarios(const LinkedList<Usuario>& usuarios);
};
