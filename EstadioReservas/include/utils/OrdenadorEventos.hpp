#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <iostream>
#include "../model/Evento.hpp"
#include "../model/InventarioEvento.hpp"
#include "../ds/LinkedList.hpp"

template<typename T>
class OrdenadorEventos {
private:
    std::vector<T*> eventos;
    std::unordered_map<std::string, InventarioEvento*> inventariosMap;

    int getAsientosDisponibles(const std::string& eventoId) {
        auto it = inventariosMap.find(eventoId);
        if (it != inventariosMap.end() && it->second != nullptr) {
            int general = it->second->capGeneral - it->second->occGeneral;
            int tribuna = it->second->capTribuna - it->second->occTribuna;
            int palco = it->second->capPalco - it->second->occPalco;
            return general + tribuna + palco;
        }
        return 0;
    }

    void merge(int left, int mid, int right, std::function<bool(T*, T*)> comparador) {
        std::vector<T*> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right) {
            if (comparador(eventos[i], eventos[j])) {
                temp[k++] = eventos[i++];
            } else {
                temp[k++] = eventos[j++];
            }
        }

        while (i <= mid) temp[k++] = eventos[i++];
        while (j <= right) temp[k++] = eventos[j++];

        for (size_t x = 0; x < temp.size(); ++x) {
            eventos[left + x] = temp[x];
        }
    }

    void mergesort(int left, int right, std::function<bool(T*, T*)> comparador) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergesort(left, mid, comparador);
            mergesort(mid + 1, right, comparador);
            merge(left, mid, right, comparador);
        }
    }

    int partition(int low, int high, std::function<bool(T*, T*)> comparador) {
        T* pivot = eventos[high];
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (comparador(eventos[j], pivot)) {
                i++;
                std::swap(eventos[i], eventos[j]);
            }
        }
        std::swap(eventos[i + 1], eventos[high]);
        return i + 1;
    }

    void quicksort(int low, int high, std::function<bool(T*, T*)> comparador) {
        if (low < high) {
            int pi = partition(low, high, comparador);
            quicksort(low, pi - 1, comparador);
            quicksort(pi + 1, high, comparador);
        }
    }

public:
    void cargarDatos(std::vector<T*>& eventosVec, std::unordered_map<std::string, InventarioEvento*>& invMap) {
        eventos = eventosVec;
        inventariosMap = invMap;
    }

    // 1. Selección
    void seleccion(std::function<bool(T*, T*)> comparador) {
        for (size_t i = 0; i < eventos.size() - 1; ++i) {
            size_t min_idx = i;
            for (size_t j = i + 1; j < eventos.size(); ++j) {
                if (comparador(eventos[j], eventos[min_idx])) {
                    min_idx = j;
                }
            }
            if (min_idx != i) {
                std::swap(eventos[i], eventos[min_idx]);
            }
        }
    }

    // 2. Inserción
    void insercion(std::function<bool(T*, T*)> comparador) {
        for (size_t i = 1; i < eventos.size(); ++i) {
            T* key = eventos[i];
            int j = i - 1;
            
            while (j >= 0 && comparador(key, eventos[j])) {
                eventos[j + 1] = eventos[j];
                j--;
            }
            eventos[j + 1] = key;
        }
    }

    // 3. Burbuja
    void burbuja(std::function<bool(T*, T*)> comparador) {
        for (size_t i = 0; i < eventos.size() - 1; ++i) {
            for (size_t j = 0; j < eventos.size() - i - 1; ++j) {
                if (comparador(eventos[j + 1], eventos[j])) {
                    std::swap(eventos[j], eventos[j + 1]);
                }
            }
        }
    }

    // 4. Shell
    void shell(std::function<bool(T*, T*)> comparador) {
        int n = eventos.size();
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; ++i) {
                T* temp = eventos[i];
                int j;
                for (j = i; j >= gap && comparador(temp, eventos[j - gap]); j -= gap) {
                    eventos[j] = eventos[j - gap];
                }
                eventos[j] = temp;
            }
        }
    }

    // 5. Heapsort
    void heapsort(std::function<bool(T*, T*)> comparador) {
        auto heapComp = [comparador](T* a, T* b) { return !comparador(a, b); };
        std::make_heap(eventos.begin(), eventos.end(), heapComp);
        
        for (auto it = eventos.end(); it != eventos.begin(); --it) {
            std::pop_heap(eventos.begin(), it, heapComp);
        }
    }

    // 6. Mergesort
    void mergesort(std::function<bool(T*, T*)> comparador) {
        if (eventos.empty()) return;
        mergesort(0, eventos.size() - 1, comparador);
    }

    // 7. Quicksort
    void quicksort(std::function<bool(T*, T*)> comparador) {
        if (eventos.empty()) return;
        quicksort(0, eventos.size() - 1, comparador);
    }

    // 8. Radixsort (simplificado para asientos disponibles)
    void radixsort(bool ascendente = true) {
        if (eventos.empty()) return;
        
        // Ordenar por asientos disponibles usando sort
        std::sort(eventos.begin(), eventos.end(), 
            [ascendente, this](T* a, T* b) {
                int asientosA = this->getAsientosDisponibles(a->id);
                int asientosB = this->getAsientosDisponibles(b->id);
                return ascendente ? asientosA < asientosB : asientosA > asientosB;
            });
    }

    // 9. Binsort (Bucket Sort simplificado)
    void binsort(bool ascendente = true) {
        if (eventos.empty()) return;
        
        // Ordenar por asientos disponibles usando sort
        std::sort(eventos.begin(), eventos.end(),
            [ascendente, this](T* a, T* b) {
                int asientosA = this->getAsientosDisponibles(a->id);
                int asientosB = this->getAsientosDisponibles(b->id);
                return ascendente ? asientosA < asientosB : asientosA > asientosB;
            });
    }

    void mostrarEventosConInventarios() {
        for (auto* evento : eventos) {
            int asientosDisp = getAsientosDisponibles(evento->id);
            std::cout << "• " << evento->nombre 
                      << " | Fecha: " << evento->fecha
                      << " | Asientos disponibles: " << asientosDisp << std::endl;
        }
    }

    std::vector<T*> obtenerEventosOrdenados() const {
        return eventos;
    }
};