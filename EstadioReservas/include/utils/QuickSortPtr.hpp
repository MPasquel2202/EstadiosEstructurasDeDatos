#pragma once
#include <vector>
#include <cstddef>

namespace QuickSortPtr {
    template<typename Ptr, typename Compare>
    void quickSortPtrRange(Ptr* left, Ptr* right, Compare cmp){
        if(left >= right) return;
        Ptr* i = left;
        Ptr* j = right;
        Ptr pivot = *(left + (right - left) / 2);
        while(i <= j){
            while(cmp(*i, pivot)) ++i;
            while(cmp(pivot, *j)) --j;
            if(i <= j){
                Ptr tmp = *i; *i = *j; *j = tmp;
                ++i; --j;
            }
        }
        if(left < j) quickSortPtrRange(left, j, cmp);
        if(i < right) quickSortPtrRange(i, right, cmp);
    }

    template<typename Ptr, typename Compare>
    void quickSort(std::vector<Ptr>& a, Compare cmp){
        if(a.empty()) return;
        quickSortPtrRange<Ptr>(a.data(), a.data() + (ptrdiff_t)a.size() - 1, cmp);
    }

    // Sobrecarga que acepta un rango de punteros [left, right]
    template<typename Ptr, typename Compare>
    void quickSort(Ptr* left, Ptr* right, Compare cmp){
        if(!left || !right) return;
        if(left > right) return;
        quickSortPtrRange<Ptr>(left, right, cmp);
    }
}
