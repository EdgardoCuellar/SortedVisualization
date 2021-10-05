#ifndef SORTEVISUALIZATION_SORTED_H
#define SORTEVISUALIZATION_SORTED_H

#include <algorithm>
#include <array>
#include <iostream>

int const NB = 100;

class Sorted {

    std::array<int, NB> lt;

public:
    Sorted() noexcept;

    bool checkSort(int where) noexcept;

    int getI(int where);
    inline void setI(int k, int i) noexcept {lt[k] = i;}
    void swap(int i, int j);
    void display() noexcept;
    void unsort() noexcept;

    ~Sorted() noexcept = default;
};


#endif //SORTEVISUALIZATION_SORTED_H
