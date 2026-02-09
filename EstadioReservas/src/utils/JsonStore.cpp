#include "utils/JsonStore.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <utility>

using nlohmann::json;

static bool file_exists(const std::string& p){ std::ifstream f(p); return f.good(); }
static bool is_non_empty_string(const json& j, const char* key){
    return j.contains(key) && j[key].is_string() && !j[key].get<std::string>().empty();
}

static bool is_non_negative_int(const json& j, const char* key){
    return j.contains(key) && j[key].is_number_integer() && j[key].get<int>() >= 0;
}

static bool is_positive_int(const json& j, const char* key){
    return j.contains(key) && j[key].is_number_integer() && j[key].get<int>() > 0;
}

namespace JsonStore{
    bool validarUsuarios(const std::string& ruta, std::string& error){
        if(!file_exists(ruta)){
            error = "Archivo de usuarios no existe: " + ruta;
            return false;
        }
        try{
            std::ifstream in(ruta);
            json j; in >> j;
            if(!j.contains("usuarios") || !j["usuarios"].is_array()){
                error = "Formato invalido: falta arreglo 'usuarios'.";
                return false;
            }
            for(const auto& ju : j["usuarios"]){
                if(!is_non_empty_string(ju, "cedula") || !is_non_empty_string(ju, "nombre")){
                    error = "Usuario invalido: cedula/nombre requeridos.";
                    return false;
                }
                if(ju.contains("reservas")){
                    if(!ju["reservas"].is_array()){
                        error = "Reservas invalidas: debe ser arreglo.";
                        return false;
                    }
                    for(const auto& jr : ju["reservas"]){
                        if(!is_non_empty_string(jr, "eventoId")){
                            error = "Reserva invalida: eventoId requerido.";
                            return false;
                        }
                        if(!is_non_negative_int(jr, "GENERAL")
                           || !is_non_negative_int(jr, "TRIBUNA")
                           || !is_non_negative_int(jr, "PALCO")){
                            error = "Reserva invalida: cantidades negativas.";
                            return false;
                        }
                    }
                }
            }
        }catch(const std::exception& e){
            error = std::string("Error leyendo usuarios: ") + e.what();
            return false;
        }
        return true;
    }

    bool validarEventos(const std::string& ruta, std::string& error){
        if(!file_exists(ruta)){
            error = "Archivo de eventos no existe: " + ruta;
            return false;
        }
        try{
            std::ifstream in(ruta);
            json j; in >> j;
            if(!j.contains("eventos") || !j["eventos"].is_array()){
                error = "Formato invalido: falta arreglo 'eventos'.";
                return false;
            }
            for(const auto& je : j["eventos"]){
                if(!is_non_empty_string(je, "id") || !is_non_empty_string(je, "nombre")){
                    error = "Evento invalido: id/nombre requeridos.";
                    return false;
                }
                if(!is_non_empty_string(je, "fecha")){
                    error = "Evento invalido: fecha requerida.";
                    return false;
                }
                try{
                    Fecha::parseISO(je.value("fecha", "1970-01-01"));
                }catch(const std::exception&){
                    error = "Evento invalido: fecha con formato incorrecto.";
                    return false;
                }
            }
        }catch(const std::exception& e){
            error = std::string("Error leyendo eventos: ") + e.what();
            return false;
        }
        return true;
    }

    bool validarInventarios(const std::string& ruta, std::string& error){
        if(!file_exists(ruta)){
            error = "Archivo de inventarios no existe: " + ruta;
            return false;
        }
        try{
            std::ifstream in(ruta);
            json j; in >> j;
            if(!j.contains("inventarios") || !j["inventarios"].is_array()){
                error = "Formato invalido: falta arreglo 'inventarios'.";
                return false;
            }
            for(const auto& ji : j["inventarios"]){
                if(!is_non_empty_string(ji, "eventoId")){
                    error = "Inventario invalido: eventoId requerido.";
                    return false;
                }
                if(!is_positive_int(ji, "limitePorUsuario")){
                    error = "Inventario invalido: limitePorUsuario debe ser positivo.";
                    return false;
                }
                if(!ji.contains("capacidad") || !ji["capacidad"].is_object()
                   || !ji.contains("ocupados") || !ji["ocupados"].is_object()){
                    error = "Inventario invalido: capacidad/ocupados requeridos.";
                    return false;
                }
                const auto& cap = ji["capacidad"];
                const auto& occ = ji["ocupados"];
                if(!is_non_negative_int(cap, "GENERAL")
                   || !is_non_negative_int(cap, "TRIBUNA")
                   || !is_non_negative_int(cap, "PALCO")){
                    error = "Inventario invalido: capacidades negativas.";
                    return false;
                }
                if(!is_non_negative_int(occ, "GENERAL")
                   || !is_non_negative_int(occ, "TRIBUNA")
                   || !is_non_negative_int(occ, "PALCO")){
                    error = "Inventario invalido: ocupados negativos.";
                    return false;
                }
                if(occ["GENERAL"].get<int>() > cap["GENERAL"].get<int>()
                   || occ["TRIBUNA"].get<int>() > cap["TRIBUNA"].get<int>()
                   || occ["PALCO"].get<int>() > cap["PALCO"].get<int>()){
                    error = "Inventario invalido: ocupados exceden capacidad.";
                    return false;
                }
            }
        }catch(const std::exception& e){
            error = std::string("Error leyendo inventarios: ") + e.what();
            return false;
        }
        return true;
    }

    bool validarDatos(const std::string& rutaUsuarios,
                      const std::string& rutaEventos,
                      const std::string& rutaInventarios,
                      std::string& error){
        if(!validarUsuarios(rutaUsuarios, error)) return false;
        if(!validarEventos(rutaEventos, error)) return false;
        if(!validarInventarios(rutaInventarios, error)) return false;
        return true;
    }

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
