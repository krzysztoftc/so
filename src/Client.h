//
// Created by krzysztof on 25.05.16.
//

#ifndef NCURSES_CLIENT_H
#define NCURSES_CLIENT_H

#include <pthread.h>
#include <ncurses.h>
#include <unistd.h>

#include "mutex.h"
#include "place.h"
#include "Station.h"

//pthread_mutex_t mutex_distr1 = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t mutex_distr2 = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t mutex_distr3 = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t mutex_cash = PTHREAD_MUTEX_INITIALIZER;

class Client {

    static pthread_mutex_t mutex_cash;



    pthread_t th_tank;

public:

    Station *station;
    static pthread_mutex_t mutex_fuel;
    static pthread_cond_t empty;

    static int fuel_state;
    place position;

    char color = 0;
    unsigned fuel_tank = 50;
    unsigned id;


    static int cnt;

    Client(char color, unsigned fuel_tank, place position, Station *station);
    void init();
    static void* thread_tank(void *obj);
    void tank(Client *client);
    void pay();
    ~Client();

};


#endif //NCURSES_CLIENT_H
