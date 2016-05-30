//
// Created by krzysztof on 25.05.16.
//

#ifndef NCURSES_CLIENT_H
#define NCURSES_CLIENT_H

#include <pthread.h>
#include <ncurses.h>

class Client {
public:
    char color = 0;
    unsigned fuel_tank = 50;

    Client(char color, unsigned fuel_tank);
    void init();
    void tank();
    void pay();


};


#endif //NCURSES_CLIENT_H
