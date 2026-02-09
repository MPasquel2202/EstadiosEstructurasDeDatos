#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils/EstrategiasController.hpp"
#include "utils/InputUtils.hpp"

namespace {

struct EventoInfo {
    std::string id;
    std::string nombre;
    Fecha fecha;
    int cuposDisponibles{0};
};

struct InventarioInfo {
    int dispGeneral{0};
    int dispTribuna{0};
    int dispPalco{0};
};

int totalDisponibles(const InventarioInfo& inv) {
    return inv.dispGeneral + inv.dispTribuna + inv.dispPalco;
}

std::string fechaIso(const Fecha& f) {
    return f.iso();
}

std::vector<EventoInfo> cargarEventosConCupos(const LinkedList<Evento>& eventos,
                                              const LinkedList<InventarioEvento>& inventarios) {
    std::unordered_map<std::string, InventarioEvento> inventariosMap;
    inventarios.for_each([&](const InventarioEvento& inv) {
        inventariosMap[inv.eventoId] = inv;
    });

    std::vector<EventoInfo> infos;
    eventos.for_each([&](const Evento& e) {
        auto it = inventariosMap.find(e.id);
        InventarioInfo inv{};
        if (it != inventariosMap.end()) {
            inv.dispGeneral = it->second.capGeneral - it->second.occGeneral;
            inv.dispTribuna = it->second.capTribuna - it->second.occTribuna;
            inv.dispPalco = it->second.capPalco - it->second.occPalco;
        }
        infos.push_back({e.id, e.nombre, e.fecha, totalDisponibles(inv)});
    });

    if (!infos.empty()) {
        return infos;
    }

    Fecha f1{2024, 9, 14};
    Fecha f2{2024, 10, 5};
    Fecha f3{2024, 10, 26};
    Fecha f4{2024, 11, 9};
    Fecha f5{2024, 12, 1};
    return {
        {"EV-EX-01", "Final Nacional", f1, 320},
        {"EV-EX-02", "Clasico Universitario", f2, 180},
        {"EV-EX-03", "Festival Rock", f3, 240},
        {"EV-EX-04", "Concierto Sinfonico", f4, 150},
        {"EV-EX-05", "Torneo Juvenil", f5, 90}
    };
}

std::vector<std::string> cargarNombresUsuarios(const LinkedList<Usuario>& usuarios) {
    std::vector<std::string> nombres;
    usuarios.for_each([&](const Usuario& u) {
        nombres.push_back(u.nombre);
    });

    if (!nombres.empty()) {
        return nombres;
    }

    return {"Marlon Pasquel", "Brandon Pazmino", "Lucia Ramos", "Karla N.", "Alfonso M."};
}

std::unordered_map<std::string, InventarioInfo> cargarInventarios(const LinkedList<InventarioEvento>& inventarios) {
    std::unordered_map<std::string, InventarioInfo> map;
    inventarios.for_each([&](const InventarioEvento& inv) {
        map[inv.eventoId] = InventarioInfo{
            inv.capGeneral - inv.occGeneral,
            inv.capTribuna - inv.occTribuna,
            inv.capPalco - inv.occPalco
        };
    });
    return map;
}

void imprimirEventos(const std::vector<EventoInfo>& eventos) {
    for (const auto& e : eventos) {
        std::cout << "• [" << e.id << "] " << e.nombre << " | "
                  << fechaIso(e.fecha) << " | cupos: " << e.cuposDisponibles << "\n";
    }
}

void menuProgramacionExhaustiva(const LinkedList<Evento>& eventos,
                                const LinkedList<InventarioEvento>& inventarios,
                                const LinkedList<Usuario>& usuarios) {
    while (true) {
        std::cout << "\n=== PROGRAMACION EXHAUSTIVA ===\n";
        std::cout << "[1] Buscar pares de eventos por cupos exactos\n";
        std::cout << "[2] Buscar usuarios por coincidencia de nombre\n";
        std::cout << "[0] Volver\n";
        std::cout << "Opcion: ";
        int opc = InputUtils::leerEnteroEnRango(0, 2);
        if (opc == 0) return;

        if (opc == 1) {
            auto info = cargarEventosConCupos(eventos, inventarios);
            std::cout << "\nEventos disponibles:\n";
            imprimirEventos(info);
            std::cout << "\nCupos objetivo: ";
            int objetivo = InputUtils::leerEnteroEnRango(1, 2000);
            bool encontrado = false;
            for (size_t i = 0; i < info.size(); ++i) {
                for (size_t j = i + 1; j < info.size(); ++j) {
                    int suma = info[i].cuposDisponibles + info[j].cuposDisponibles;
                    if (suma == objetivo) {
                        std::cout << "-> " << info[i].nombre << " + "
                                  << info[j].nombre << " = " << suma << "\n";
                        encontrado = true;
                    }
                }
            }
            if (!encontrado) {
                std::cout << "No se encontraron pares exactos para " << objetivo << ".\n";
            }
        } else {
            auto nombres = cargarNombresUsuarios(usuarios);
            std::cout << "\nUsuarios disponibles:\n";
            for (const auto& nombre : nombres) {
                std::cout << "• " << nombre << "\n";
            }
            std::cout << "\nFragmento a buscar: ";
            std::string fragmento = InputUtils::leerLineaNoVacia(1);
            std::string fragmentoLower = fragmento;
            std::transform(fragmentoLower.begin(), fragmentoLower.end(), fragmentoLower.begin(), ::tolower);

            bool encontrado = false;
            for (const auto& nombre : nombres) {
                std::string nombreLower = nombre;
                std::transform(nombreLower.begin(), nombreLower.end(), nombreLower.begin(), ::tolower);
                if (nombreLower.find(fragmentoLower) != std::string::npos) {
                    std::cout << "-> Coincidencia: " << nombre << "\n";
                    encontrado = true;
                }
            }
            if (!encontrado) {
                std::cout << "No se encontraron coincidencias para \"" << fragmento << "\".\n";
            }
        }
    }
}

int busquedaBinariaNombre(const std::vector<EventoInfo>& eventos, const std::string& objetivo) {
    int izquierda = 0;
    int derecha = static_cast<int>(eventos.size()) - 1;
    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        if (eventos[medio].nombre == objetivo) {
            return medio;
        }
        if (eventos[medio].nombre < objetivo) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }
    return -1;
}

