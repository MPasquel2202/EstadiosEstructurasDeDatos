
#pragma once
#include "ds/LinkedList.hpp"
#include "model/Usuario.hpp"

namespace AuthController{
    Usuario* login(LinkedList<Usuario>& usuarios);
}
