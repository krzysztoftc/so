//
// Created by krzysztof on 25.05.16.
//

#ifndef NCURSES_STATION_H
#define NCURSES_STATION_H

#include <list>
#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <fstream>
#include <cerrno>
#include <cstdio>

#include "Client.h"
#include "place.h"

class Station {
    std::list <Client *> clients;

    mutable pthread_mutex_t mutex_queues = PTHREAD_MUTEX_INITIALIZER;
    mutable pthread_mutex_t mutex_refresh = PTHREAD_MUTEX_INITIALIZER;

    int rows;
    int cols;

    pthread_t th_new_clients = 0;
    pthread_t th_refresh = 0;
    pthread_t th_cistern = 0;

    static void* thread_new_clients(void *arg);
    static void* thread_refresh(void *arg);
    static void* thread_cistern(void *arg);

public:
    static int pump1;
    static int pump2;
    static int pump3;

    Station();
    void new_client();
    void refresh_view();
    ~Station();
};


#endif //NCURSES_STATION_H