void menuDivideVenceras(const LinkedList<Evento>& eventos,
                        const LinkedList<InventarioEvento>& inventarios) {
    while (true) {
        std::cout << "\n=== DIVIDE Y VENCERAS ===\n";
        std::cout << "[1] Busqueda binaria de evento por nombre\n";
        std::cout << "[2] Merge de listas de eventos por fecha\n";
        std::cout << "[0] Volver\n";
        std::cout << "Opcion: ";
        int opc = InputUtils::leerEnteroEnRango(0, 2);
        if (opc == 0) return;

        auto info = cargarEventosConCupos(eventos, inventarios);
        if (opc == 1) {
            std::sort(info.begin(), info.end(), [](const EventoInfo& a, const EventoInfo& b) {
                return a.nombre < b.nombre;
            });
            std::cout << "\nEventos ordenados por nombre:\n";
            imprimirEventos(info);
            std::cout << "\nNombre exacto a buscar: ";
            std::string objetivo = InputUtils::leerLineaNoVacia(1);
            int indice = busquedaBinariaNombre(info, objetivo);
            if (indice >= 0) {
                std::cout << "Encontrado: " << info[indice].nombre
                          << " en fecha " << fechaIso(info[indice].fecha) << ".\n";
            } else {
                std::cout << "No se encontro el evento \"" << objetivo << "\".\n";
            }
        } else {
            if (info.size() < 2) {
                std::cout << "No hay suficientes eventos para dividir y mezclar.\n";
                continue;
            }
            size_t mitad = info.size() / 2;
            std::vector<EventoInfo> izquierda(info.begin(), info.begin() + mitad);
            std::vector<EventoInfo> derecha(info.begin() + mitad, info.end());
            auto cmpFecha = [](const EventoInfo& a, const EventoInfo& b) {
                return a.fecha < b.fecha;
            };
            std::sort(izquierda.begin(), izquierda.end(), cmpFecha);
            std::sort(derecha.begin(), derecha.end(), cmpFecha);

            std::vector<EventoInfo> fusion;
            fusion.reserve(info.size());
            size_t i = 0;
            size_t j = 0;
            while (i < izquierda.size() && j < derecha.size()) {
                if (cmpFecha(izquierda[i], derecha[j])) {
                    fusion.push_back(izquierda[i++]);
                } else {
                    fusion.push_back(derecha[j++]);
                }
            }
            while (i < izquierda.size()) {
                fusion.push_back(izquierda[i++]);
            }
            while (j < derecha.size()) {
                fusion.push_back(derecha[j++]);
            }
            std::cout << "\nResultado del merge por fecha:\n";
            imprimirEventos(fusion);
        }
    }
}

