#include <chrono>
#include <thread>
#include "Screen.hpp"

using namespace std;

Screen::Screen() noexcept = default;

Screen::~Screen() noexcept = default;

void Screen::init(const char *title, int xpos, int ypos, int wigth, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        cout << "All is init" << endl;

        window = SDL_CreateWindow(title, xpos, ypos, wigth, height, flags);
        if (window){
            cout << "Window created" << endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer){
            SDL_SetRenderDrawColor(renderer, 33, 33, 33, 255);
            cout << "Renderer create" << endl;
        }
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        isRunning = true;
    } else{
        isRunning = false;
    }
    createBase();
    cout << "Nb : " << NB << endl;
}

void Screen::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_SPACE:
                    startSort();
                    break;
            }
    }
}
void Screen::update(){
    if (isStart){
        sort.display();

        // SORT TYPE
        //bubbleSort(); // Lent avec bcp d'elem, speed = 10 ok pour NB = 100
        quicksort(0, NB-1); // tres rapide, speed = 40 ok pour NB = 100
        //mergeSort(0, NB-1); // tres rapide(mais visuelement lent), speed = 25 ok pour NB = 100
        //insertSort(); // Lent avec bcp d'elem, speed = 10 ok pour NB = 100
        //heapSort(NB); // moyen fast, speed = 25 ok pour NB = 100
        //bongoSort(); // infinit, hehe NB_MAX = 15

        sort.display();
        check();
        isStart = false;
    }
}

void Screen::render(){
    // Background
    SDL_SetRenderDrawColor(renderer, COLORS[0][0], COLORS[0][1], COLORS[0][2], 255);
    SDL_RenderClear(renderer);
    displayBase();
    // Display all point
    SDL_RenderPresent(renderer);
}

void Screen::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "All clean up" << endl;
}

void Screen::createBase() noexcept {
    sort = Sorted();
    for (size_t i = 0; i < NB; ++i) {
        lc[i] = 1;
    }
}

void Screen::displayBase() noexcept {
    for (int i = 0; i < NB; ++i) {
        SDL_SetRenderDrawColor(renderer, COLORS[lc[i]][0], COLORS[lc[i]][1], COLORS[lc[i]][2], 255);
        int tmpH = sort.getI(i)*(HEIGHT/(NB+1));
        SDL_Rect tmp;
        tmp.x = i * (WITDH_LINE + 1);
        tmp.y = HEIGHT-tmpH;
        tmp.w = WITDH_LINE;
        tmp.h = tmpH;
        SDL_RenderFillRect(renderer, &tmp);
    }
}

void Screen::check() {
    for (int i = 0; i < NB; ++i) {
        if (sort.checkSort(i))
            lc[i] = 3;
        else{
            throw domain_error("Badly sorted list");
        }
        render();
        std::chrono::milliseconds timespan(SPEED/3); // or whatever
        std::this_thread::sleep_for(timespan);
    }
}

void Screen::display(int i, int j) noexcept {
    lc[i] = 2;
    lc[j] = 2;
    render();
    std::chrono::milliseconds timespan(SPEED); // or whatever
    std::this_thread::sleep_for(timespan);
    lc[i] = 1;
    lc[j] = 1;
}

/***********************************/
/**       SORT ALGORITHM          **/
/***********************************/
void Screen::bubbleSort() noexcept {
    for (int i = 0; i < NB-1; ++i) {
        int min = sort.getI(i);
        for (int j = i+1; j < NB; ++j) {
            if (sort.getI(j) < min){
                min = sort.getI(j);
                sort.swap(i, j);
                display(i ,j);
            }
        }
    }
}

void Screen::quicksort(int start,int end) noexcept {
    if(start<end){
        int P_index=partition(start,end);
        quicksort(start,P_index-1);
        quicksort(P_index+1,end);
    }
}
int Screen::partition(int start,int end){
    int pivot=sort.getI(end);
    int P_index=start;
    int i;
    for(i=start;i<end;i++){
        if(sort.getI(i)<=pivot){
            sort.swap(i, P_index);
            display(i ,P_index);
            P_index++;
        }
    }
    // Swap pivot et index
    sort.swap(end, P_index);
    return P_index;
}

void Screen::mergeSort(int l,int r){
    if(l>=r){
        return;//returns recursively
    }
    int m = (l+r-1)/2;
    mergeSort(l,m);
    mergeSort(m+1,r);
    merge(l,m,r);
}
void Screen::merge(int l, int m, int r){
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = sort.getI(l + i);
    for (int j = 0; j < n2; j++)
        R[j] = sort.getI(m + 1 + j);
    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            sort.setI(k, L[i]);
            display(k, L[i]);
            i++;
        }
        else {
            sort.setI(k, R[j]);
            display(k, R[j]);
            j++;
        }
        k++;
    }
    while (i < n1) {
        sort.setI(k, L[i]);
        display(k, L[i]);
        i++;
        k++;
    }
    while (j < n2) {
        sort.setI(k, R[j]);
        display(k, R[j]);
        j++;
        k++;
    }
}

void Screen::insertSort() noexcept {
    for (int i = 1; i < NB; ++i) {
        int j = i;
        while (j > 0 && sort.getI(j-1) > sort.getI(j)){
            sort.swap(j, j-1);
            display(j, j-1);
            --j;
        }
    }
}

void Screen::heapSort(int n){
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(n, i);

    for (int i = n - 1; i >= 0; i--) {
        sort.swap(0, i);
        display(0, i);
        heapify(i, 0);
    }
}
void Screen::heapify(int n, int i){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && sort.getI(l) > sort.getI(largest))
        largest = l;
    if (r < n && sort.getI(r) > sort.getI(largest))
        largest = r;
    if (largest != i) {
        sort.swap(i, largest);
        display(i, largest);
        heapify(n, largest);
    }
}

void Screen::bongoSort() noexcept {
    bool work = false;
    while (!work){
        sort.unsort();
        work = true;
        for (int i = 0; i < NB; ++i) {
            if (! sort.checkSort(i))
                work = false;
        }
        render();
        std::chrono::milliseconds timespan(250); // or whatever
        std::this_thread::sleep_for(timespan);
    }
}







