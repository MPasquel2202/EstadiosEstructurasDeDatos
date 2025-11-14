#include <iostream>
using namespace std;

// -----------------------------
// LISTA SIMPLEMENTE ENLAZADA
// -----------------------------
struct NodoSimple {
    int dato;
    NodoSimple* siguiente;
};

// Inserta al inicio
void insertarSimple(NodoSimple*& cabeza, int valor) {
    NodoSimple* nuevo = new NodoSimple();
    nuevo->dato = valor;
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

// Muestra la lista simple
void mostrarSimple(NodoSimple* cabeza) {
    NodoSimple* actual = cabeza;
    while (actual != nullptr) {
        cout << actual->dato << " -> ";
        actual = actual->siguiente;
    }
    cout << "NULL" << endl;
}

// -----------------------------
// LISTA DOBLEMENTE ENLAZADA
// -----------------------------
struct NodoDoble {
    int dato;
    NodoDoble* siguiente;
    NodoDoble* anterior;
};

// Inserta al inicio en la lista doble
void insertarDoble(NodoDoble*& cabeza, int valor) {
    NodoDoble* nuevo = new NodoDoble();
    nuevo->dato = valor;
    nuevo->siguiente = cabeza;
    nuevo->anterior = nullptr;

    if (cabeza != nullptr)
        cabeza->anterior = nuevo;

    cabeza = nuevo;
}

// Muestra la lista doble hacia adelante
void mostrarDobleAdelante(NodoDoble* cabeza) {
    NodoDoble* actual = cabeza;
    while (actual != nullptr) {
        cout << actual->dato << " <-> ";
        actual = actual->siguiente;
    }
    cout << "NULL" << endl;
}

// -----------------------------
// MAIN DEMOSTRATIVO
// -----------------------------
int main() {
    cout << "=== LISTA SIMPLE ===" << endl;
    NodoSimple* listaSimple = nullptr;
    insertarSimple(listaSimple, 10);
    insertarSimple(listaSimple, 20);
    insertarSimple(listaSimple, 30);
    mostrarSimple(listaSimple);

    cout << "\n=== LISTA DOBLE ===" << endl;
    NodoDoble* listaDoble = nullptr;
    insertarDoble(listaDoble, 10);
    insertarDoble(listaDoble, 20);
    insertarDoble(listaDoble, 30);
    mostrarDobleAdelante(listaDoble);

    return 0;
}
