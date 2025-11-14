#include "Persona.h"

Persona::Persona() : nombre(""), cedula(""), id(0) {}

Persona::Persona(const std::string& nombre, const std::string& cedula, int id) 
    : nombre(nombre), cedula(cedula), id(id) {}

std::string Persona::getNombre() const {
    return nombre;
}

std::string Persona::getCedula() const {
    return cedula;
}

int Persona::getId() const {
    return id;
}

void Persona::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

void Persona::setCedula(const std::string& cedula) {
    this->cedula = cedula;
}

void Persona::setId(int id) {
    this->id = id;
}

bool Persona::operator==(const Persona& other) const {
    return (id == other.id && 
            cedula == other.cedula &&
            nombre == other.nombre);
}