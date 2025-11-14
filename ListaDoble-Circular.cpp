#include <iostream>
using namespace std;

// -----------------------------
// LISTA DOBLEMENTE CIRCULAR
// -----------------------------
struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo* anterior;
};

// Inserta al final
void insertarCircular(Nodo*& cabeza, int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;

    if (cabeza == nullptr) {
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
        cabeza = nuevo;
    } else {
        Nodo* ultimo = cabeza->anterior;
        nuevo->siguiente = cabeza;
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
        cabeza->anterior = nuevo;
    }
}

// Mostrar hacia adelante
void mostrarAdelante(Nodo* cabeza) {
    if (cabeza == nullptr) return;
    Nodo* actual = cabeza;
    do {
        cout << actual->dato << " <-> ";
        actual = actual->siguiente;
    } while (actual != cabeza);
    cout << "(vuelve al inicio)" << endl;
}

// Mostrar hacia atrás
void mostrarAtras(Nodo* cabeza) {
    if (cabeza == nullptr) return;
    Nodo* actual = cabeza->anterior;
    Nodo* inicio = actual;
    do {
        cout << actual->dato << " <-> ";
        actual = actual->anterior;
    } while (actual != inicio);
    cout << "(vuelve al final)" << endl;
}

// -----------------------------
// MAIN DEMOSTRATIVO
// -----------------------------
int main() {
    Nodo* listaCircular = nullptr;

    insertarCircular(listaCircular, 10);
    insertarCircular(listaCircular, 20);
    insertarCircular(listaCircular, 30);

    cout << "=== RECORRIDO ADELANTE ===" << endl;
    mostrarAdelante(listaCircular);

    cout << "\n=== RECORRIDO ATRAS ===" << endl;
    mostrarAtras(listaCircular);

    return 0;
}
