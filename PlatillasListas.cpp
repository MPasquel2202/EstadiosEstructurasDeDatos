template <typename T>
class ListaSimple {
private:
    Nodo<T>* cabeza;

public:
    ListaSimple() : cabeza(nullptr) {}

    // Insertar al final
    void insertar(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        if (!cabeza) {
            cabeza = nuevo;
        } else {
            Nodo<T>* temp = cabeza;
            while (temp->siguiente)
                temp = temp->siguiente;
            temp->siguiente = nuevo;
        }
    }

    // Eliminar un nodo con cierto valor
    void eliminar(T valor) {
        if (!cabeza) return;

        // Si el valor está en el primer nodo
        if (cabeza->dato == valor) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            return;
        }

        // Buscar el nodo anterior al que queremos eliminar
        Nodo<T>* actual = cabeza;
        Nodo<T>* anterior = nullptr;

        while (actual && actual->dato != valor) {
            anterior = actual;
            actual = actual->siguiente;
        }

        if (actual) {
            anterior->siguiente = actual->siguiente;
            delete actual;
        } else {
            cout << "Elemento no encontrado\n";
        }
    }

    // Buscar un nodo
    Nodo<T>* buscar(T valor) {
        Nodo<T>* temp = cabeza;
        while (temp) {
            if (temp->dato == valor)
                return temp;
            temp = temp->siguiente;
        }
        return nullptr; // No encontrado
    }

    // Imprimir toda la lista
    void imprimir() {
        Nodo<T>* temp = cabeza;
        while (temp) {
            cout << temp->dato << " -> ";
            temp = temp->siguiente;
        }
        cout << "NULL\n";
    }

    // Destructor para liberar memoria
    ~ListaSimple() {
        Nodo<T>* temp;
        while (cabeza) {
            temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
};

