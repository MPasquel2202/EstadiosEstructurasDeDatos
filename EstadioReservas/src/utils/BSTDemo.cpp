#include "utils/BSTDemo.hpp"
#include "structures/BinarySearchTree.h"
#include <iostream>
#include <string>

class DemoValor {
public:
    std::string nombre;
};

void ejecutarDemoBST(){
    BinarySearchTree<DemoValor> bst;

    DemoValor a{"Alpha"};
    DemoValor b{"Bravo"};
    DemoValor c{"Charlie"};

    bst.insert("2", &b);
    bst.insert("1", &a);
    bst.insert("3", &c);

    std::cout << "[BST Demo] Recorrido en orden: ";
    bst.inOrder([](const BinarySearchTree<DemoValor>::Node& n){
        std::cout << n.key << ":" << n.payload->nombre << " ";
    });
    std::cout << "\n";

    auto* encontrado = bst.find("2");
    if(encontrado){
        std::cout << "[BST Demo] Encontrado nodo 2 => " << encontrado->nombre << "\n";
    }
}