void menuVoraz(const LinkedList<Evento>& eventos,
               const LinkedList<InventarioEvento>& inventarios) {
    while (true) {
        std::cout << "\n=== ALGORITMO VORAZ ===\n";
        std::cout << "[1] Seleccionar eventos mas cercanos (greedy)\n";
        std::cout << "[2] Cubrir cupos objetivo con eventos de mayor disponibilidad\n";
        std::cout << "[0] Volver\n";
        std::cout << "Opcion: ";
        int opc = InputUtils::leerEnteroEnRango(0, 2);
        if (opc == 0) return;

        auto info = cargarEventosConCupos(eventos, inventarios);
        if (opc == 1) {
            std::cout << "\nCantidad de eventos a sugerir: ";
            int k = InputUtils::leerEnteroEnRango(1, static_cast<int>(info.size()));
            std::vector<EventoInfo> seleccion;
            std::vector<EventoInfo> restantes = info;
            for (int i = 0; i < k; ++i) {
                auto it = std::min_element(restantes.begin(), restantes.end(),
                                           [](const EventoInfo& a, const EventoInfo& b) {
                                               return a.fecha < b.fecha;
                                           });
                seleccion.push_back(*it);
                restantes.erase(it);
            }
            std::cout << "\nSeleccion greedy de eventos cercanos:\n";
            imprimirEventos(seleccion);
        } else {
            std::cout << "\nCupos objetivo: ";
            int objetivo = InputUtils::leerEnteroEnRango(1, 2000);
            std::sort(info.begin(), info.end(), [](const EventoInfo& a, const EventoInfo& b) {
                return a.cuposDisponibles > b.cuposDisponibles;
            });
            int acumulado = 0;
            std::vector<EventoInfo> seleccion;
            for (const auto& e : info) {
                if (acumulado >= objetivo) break;
                if (e.cuposDisponibles == 0) continue;
                seleccion.push_back(e);
                acumulado += e.cuposDisponibles;
            }
            if (seleccion.empty()) {
                std::cout << "No hay cupos disponibles para cubrir el objetivo.\n";
                continue;
            }
            std::cout << "\nSeleccion greedy por cupos:\n";
            imprimirEventos(seleccion);
            std::cout << "Cupos acumulados: " << acumulado << " (objetivo " << objetivo << ")\n";
        }
    }
}

