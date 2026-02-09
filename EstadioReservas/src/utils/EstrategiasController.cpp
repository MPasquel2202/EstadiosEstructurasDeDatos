#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "utils/EstrategiasController.hpp"
#include "utils/InputUtils.hpp"

namespace {

class EventoInfo {
public:
    EventoInfo(std::string id,
               std::string nombre,
               Fecha fecha,
               int cuposDisponibles)
        : id(std::move(id)),
          nombre(std::move(nombre)),
          fecha(std::move(fecha)),
          cuposDisponibles(cuposDisponibles) {}

    EventoInfo() = default;

    std::string id;
    std::string nombre;
    Fecha fecha;
    int cuposDisponibles{0};
};

class InventarioInfo {
public:
    InventarioInfo(int dispGeneral, int dispTribuna, int dispPalco)
        : dispGeneral(dispGeneral),
          dispTribuna(dispTribuna),
          dispPalco(dispPalco) {}

    InventarioInfo() = default;

    int dispGeneral{0};
    int dispTribuna{0};
    int dispPalco{0};
};

template <typename T>
class DynamicList {
public:
    DynamicList() = default;

    explicit DynamicList(size_t capacidad) {
        reserve(capacidad);
    }

    DynamicList(const DynamicList& other) {
        reserve(other.size_);
        for (size_t i = 0; i < other.size_; ++i) {
            data_[i] = other.data_[i];
        }
        size_ = other.size_;
    }

    DynamicList& operator=(const DynamicList& other) {
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        reserve(other.size_);
        for (size_t i = 0; i < other.size_; ++i) {
            data_[i] = other.data_[i];
        }
        size_ = other.size_;
        return *this;
    }

    ~DynamicList() {
        delete[] data_;
    }

    void reserve(size_t capacidad) {
        if (capacidad <= capacity_) {
            return;
        }
        auto* nuevo = new T[capacidad];
        for (size_t i = 0; i < size_; ++i) {
            nuevo[i] = data_[i];
        }
        delete[] data_;
        data_ = nuevo;
        capacity_ = capacidad;
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 4 : capacity_ * 2);
        }
        data_[size_++] = value;
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    void remove_at(size_t index) {
        if (index >= size_) {
            return;
        }
        for (size_t i = index + 1; i < size_; ++i) {
            data_[i - 1] = data_[i];
        }
        --size_;
    }

    void clear() {
        size_ = 0;
    }

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    T* data() {
        return data_;
    }

