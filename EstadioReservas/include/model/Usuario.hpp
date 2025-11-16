#pragma once
#include <string>
#include <ostream>
#include "ds/LinkedList.hpp"
#include "model/Reserva.hpp"

struct Usuario{
    std::string cedula;
    std::string nombre;
    LinkedList<Reserva> reservas;

    int totalReservadoEn(const std::string& eventoId) const;
    Reserva* buscarReserva(const std::string& eventoId);
    void agregarOModificarReserva(const Reserva& r);

    bool eliminarReserva(const std::string& eventoId, Reserva& out);
};

bool operator==(const Usuario& a, const Usuario& b);
std::ostream& operator<<(std::ostream& os, const Usuario& u);
