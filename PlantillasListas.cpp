#include <iostream>
// Definimos la estructura de un nodo
struct Node {
    int data;
    Node* next;
};

// Función para insertar un nodo al principio de la lista
void insertAtHead(Node*& head, int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

// Función para insertar un nodo al final de la lista
void insertAtTail(Node*& head, int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Función para liberar memoria
void freeList(Node*& head) {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}

int main() {
    // La cabeza se inicializa como nullptr (lista vacía), esto es correcto y seguro.
    Node* head = nullptr;

    // Insertamos elementos en la lista
    insertAtHead(head, 3);
    insertAtTail(head, 5);
    insertAtHead(head, 2);
    insertAtTail(head, 7);

    // Lambda para mostrar la lista
    auto display = [](Node* head) {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr" << std::endl;
    };

    // Lambda para sumar los números impares
    auto sumaImpares = [](Node* head) -> int {
        int suma = 0;
        Node* actual = head;
        while (actual != nullptr) {
            if (actual->data % 2 == 1)
                suma += actual->data;
            actual = actual->next;
        }
        return suma;
    };

    // Mostramos la lista usando la lambda
    display(head);

    // Imprimimos la suma de los impares
    std::cout << "Suma de impares: " << sumaImpares(head) << std::endl;

    // Liberamos la memoria
    freeList(head);

    return 0;
}