    const T* data() const {
        return data_;
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

private:
    T* data_{nullptr};
    size_t size_{0};
    size_t capacity_{0};
};

struct EventoInfoList {
    std::unique_ptr<EventoInfo[]> data;
    size_t size{0};
};

struct NombreList {
    std::unique_ptr<std::string[]> data;
    size_t size{0};
};

std::string fechaIso(const Fecha& f) {
    return f.iso();
}

EventoInfoList cargarEventosConCupos(const LinkedList<Evento>& eventos,
                                    const LinkedList<InventarioEvento>& inventarios) {
    std::unordered_map<std::string, InventarioEvento> inventariosMap;
    inventarios.for_each([&](const InventarioEvento& inv) {
        inventariosMap[inv.eventoId] = inv;
    });

    auto totalDisponibles = [](const InventarioInfo& inv) {
        return inv.dispGeneral + inv.dispTribuna + inv.dispPalco;
    };

    size_t total = eventos.size();
    EventoInfoList infos;
    if (total > 0) {
        infos.data = std::make_unique<EventoInfo[]>(total);
        infos.size = total;
        size_t idx = 0;
        eventos.for_each([&](const Evento& e) {
            auto it = inventariosMap.find(e.id);
            InventarioInfo inv;
            if (it != inventariosMap.end()) {
                inv.dispGeneral = it->second.capGeneral - it->second.occGeneral;
                inv.dispTribuna = it->second.capTribuna - it->second.occTribuna;
                inv.dispPalco = it->second.capPalco - it->second.occPalco;
            }
            infos.data[idx++] = EventoInfo(e.id, e.nombre, e.fecha, totalDisponibles(inv));
        });
        return infos;
    }

    infos.size = 5;
    infos.data = std::make_unique<EventoInfo[]>(infos.size);
    infos.data[0] = EventoInfo("EV-EX-01", "Final Nacional", Fecha{2024, 9, 14}, 320);
    infos.data[1] = EventoInfo("EV-EX-02", "Clasico Universitario", Fecha{2024, 10, 5}, 180);
    infos.data[2] = EventoInfo("EV-EX-03", "Festival Rock", Fecha{2024, 10, 26}, 240);
    infos.data[3] = EventoInfo("EV-EX-04", "Concierto Sinfonico", Fecha{2024, 11, 9}, 150);
    infos.data[4] = EventoInfo("EV-EX-05", "Torneo Juvenil", Fecha{2024, 12, 1}, 90);
    return infos;
}

NombreList cargarNombresUsuarios(const LinkedList<Usuario>& usuarios) {
    size_t total = usuarios.size();
    NombreList nombres;
    if (total > 0) {
        nombres.data = std::make_unique<std::string[]>(total);
        nombres.size = total;
        size_t idx = 0;
        usuarios.for_each([&](const Usuario& u) {
            nombres.data[idx++] = u.nombre;
        });
        return nombres;
    }

    nombres.size = 5;
    nombres.data = std::make_unique<std::string[]>(nombres.size);
    nombres.data[0] = "Marlon Pasquel";
    nombres.data[1] = "Brandon Pazmino";
    nombres.data[2] = "Lucia Ramos";
    nombres.data[3] = "Karla N.";
    nombres.data[4] = "Alfonso M.";
    return nombres;
}

std::unordered_map<std::string, std::unique_ptr<InventarioInfo>> cargarInventarios(
    const LinkedList<InventarioEvento>& inventarios) {
    std::unordered_map<std::string, std::unique_ptr<InventarioInfo>> map;
    inventarios.for_each([&](const InventarioEvento& inv) {
        map[inv.eventoId] = std::make_unique<InventarioInfo>(
            inv.capGeneral - inv.occGeneral,
            inv.capTribuna - inv.occTribuna,
            inv.capPalco - inv.occPalco);
    });
    return map;
}

void imprimirEventos(const EventoInfo* const* eventos, size_t total) {
    for (size_t i = 0; i < total; ++i) {
        const auto* e = eventos[i];
        std::cout << "• [" << e->id << "] " << e->nombre << " | "
                  << fechaIso(e->fecha) << " | cupos: " << e->cuposDisponibles << "\n";
    }
}

DynamicList<const EventoInfo*> crearInfoRefs(const EventoInfoList& info) {
    DynamicList<const EventoInfo*> refs(info.size);
    for (size_t i = 0; i < info.size; ++i) {
        refs.push_back(&info.data[i]);
    }
    return refs;
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
            auto infoRefs = crearInfoRefs(info);
            std::cout << "\nEventos disponibles:\n";
            imprimirEventos(infoRefs.data(), infoRefs.size());
            std::cout << "\nCupos objetivo: ";
            int objetivo = InputUtils::leerEnteroEnRango(1, 2000);
            auto buscarPares = [&infoRefs](int target) {
                bool encontrado = false;
                for (size_t i = 0; i < infoRefs.size(); ++i) {
                    for (size_t j = i + 1; j < infoRefs.size(); ++j) {
                        int suma = infoRefs[i]->cuposDisponibles + infoRefs[j]->cuposDisponibles;
                        if (suma == target) {
                            std::cout << "-> " << infoRefs[i]->nombre << " + "
                                      << infoRefs[j]->nombre << " = " << suma << "\n";
                            encontrado = true;
                        }
                    }
                }
                return encontrado;
            };
            if (!buscarPares(objetivo)) {
                std::cout << "No se encontraron pares exactos para " << objetivo << ".\n";
            }
        } else {
            auto nombres = cargarNombresUsuarios(usuarios);
            std::cout << "\nUsuarios disponibles:\n";
            for (size_t i = 0; i < nombres.size; ++i) {
                std::cout << "• " << nombres.data[i] << "\n";
            }
            std::cout << "\nFragmento a buscar: ";
            std::string fragmento = InputUtils::leerLineaNoVacia(1);
            std::string fragmentoLower = fragmento;
            std::transform(fragmentoLower.begin(), fragmentoLower.end(), fragmentoLower.begin(), ::tolower);

            auto buscarCoincidencias = [&nombres](const std::string& queryLower) {
                bool encontrado = false;
                for (size_t i = 0; i < nombres.size; ++i) {
                    std::string nombreLower = nombres.data[i];
                    std::transform(nombreLower.begin(), nombreLower.end(), nombreLower.begin(), ::tolower);
                    if (nombreLower.find(queryLower) != std::string::npos) {
                        std::cout << "-> Coincidencia: " << nombres.data[i] << "\n";
                        encontrado = true;
                    }
                }
                return encontrado;
            };
            if (!buscarCoincidencias(fragmentoLower)) {
                std::cout << "No se encontraron coincidencias para \"" << fragmento << "\".\n";
            }
        }
    }
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
        auto infoRefs = crearInfoRefs(info);
        if (opc == 1) {
            DynamicList<const EventoInfo*> ordenados = infoRefs;
            std::sort(ordenados.data(), ordenados.data() + ordenados.size(),
                      [](const EventoInfo* a, const EventoInfo* b) {
                return a->nombre < b->nombre;
            });
            std::cout << "\nEventos ordenados por nombre:\n";
            imprimirEventos(ordenados.data(), ordenados.size());
            std::cout << "\nNombre exacto a buscar: ";
            std::string objetivo = InputUtils::leerLineaNoVacia(1);
            auto busquedaBinariaNombre = [&ordenados](const std::string& target) {
                int izquierda = 0;
                int derecha = static_cast<int>(ordenados.size()) - 1;
                while (izquierda <= derecha) {
                    int medio = izquierda + (derecha - izquierda) / 2;
                    if (ordenados[medio]->nombre == target) {
                        return medio;
                    }
                    if (ordenados[medio]->nombre < target) {
                        izquierda = medio + 1;
                    } else {
                        derecha = medio - 1;
                    }
                }
                return -1;
            };
            int indice = busquedaBinariaNombre(objetivo);
            if (indice >= 0) {
                std::cout << "Encontrado: " << ordenados[static_cast<size_t>(indice)]->nombre
                          << " en fecha " << fechaIso(ordenados[static_cast<size_t>(indice)]->fecha) << ".\n";
            } else {
                std::cout << "No se encontro el evento \"" << objetivo << "\".\n";
            }
        } else {
            if (infoRefs.size() < 2) {
                std::cout << "No hay suficientes eventos para dividir y mezclar.\n";
                continue;
            }
            size_t mitad = infoRefs.size() / 2;
            DynamicList<const EventoInfo*> izquierda(mitad);
            DynamicList<const EventoInfo*> derecha(infoRefs.size() - mitad);
            for (size_t i = 0; i < mitad; ++i) {
                izquierda.push_back(infoRefs[i]);
            }
            for (size_t i = mitad; i < infoRefs.size(); ++i) {
                derecha.push_back(infoRefs[i]);
            }
            auto cmpFecha = [](const EventoInfo* a, const EventoInfo* b) {
                return a->fecha < b->fecha;
            };
            std::sort(izquierda.data(), izquierda.data() + izquierda.size(), cmpFecha);
            std::sort(derecha.data(), derecha.data() + derecha.size(), cmpFecha);

            auto mergePorFecha = [&izquierda, &derecha, &cmpFecha]() {
                DynamicList<const EventoInfo*> fusion(izquierda.size() + derecha.size());
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
                return fusion;
            };
            auto fusion = mergePorFecha();
            std::cout << "\nResultado del merge por fecha:\n";
            imprimirEventos(fusion.data(), fusion.size());
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
        auto infoRefs = crearInfoRefs(info);
        if (opc == 1) {
            std::cout << "\nCantidad de eventos a sugerir: ";
            int k = InputUtils::leerEnteroEnRango(1, static_cast<int>(infoRefs.size()));
            auto seleccionarCercanos = [&infoRefs](int cantidad) {
                DynamicList<const EventoInfo*> seleccion(cantidad);
                DynamicList<const EventoInfo*> restantes = infoRefs;
                for (int i = 0; i < cantidad; ++i) {
                    size_t minIndex = 0;
                    for (size_t j = 1; j < restantes.size(); ++j) {
                        if (restantes[j]->fecha < restantes[minIndex]->fecha) {
                            minIndex = j;
                        }
                    }
                    seleccion.push_back(restantes[minIndex]);
                    restantes.remove_at(minIndex);
                }
                return seleccion;
            };
            auto seleccion = seleccionarCercanos(k);
            std::cout << "\nSeleccion greedy de eventos cercanos:\n";
            imprimirEventos(seleccion.data(), seleccion.size());
        } else {
            std::cout << "\nCupos objetivo: ";
            int objetivo = InputUtils::leerEnteroEnRango(1, 2000);
            auto seleccionarPorCupos = [&infoRefs](int target) {
                DynamicList<const EventoInfo*> ordenados = infoRefs;
                std::sort(ordenados.data(), ordenados.data() + ordenados.size(),
                          [](const EventoInfo* a, const EventoInfo* b) {
                    return a->cuposDisponibles > b->cuposDisponibles;
                });
                int acumulado = 0;
                DynamicList<const EventoInfo*> seleccion(ordenados.size());
                for (size_t i = 0; i < ordenados.size(); ++i) {
                    const auto* e = ordenados[i];
                    if (acumulado >= target) break;
                    if (e->cuposDisponibles == 0) continue;
                    seleccion.push_back(e);
                    acumulado += e->cuposDisponibles;
                }
                return std::make_pair(seleccion, acumulado);
            };
            auto resultado = seleccionarPorCupos(objetivo);
            if (resultado.first.empty()) {
                std::cout << "No hay cupos disponibles para cubrir el objetivo.\n";
                continue;
            }
            std::cout << "\nSeleccion greedy por cupos:\n";
            imprimirEventos(resultado.first.data(), resultado.first.size());
            std::cout << "Cupos acumulados: " << resultado.second << " (objetivo " << objetivo << ")\n";
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
            auto infoRefs = crearInfoRefs(info);
            std::cout << "\nEventos disponibles:\n";
            imprimirEventos(infoRefs.data(), infoRefs.size());
            std::cout << "\nLimite de cupos: ";
            int limite = InputUtils::leerEnteroEnRango(1, 2000);
            auto mejorCombinacion = [&infoRefs](int limiteCupos) {
                auto prevSum = std::make_unique<int[]>(static_cast<size_t>(limiteCupos) + 1);
                auto prevIdx = std::make_unique<int[]>(static_cast<size_t>(limiteCupos) + 1);
                auto dp = std::make_unique<bool[]>(static_cast<size_t>(limiteCupos) + 1);
                for (int i = 0; i <= limiteCupos; ++i) {
                    prevSum[i] = -1;
                    prevIdx[i] = -1;
                    dp[i] = false;
                }
                dp[0] = true;
                for (size_t idx = 0; idx < infoRefs.size(); ++idx) {
                    int peso = infoRefs[idx]->cuposDisponibles;
                    for (int s = limiteCupos - peso; s >= 0; --s) {
                        if (dp[s] && !dp[s + peso]) {
                            dp[s + peso] = true;
                            prevSum[s + peso] = s;
                            prevIdx[s + peso] = static_cast<int>(idx);
                        }
                    }
                }
                int mejor = 0;
                for (int s = limiteCupos; s >= 0; --s) {
                    if (dp[s]) {
                        mejor = s;
                        break;
                    }
                }
                DynamicList<const EventoInfo*> seleccion(infoRefs.size());
                int s = mejor;
                while (s > 0 && prevIdx[s] != -1) {
                    int idx = prevIdx[s];
                    seleccion.push_back(infoRefs[static_cast<size_t>(idx)]);
                    s = prevSum[s];
                }
                return std::make_pair(mejor, seleccion);
            };
            auto resultado = mejorCombinacion(limite);
            std::cout << "\nMejor total alcanzado: " << resultado.first << " cupos.\n";
            if (resultado.second.empty()) {
                std::cout << "No se encontraron combinaciones dentro del limite.\n";
            } else {
                std::cout << "Eventos seleccionados:\n";
                imprimirEventos(resultado.second.data(), resultado.second.size());
            }
        } else {
            auto contarFormas = []() {
                const int paquetes[] = {1, 3, 5, 7};
                const int totalPaquetes = 4;
                std::cout << "\nPaquetes ejemplo (cupos): 1, 3, 5, 7\n";
                std::cout << "Cupos objetivo: ";
                int objetivo = InputUtils::leerEnteroEnRango(1, 30);
                auto dp = std::make_unique<long long[]>(static_cast<size_t>(objetivo) + 1);
                for (int i = 0; i <= objetivo; ++i) {
                    dp[i] = 0;
                }
                dp[0] = 1;
                for (int i = 0; i < totalPaquetes; ++i) {
                    int paquete = paquetes[i];
                    for (int s = paquete; s <= objetivo; ++s) {
                        dp[s] += dp[s - paquete];
                    }
                }
                std::cout << "Formas de alcanzar " << objetivo << ": " << dp[objetivo] << "\n";
            };
            contarFormas();
        }
    }
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
        auto infoRefs = crearInfoRefs(info);
        if (opc == 1) {
            DynamicList<const EventoInfo*> mejor(infoRefs.size());
            DynamicList<const EventoInfo*> actual(infoRefs.size());
            std::unordered_map<std::string, bool> fechasUsadas;

            std::function<void(size_t)> dfs = [&](size_t idx) {
                if (idx == infoRefs.size()) {
                    if (actual.size() > mejor.size()) {
                        mejor = actual;
                    }
                    return;
                }
                dfs(idx + 1);
                std::string fecha = fechaIso(infoRefs[idx]->fecha);
                if (!fechasUsadas[fecha]) {
                    fechasUsadas[fecha] = true;
                    actual.push_back(infoRefs[idx]);
                    dfs(idx + 1);
                    actual.pop_back();
                    fechasUsadas[fecha] = false;
                }
            };
            dfs(0);
            std::cout << "\nAgenda maxima sin repetir fecha (" << mejor.size() << " eventos):\n";
            imprimirEventos(mejor.data(), mejor.size());
        } else {
            auto inventarioMap = cargarInventarios(inventarios);
            std::cout << "\nEventos disponibles:\n";
            imprimirEventos(infoRefs.data(), infoRefs.size());
            std::cout << "\nSeleccione indice de evento (1 a " << infoRefs.size() << "): ";
            int indice = InputUtils::leerEnteroEnRango(1, static_cast<int>(infoRefs.size()));
            const auto* evento = infoRefs[static_cast<size_t>(indice - 1)];
            const auto& invPtr = inventarioMap[evento->id];
            auto inv = std::make_unique<InventarioInfo>();
            if (invPtr) {
                *inv = *invPtr;
            }
            auto totalDisponibles = [](const InventarioInfo& invInfo) {
                return invInfo.dispGeneral + invInfo.dispTribuna + invInfo.dispPalco;
            };
            if (totalDisponibles(*inv) == 0) {
                inv = std::make_unique<InventarioInfo>(40, 20, 10);
            }
            std::cout << "Cupos objetivo para asignar: ";
            int objetivo = InputUtils::leerEnteroEnRango(1, totalDisponibles(*inv));
            const size_t tiposCount = 3;
            auto tipos = std::make_unique<std::string[]>(tiposCount);
            tipos[0] = "General";
            tipos[1] = "Tribuna";
            tipos[2] = "Palco";
            auto seleccion = std::make_unique<int[]>(tiposCount);
            for (size_t i = 0; i < tiposCount; ++i) {
                seleccion[i] = 0;
            }
            auto maxDisponible = [&inv, &tipos](size_t idx) {
                if (tipos[idx] == "General") return inv->dispGeneral;
                if (tipos[idx] == "Tribuna") return inv->dispTribuna;
                return inv->dispPalco;
            };
            std::function<bool(int, int)> backtrackAsignacion = [&](int objetivoCupos, int idx) {
                if (idx == static_cast<int>(tiposCount) - 1) {
                    int restante = objetivoCupos;
                    for (int i = 0; i < idx; ++i) {
                        restante -= seleccion[static_cast<size_t>(i)];
                    }
                    int maxDisp = maxDisponible(static_cast<size_t>(idx));
                    if (restante >= 0 && restante <= maxDisp) {
                        seleccion[static_cast<size_t>(idx)] = restante;
                        return true;
                    }
                    return false;
                }

                int maxDisp = maxDisponible(static_cast<size_t>(idx));
                for (int cantidad = 0; cantidad <= maxDisp; ++cantidad) {
                    seleccion[static_cast<size_t>(idx)] = cantidad;
                    int suma = 0;
                    for (int i = 0; i <= idx; ++i) {
                        suma += seleccion[static_cast<size_t>(i)];
                    }
                    if (suma > objetivoCupos) break;
                    if (backtrackAsignacion(objetivoCupos, idx + 1)) {
                        return true;
                    }
                }
                return false;
            };
            bool ok = backtrackAsignacion(objetivo, 0);
            if (!ok) {
                std::cout << "No se pudo asignar cupos exactos con backtracking.\n";
                continue;
            }
            std::cout << "\nAsignacion encontrada para " << evento->nombre << ":\n";
            for (size_t i = 0; i < tiposCount; ++i) {
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
