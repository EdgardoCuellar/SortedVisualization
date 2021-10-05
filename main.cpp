#include <iostream>
#include "Screen.hpp"

int main(int argc, char* argv[]) {

    auto *screen = new Screen();
    screen->init("Sort visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WITDH, HEIGHT, false);

    screen->render();
    while (screen->running()){
        screen->handleEvents();
        screen->update();
    }

    screen->clean();

    return 0;
}
