#pragma once
#include <utility>

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    explicit Node(const T& d) : data(d), next(this), prev(this) {}
    explicit Node(T&& d) : data(std::move(d)), next(this), prev(this) {}
};