void menuDinamica(const LinkedList<Evento>& eventos,
                  const LinkedList<InventarioEvento>& inventarios) {
    while (true) {
        std::cout << "\n=== PROGRAMACION DINAMICA ===\n";
        std::cout << "[1] Mejor combinacion de eventos hasta un limite de cupos\n";
        std::cout << "[2] Contar formas de armar cupos con paquetes ejemplo\n";
        std::cout << "[0] Volver\n";
        std::cout << "Opcion: ";
        int opc = InputUtils::leerEnteroEnRango(0, 2);
        if (opc == 0) return;

        if (opc == 1) {
            auto info = cargarEventosConCupos(eventos, inventarios);
            std::cout << "\nEventos disponibles:\n";
            imprimirEventos(info);
            std::cout << "\nLimite de cupos: ";
            int limite = InputUtils::leerEnteroEnRango(1, 2000);
            std::vector<int> prevSum(limite + 1, -1);
            std::vector<int> prevIdx(limite + 1, -1);
            std::vector<bool> dp(limite + 1, false);
            dp[0] = true;
            for (size_t idx = 0; idx < info.size(); ++idx) {
                int peso = info[idx].cuposDisponibles;
                for (int s = limite - peso; s >= 0; --s) {
                    if (dp[s] && !dp[s + peso]) {
                        dp[s + peso] = true;
                        prevSum[s + peso] = s;
                        prevIdx[s + peso] = static_cast<int>(idx);
                    }
                }
            }
            int mejor = 0;
            for (int s = limite; s >= 0; --s) {
                if (dp[s]) {
                    mejor = s;
                    break;
                }
            }
            std::cout << "\nMejor total alcanzado: " << mejor << " cupos.\n";
            std::vector<EventoInfo> seleccion;
            int s = mejor;
            while (s > 0 && prevIdx[s] != -1) {
                int idx = prevIdx[s];
                seleccion.push_back(info[idx]);
                s = prevSum[s];
            }
            if (seleccion.empty()) {
                std::cout << "No se encontraron combinaciones dentro del limite.\n";
            } else {
                std::cout << "Eventos seleccionados:\n";
                imprimirEventos(seleccion);
            }
        } else {
            std::vector<int> paquetes = {1, 3, 5, 7};
            std::cout << "\nPaquetes ejemplo (cupos): 1, 3, 5, 7\n";
            std::cout << "Cupos objetivo: ";
            int objetivo = InputUtils::leerEnteroEnRango(1, 30);
            std::vector<long long> dp(objetivo + 1, 0);
            dp[0] = 1;
            for (int paquete : paquetes) {
                for (int s = paquete; s <= objetivo; ++s) {
                    dp[s] += dp[s - paquete];
                }
            }
            std::cout << "Formas de alcanzar " << objetivo << ": " << dp[objetivo] << "\n";
        }
    }
}

bool backtrackAsignacion(int objetivo,
                         const InventarioInfo& inv,
                         int idx,
                         const std::vector<std::string>& tipos,
                         std::vector<int>& seleccion) {
    if (idx == static_cast<int>(tipos.size()) - 1) {
        int restante = objetivo;
        for (int i = 0; i < idx; ++i) {
            restante -= seleccion[i];
        }
        int maxDisp = 0;
        if (tipos[idx] == "General") maxDisp = inv.dispGeneral;
        if (tipos[idx] == "Tribuna") maxDisp = inv.dispTribuna;
        if (tipos[idx] == "Palco") maxDisp = inv.dispPalco;
        if (restante >= 0 && restante <= maxDisp) {
            seleccion[idx] = restante;
            return true;
        }
        return false;
    }

    int maxDisp = 0;
    if (tipos[idx] == "General") maxDisp = inv.dispGeneral;
    if (tipos[idx] == "Tribuna") maxDisp = inv.dispTribuna;
    if (tipos[idx] == "Palco") maxDisp = inv.dispPalco;
    for (int cantidad = 0; cantidad <= maxDisp; ++cantidad) {
        seleccion[idx] = cantidad;
        int suma = 0;
        for (int i = 0; i <= idx; ++i) {
            suma += seleccion[i];
        }
        if (suma > objetivo) break;
        if (backtrackAsignacion(objetivo, inv, idx + 1, tipos, seleccion)) {
            return true;
        }
    }
    return false;
}

