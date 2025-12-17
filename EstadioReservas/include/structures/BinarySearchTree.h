#pragma once
#include <cstddef>
#include <functional>
#include <string>
#include <utility>

// Árbol binario de búsqueda simple que almacena claves y punteros sin ser dueño
// de la memoria de los elementos almacenados.
template <typename T>
class BinarySearchTree {
public:
    class Node {
    public:
        std::string key;
        T* payload;
        Node* left;
        Node* right;

        Node(std::string k, T* p) : key(std::move(k)), payload(p), left(nullptr), right(nullptr) {}
    };

    BinarySearchTree() = default;
    ~BinarySearchTree(){ clear(); }

    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    BinarySearchTree(BinarySearchTree&& other) noexcept : root(other.root), n(other.n) {
        other.root = nullptr; other.n = 0;
    }

    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
        if(this != &other){
            clear();
            root = other.root; n = other.n;
            other.root = nullptr; other.n = 0;
        }
        return *this;
    }

    bool empty() const { return root == nullptr; }
    std::size_t size() const { return n; }

    bool insert(const std::string& key, T* payload){
        return insert(root, key, payload);
    }

    T* find(const std::string& key){
        return const_cast<T*>(static_cast<const BinarySearchTree<T>*>(this)->find(key));
    }

    const T* find(const std::string& key) const{
        Node* cur = root;
        while(cur){
            if(key == cur->key) return cur->payload;
            cur = key < cur->key ? cur->left : cur->right;
        }
        return nullptr;
    }

    bool remove(const std::string& key){
        return remove(root, key);
    }

    void inOrder(const std::function<void(const Node&)>& fn) const{
        inOrder(root, fn);
    }

    void clear(){
        clear(root);
        root = nullptr; n = 0;
    }

private:
    Node* root{nullptr};
    std::size_t n{0};

    static void clear(Node* node){
        if(!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    bool insert(Node*& node, const std::string& key, T* payload){
        if(!node){
            node = new Node(key, payload);
            ++n;
            return true;
        }
        if(key == node->key){
            node->payload = payload;
            return false;
        }
        if(key < node->key) return insert(node->left, key, payload);
        return insert(node->right, key, payload);
    }

    static Node* findMin(Node* node){
        while(node && node->left) node = node->left;
        return node;
    }

    bool remove(Node*& node, const std::string& key){
        if(!node) return false;
        if(key < node->key) return remove(node->left, key);
        if(key > node->key) return remove(node->right, key);

        // encontrado
        if(!node->left && !node->right){
            delete node; node = nullptr; --n; return true;
        }
        if(!node->left || !node->right){
            Node* child = node->left ? node->left : node->right;
            delete node; node = child; --n; return true;
        }

        Node* succ = findMin(node->right);
        node->key = succ->key;
        node->payload = succ->payload;
        return remove(node->right, succ->key);
    }

    static void inOrder(Node* node, const std::function<void(const Node&)>& fn){
        if(!node) return;
        inOrder(node->left, fn);
        fn(*node);
        inOrder(node->right, fn);
    }
};

