#pragma once
#include <functional>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include "ds/Node.hpp"

template <typename T>
class LinkedList {
private:
    Node<T>* head{nullptr};
    std::size_t n{0};

public:
    LinkedList() = default;
    ~LinkedList(){ clear(); }

    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    LinkedList(LinkedList&& other) noexcept : head(other.head), n(other.n) {
        other.head = nullptr; other.n = 0;
    }
    LinkedList& operator=(LinkedList&& other) noexcept {
        if(this != &other){
            clear();
            head = other.head; n = other.n;
            other.head = nullptr; other.n = 0;
        }
        return *this;
    }

    bool empty() const { return n == 0; }
    std::size_t size() const { return n; }

    void clear(){
        if(!head) return;
        Node<T>* cur = head;
        for(std::size_t i=0;i<n;i++){
            Node<T>* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = nullptr; n = 0;
    }

    void push_back(const T& value){
        Node<T>* node = new Node<T>(value);
        if(!head){ head = node; n = 1; return; }
        Node<T>* tail = head->prev;
        tail->next = node; node->prev = tail;
        node->next = head; head->prev = node;
        ++n;
    }

    void push_back(T&& value){
        Node<T>* node = new Node<T>(std::move(value));
        if(!head){ head = node; n = 1; return; }
        Node<T>* tail = head->prev;
        tail->next = node; node->prev = tail;
        node->next = head; head->prev = node;
        ++n;
    }

    T* find(const std::function<bool(const T&)>& pred){
        if(!head) return nullptr;
        Node<T>* cur = head;
        for(std::size_t i=0;i<n;i++){
            if(pred(cur->data)) return &cur->data;
            cur = cur->next;
        }
        return nullptr;
    }

    const T* find(const std::function<bool(const T&)>& pred) const{
        if(!head) return nullptr;
        Node<T>* cur = head;
        for(std::size_t i=0;i<n;i++){
            if(pred(cur->data)) return &cur->data;
            cur = cur->next;
        }
        return nullptr;
    }

    bool remove_if(const std::function<bool(const T&)>& pred){
        if(!head) return false;
        Node<T>* cur = head;
        for(std::size_t i=0;i<n;i++){
            if(pred(cur->data)){
                if(n==1){ delete cur; head=nullptr; n=0; return true; }
                Node<T>* p = cur->prev; Node<T>* nx = cur->next;
                p->next = nx; nx->prev = p;
                if(cur==head) head = nx;
                delete cur; --n; return true;
            }
            cur = cur->next;
        }
        return false;
    }

    // NUEVO: elimina el primer elemento que cumpla el predicado y devuelve la data eliminada en 'out'
    bool remove_first(const std::function<bool(const T&)>& pred, T& out){
        if(!head) return false;
        Node<T>* cur = head;
        for(std::size_t i=0;i<n;i++){
            if(pred(cur->data)){
                out = std::move(cur->data);
                if(n==1){ delete cur; head=nullptr; n=0; return true; }
                Node<T>* p = cur->prev; Node<T>* nx = cur->next;
                p->next = nx; nx->prev = p;
                if(cur==head) head = nx;
                delete cur; --n; return true;
            }
            cur = cur->next;
        }
        return false;
    }

    void for_each(const std::function<void(T&)>& fn){
        if(!head) return;
        Node<T>* cur = head;
        for(std::size_t i=0;i<n;i++){ fn(cur->data); cur = cur->next; }
    }

    void for_each(const std::function<void(const T&)>& fn) const{
        if(!head) return;
        Node<T>* cur = head;
        for(std::size_t i=0;i<n;i++){ fn(cur->data); cur = cur->next; }
    }
};
