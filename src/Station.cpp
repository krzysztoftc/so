//
// Created by krzysztof on 25.05.16.
//

#include "Station.h"

using namespace std;

Station::Station() {
    initscr();
    printw("chuj\n");
    int status = pthread_create(&th_new_clients, NULL, Station::thread_new_clients, (void*)this);
    if (status != 0) printw("error\n");
    status = pthread_create(&th_refresh, NULL,  Station::thread_refresh, (void*)this);
    if (status != 0) printw("error\n");
    printw("started\n");
}

void Station::new_client() {

    pthread_mutex_lock(&mutex_queues);
    unsigned pump1_queue = pump1.size();
    unsigned pump2_queue = pump2.size();
    unsigned pump3_queue = pump3.size();

    if (pump1_queue <= pump2_queue && pump1_queue < pump3_queue) {
        pump1.push_back(new Client(1 + rand() % 6, 30 + rand() % 50));
    }

    else if (pump2_queue <= pump3_queue && pump2_queue < pump1_queue) {
        pump2.push_back(new Client(1 + rand() % 6, 30 + rand() % 50));
    }

    else {
        pump3.push_back(new Client((1 + rand() % 6), (30 + rand() % 50)));
    }

    pthread_mutex_unlock(&mutex_queues);
}

void Station::refresh_view() {
    getmaxyx(stdscr,rows,cols);
    start_color();

    mvprintw(rows-3, 0, "Dystrybutor 1: ");
    mvprintw(rows-4, 0, "Dystrybutor 2: ");
    mvprintw(rows-5, 0, "Dystrybutor 3: ");

    mvprintw(rows-7, 0, "Kasa: ");
    mvprintw(rows-9, 0, "Paliwa w zbiorniku: ");
    mvprintw(rows-10,0, "Miejsce dla cysterny: ");

    init_pair(1,COLOR_RED, COLOR_BLACK);
    init_pair(2,COLOR_GREEN, COLOR_BLACK);
    init_pair(3,COLOR_YELLOW, COLOR_BLACK);
    init_pair(4,COLOR_BLUE, COLOR_BLACK);
    init_pair(5,COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6,COLOR_CYAN, COLOR_BLACK);
    init_pair(7,COLOR_WHITE, COLOR_BLACK);

    int i = 0;

    pthread_mutex_lock(&mutex_refresh);
    for(Client * client : pump1){
        attron(COLOR_PAIR(client->color));
        mvprintw(rows-3, 15 + i++, "@");
    }

    i = 0;
    for(Client * client : pump2){
        attron(COLOR_PAIR(client->color));
        mvprintw(rows-4, 15 + i++, "@");
    }

    i = 0;
    for(Client * client : pump3){
        attron(COLOR_PAIR(client->color));

        mvprintw(rows-5, 15 + i++, "@");
    }
    pthread_mutex_unlock(&mutex_refresh);
}

void* Station::thread_new_clients(void *obj){
    printw("new client\n");
    ((Station *)obj) -> new_client();
    printw("new client\n");
    usleep(50000);
}

void* Station::thread_refresh(void *obj){
    ((Station *)obj) -> refresh_view();
    usleep(100);
}


Station::~Station(){
    for(Client * client : pump1) delete(client);
    for(Client * client : pump2) delete(client);
    for(Client * client : pump3) delete(client);

    pthread_join(th_new_clients, NULL);
    pthread_join(th_refresh, NULL);

    endwin();
}

