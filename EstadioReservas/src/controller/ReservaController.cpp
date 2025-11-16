#include "controller/ReservaController.hpp"
#include "utils/InputUtils.hpp"
#include "utils/Exceptions.hpp"
#include "view/Printer.hpp"
#include <iostream>

namespace ReservaController{
    void reservar(Usuario& u, InventarioEvento& inv, const Evento& e){
        Printer::mostrarInventario(inv);

        int ya = u.totalReservadoEn(e.id);
        int maxAdic = inv.limitePorUsuario - ya;
        if(maxAdic <= 0){ throw LimiteExcedido("Ya o el limite por usuario para este evento."); }
        std::cout << "Ya reservado por usted: " << ya << " | Puede reservar adicional: " << maxAdic << " boletos\n";

        std::cout << "Cantidad GENERAL (0.." << maxAdic << "): ";
        int g = InputUtils::leerEnteroEnRango(0, maxAdic);
        int rem = maxAdic - g;
        std::cout << "Cantidad TRIBUNA (0.." << rem << "): ";
        int t = InputUtils::leerEnteroEnRango(0, rem);
        rem -= t;
        std::cout << "Cantidad PALCO (0.." << rem << "): ";
        int p = InputUtils::leerEnteroEnRango(0, rem);

        if(g + t + p == 0){ std::cout << "No se realizo reserva.\n"; return; }

        Reserva req{e.id, g, t, p};
        if(!inv.cabe(req)) throw CupoInsuficiente("No hay cupo suficiente en uno o mas tipos.");

        u.agregarOModificarReserva(req);
        inv.ocupar(req);

        std::cout << "Reserva realizada con exito.\n";
    }

    void cancelar(Usuario& u, InventarioEvento& inv, const Evento& e){
        Reserva existente{e.id,0,0,0};
        Reserva dummy;
        Reserva* ptr = u.buscarReserva(e.id);
        if(!ptr){
            std::cout << "No tiene reservas para este evento.\n";
            return;
        }
        existente = *ptr;

        std::cout << "Se cancelara la reserva completa del evento " << e.id
                  << " (G=" << existente.general << ", T=" << existente.tribuna
                  << ", P=" << existente.palco << "). Confirmar [1=Si/0=No]: ";
        int ok = InputUtils::leerEnteroEnRango(0,1);
        if(!ok){ std::cout << "Operacon cancelada.\n"; return; }

        Reserva removida;
        if(!u.eliminarReserva(e.id, removida)){
            std::cout << "No fue posible eliminar la reserva.\n";
            return;
        }

        inv.occGeneral -= removida.general; if(inv.occGeneral < 0) inv.occGeneral = 0;
        inv.occTribuna -= removida.tribuna; if(inv.occTribuna < 0) inv.occTribuna = 0;
        inv.occPalco   -= removida.palco;   if(inv.occPalco   < 0) inv.occPalco   = 0;

        std::cout << "Reserva cancelada y cupos restituidos.\n";
    }
}
