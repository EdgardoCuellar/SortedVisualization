#ifndef SDL2_TEST_SCREEN_HPP
#define SDL2_TEST_SCREEN_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <array>
#include "Sorted.h"
#include <random>
#include <cmath>

// OPTION
int const WITDH = 1000;
int const HEIGHT = 800;
int const COLORS[5][3] = {{30,30,30}, {200,200,200}, {98, 0, 234}, {0, 200, 83}};
int const SPEED = 20;
int const WITDH_LINE = (WITDH/NB)-1;

class Screen{
    // BASICS
    bool isRunning{};
    SDL_Window *window{};
    SDL_Renderer *renderer{};

    // SPECIAL
    bool isStart = false;
    Sorted sort;
    std::array<int, NB> lc{};

public:
    Screen () noexcept;
    ~Screen() noexcept;

    void init(const char* title, int xpos, int ypos, int wigth, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    void displayBase() noexcept;
    void createBase() noexcept;
    void display(int i, int j) noexcept;
    inline void startSort() noexcept {isStart = true;}
    void check();

    // SORT LIST
    void bubbleSort() noexcept;

    void quicksort(int start,int end) noexcept; // FROM https://www.geeksforgeeks.org/
    int partition(int start,int end);

    void mergeSort(int l,int r); // FROM https://www.geeksforgeeks.org/
    void merge(int l, int m, int r);

    void insertSort() noexcept;

    void heapSort(int n); // FROM https://www.geeksforgeeks.org/
    void heapify(int n, int i);

    void bongoSort() noexcept; // lmao
    // Simple func
    bool running() const {return isRunning; };
};

#endif //SDL2_TEST_SCREEN_HPP