void menuBacktracking(const LinkedList<Evento>& eventos,
                      const LinkedList<InventarioEvento>& inventarios) {
    while (true) {
        std::cout << "\n=== BACKTRACKING ===\n";
        std::cout << "[1] Armar agenda sin fechas repetidas\n";
        std::cout << "[2] Asignar cupos por tipo con backtracking\n";
        std::cout << "[0] Volver\n";
        std::cout << "Opcion: ";
        int opc = InputUtils::leerEnteroEnRango(0, 2);
        if (opc == 0) return;

        auto info = cargarEventosConCupos(eventos, inventarios);
        if (opc == 1) {
            std::vector<EventoInfo> mejor;
            std::vector<EventoInfo> actual;
            std::unordered_map<std::string, bool> fechasUsadas;

            std::function<void(size_t)> dfs = [&](size_t idx) {
                if (idx == info.size()) {
                    if (actual.size() > mejor.size()) {
                        mejor = actual;
                    }
                    return;
                }
                dfs(idx + 1);
                std::string fecha = fechaIso(info[idx].fecha);
                if (!fechasUsadas[fecha]) {
                    fechasUsadas[fecha] = true;
                    actual.push_back(info[idx]);
                    dfs(idx + 1);
                    actual.pop_back();
                    fechasUsadas[fecha] = false;
                }
            };
            dfs(0);
            std::cout << "\nAgenda maxima sin repetir fecha (" << mejor.size() << " eventos):\n";
            imprimirEventos(mejor);
        } else {
            auto inventarioMap = cargarInventarios(inventarios);
            std::cout << "\nEventos disponibles:\n";
            imprimirEventos(info);
            std::cout << "\nSeleccione indice de evento (1 a " << info.size() << "): ";
            int indice = InputUtils::leerEnteroEnRango(1, static_cast<int>(info.size()));
            const auto& evento = info[static_cast<size_t>(indice - 1)];
            InventarioInfo inv = inventarioMap[evento.id];
            if (totalDisponibles(inv) == 0) {
                inv = InventarioInfo{40, 20, 10};
            }
            std::cout << "Cupos objetivo para asignar: ";
            int objetivo = InputUtils::leerEnteroEnRango(1, totalDisponibles(inv));
            std::vector<std::string> tipos = {"General", "Tribuna", "Palco"};
            std::vector<int> seleccion(tipos.size(), 0);
            bool ok = backtrackAsignacion(objetivo, inv, 0, tipos, seleccion);
            if (!ok) {
                std::cout << "No se pudo asignar cupos exactos con backtracking.\n";
                continue;
            }
            std::cout << "\nAsignacion encontrada para " << evento.nombre << ":\n";
            for (size_t i = 0; i < tipos.size(); ++i) {
                std::cout << "- " << tipos[i] << ": " << seleccion[i] << "\n";
            }
        }
    }
}

} // namespace

void EstrategiasController::mostrarMenuEstrategias(LinkedList<Evento>& eventos,
                                                   LinkedList<InventarioEvento>& inventarios,
                                                   LinkedList<Usuario>& usuarios) {
    while (true) {
        std::cout << "\n=== MENU DE ESTRATEGIAS DE DISENO ===\n";
        std::cout << "[1] Programacion Exhaustiva\n";
        std::cout << "[2] Divide y Venceras\n";
        std::cout << "[3] Algoritmo Voraz\n";
        std::cout << "[4] Programacion Dinamica\n";
        std::cout << "[5] Backtracking\n";
        std::cout << "[0] Volver\n";
        std::cout << "Opcion: ";
        int opc = InputUtils::leerEnteroEnRango(0, 5);
        switch (opc) {
            case 1:
                menuProgramacionExhaustiva(eventos, inventarios, usuarios);
                break;
            case 2:
                menuDivideVenceras(eventos, inventarios);
                break;
            case 3:
                menuVoraz(eventos, inventarios);
                break;
            case 4:
                menuDinamica(eventos, inventarios);
                break;
            case 5:
                menuBacktracking(eventos, inventarios);
                break;
            case 0:
            default:
                return;
        }
    }
}
