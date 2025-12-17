#include "utils/JsonStore.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <utility>

using nlohmann::json;

static bool file_exists(const std::string& p){ std::ifstream f(p); return f.good(); }

namespace JsonStore{

    void loadUsuarios(LinkedList<Usuario>& out, const std::string& ruta){
        if(!file_exists(ruta)) return;
        std::ifstream in(ruta);
        json j; in >> j;
        if(!j.contains("usuarios")) return;

        for(const auto& ju : j["usuarios"]) {
            Usuario u;
            u.cedula = ju.value("cedula", "");
            u.nombre = ju.value("nombre", "");

            if(ju.contains("reservas")){
                for(const auto& jr : ju["reservas"]) {
                    Reserva r;
                    r.eventoId = jr.value("eventoId", "");
                    r.general  = jr.value("GENERAL", 0);
                    r.tribuna  = jr.value("TRIBUNA", 0);
                    r.palco    = jr.value("PALCO",   0);
                    u.reservas.push_back(r);
                }
            }
            out.push_back(std::move(u));
        }
    }

    void saveUsuarios(const LinkedList<Usuario>& in, const std::string& ruta){
        json j;
        j["usuarios"] = json::array();

        in.for_each([&](const Usuario& u){
            json ju;
            ju["cedula"]   = u.cedula;
            ju["nombre"]   = u.nombre;
            ju["reservas"] = json::array();

            u.reservas.for_each([&](const Reserva& r){
                json jr;
                jr["eventoId"] = r.eventoId;
                jr["GENERAL"]  = r.general;
                jr["TRIBUNA"]  = r.tribuna;
                jr["PALCO"]    = r.palco;
                ju["reservas"].push_back(jr);
            });

            j["usuarios"].push_back(ju);
        });

        std::ofstream outF(ruta);
        outF << j.dump(2);
    }

    void loadEventos(LinkedList<Evento>& out, const std::string& ruta){
        BinarySearchTree<Evento> dummy;
        loadEventos(out, dummy, ruta);
    }

    void loadEventos(LinkedList<Evento>& out, BinarySearchTree<Evento>& indice, const std::string& ruta){
        if(!file_exists(ruta)) return;
        std::ifstream in(ruta);
        json j; in >> j;
        if(!j.contains("eventos")) return;

        for(const auto& je : j["eventos"]) {
            Evento e;
            std::string id = je.value("id", "");
            e.id     = id;
            e.nombre = je.value("nombre", "");
            e.fecha  = Fecha::parseISO(je.value("fecha","1970-01-01"));
            out.push_back(std::move(e));

            Evento* almacenado = out.find([&](const Evento& ev){ return ev.id == id; });
            if(almacenado){
                indice.insert(almacenado->id, almacenado);
            }
        }
    }

    void loadInventarios(LinkedList<InventarioEvento>& out, const std::string& ruta){
        if(!file_exists(ruta)) return;
        std::ifstream in(ruta);
        json j; in >> j;
        if(!j.contains("inventarios")) return;

        for(const auto& ji : j["inventarios"]) {
            InventarioEvento inv;
            inv.eventoId         = ji.value("eventoId","");
            inv.limitePorUsuario = ji.value("limitePorUsuario",0);

            auto cap = ji.value("capacidad", json::object());
            auto occ = ji.value("ocupados",  json::object());

            inv.capGeneral = cap.value("GENERAL",0);
            inv.capTribuna = cap.value("TRIBUNA",0);
            inv.capPalco   = cap.value("PALCO",0);

            inv.occGeneral = occ.value("GENERAL",0);
            inv.occTribuna = occ.value("TRIBUNA",0);
            inv.occPalco   = occ.value("PALCO",0);

            out.push_back(std::move(inv));
        }
    }

    void saveInventarios(const LinkedList<InventarioEvento>& in, const std::string& ruta){
        json j;
        j["inventarios"] = json::array();

        in.for_each([&](const InventarioEvento& inv){
            json ji;
            ji["eventoId"]         = inv.eventoId;
            ji["limitePorUsuario"] = inv.limitePorUsuario;
            ji["capacidad"] = {
                {"GENERAL", inv.capGeneral},
                {"TRIBUNA", inv.capTribuna},
                {"PALCO",   inv.capPalco}
            };
            ji["ocupados"] = {
                {"GENERAL", inv.occGeneral},
                {"TRIBUNA", inv.occTribuna},
                {"PALCO",   inv.occPalco}
            };
            j["inventarios"].push_back(ji);
        });

        std::ofstream outF(ruta);
        outF << j.dump(2);
    }
}
