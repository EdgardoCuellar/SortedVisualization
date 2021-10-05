#include "Sorted.h"

#include <random>

using namespace std;

Sorted::Sorted() noexcept {
    for (int i = 1; i < NB+1; ++i) {
        lt[i-1] = i;
    }
    unsort();
}

bool Sorted::checkSort(int where) noexcept {
    if (where+1 == lt[where]) return true;
    return false;
}

int Sorted::getI(int where) {
    return lt[where];
}

void Sorted::swap(int i, int j) {
    int tmp = lt[i];
    lt[i] = lt[j];
    lt[j] = tmp;
}

void Sorted::display() noexcept {
    for (int i = 0; i < NB; ++i) {
        cout << lt[i] << " ";
    }cout << endl;
}

void Sorted::unsort() noexcept {
    shuffle(lt.begin(), lt.end(), std::mt19937(std::random_device()()));
}
