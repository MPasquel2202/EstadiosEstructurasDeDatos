
#pragma once
#include <stdexcept>

class CedulaInvalida : public std::runtime_error{
public:
    using std::runtime_error::runtime_error;
};

class FechaInvalida : public std::runtime_error{
public:
    using std::runtime_error::runtime_error;
};

class LimiteExcedido : public std::runtime_error{
public:
    using std::runtime_error::runtime_error;
};

class CupoInsuficiente : public std::runtime_error{
public:
    using std::runtime_error::runtime_error;
};

class EntradaInvalida : public std::runtime_error{
public:
    using std::runtime_error::runtime_error;
};
