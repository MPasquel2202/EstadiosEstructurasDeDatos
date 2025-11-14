#ifndef PERSONA_H
#define PERSONA_H

#include <string>

class Persona {
private:
    std::string nombre;
    std::string cedula;
    int id;

public:
    Persona();
    Persona(const std::string& nombre, const std::string& cedula, int id);
    
    // Getters
    std::string getNombre() const;
    std::string getCedula() const;
    int getId() const;
    
    // Setters
    void setNombre(const std::string& nombre);
    void setCedula(const std::string& cedula);
    void setId(int id);
    
    // Para comparaciones
    bool operator==(const Persona& other) const;
};

#endif // PERSONA_H