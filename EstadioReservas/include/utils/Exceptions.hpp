
#pragma once
#include <stdexcept>

struct CedulaInvalida : public std::runtime_error{ using std::runtime_error::runtime_error; };
struct FechaInvalida  : public std::runtime_error{ using std::runtime_error::runtime_error; };
struct LimiteExcedido : public std::runtime_error{ using std::runtime_error::runtime_error; };
struct CupoInsuficiente : public std::runtime_error{ using std::runtime_error::runtime_error; };
struct EntradaInvalida : public std::runtime_error{ using std::runtime_error::runtime_error; };
