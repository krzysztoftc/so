#include <iostream>
#include <ncurses.h>
#include <list>
#include <ctime>

#include "src/Client.h"
#include "src/Station.h"


using namespace std;

int cols = 0;
int rows = 0;

int main() {
    srand(time(NULL));

    //initscr();
    Station station;

    getch();

    //endwin();

    return 0;
}