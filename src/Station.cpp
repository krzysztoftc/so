//
// Created by krzysztof on 25.05.16.
//

#include "Station.h"

using namespace std;

int Station::pump1 = 0;
int Station::pump2 = 0;
int Station::pump3 = 0;

Station::Station() {

    initscr();
    curs_set(0);
    //pthread_mutex_lock(&mutex_refresh);

    int status = pthread_create(&th_new_clients, NULL, Station::thread_new_clients, (void*)this);
    //if (status != 0) printw("error\n");
    status = pthread_create(&th_refresh, NULL,  Station::thread_refresh, (void*)this);
    if (status != 0) printw("error\n");
    //mvprintw(2,2,"started");
    //status = pthread_create(&th_cistern, NULL,  Station::thread_cistern, (void*)this);
    if (status != 0) mvprintw(2,2,"error");
    //mvprintw(3,0,"started");
    //refresh();
    //pthread_mutex_unlock(&mutex_refresh);
}

void Station::new_client() {

    pthread_mutex_lock(&mutex_queues);
    /*
    unsigned pump1_queue = pump1.size();
    unsigned pump2_queue = pump2.size();
    unsigned pump3_queue = pump3.size();

    if (pump1_queue <= pump2_queue && pump1_queue < pump3_queue) {
        pump1.push_back(new Client(1 + rand() % 6, 30 + rand() % 50, distr1));
    }

    else if (pump2_queue <= pump3_queue && pump2_queue < pump1_queue) {
        pump2.push_back(new Client(1 + rand() % 6, 30 + rand() % 50, distr2));
    }

    else {
        pump3.push_back(new Client(1 + rand() % 6, 30 + rand() % 50, distr3));
    }*/


    if (pump1 <= pump2 && pump1 < pump3) {
        pump1++;
        clients.push_back(new Client(1 + rand() % 6, 30 + rand() % 50, distr1));
    }

    else if (pump2 <= pump3 && pump2 < pump1) {
        pump2++;
        clients.push_back(new Client(1 + rand() % 6, 30 + rand() % 50, distr2));
    }

    else {
        pump3++;
        clients.push_back(new Client(1 + rand() % 6, 30 + rand() % 50, distr3));
    }
    pthread_mutex_unlock(&mutex_queues);

    //mvprintw(0,0,"New client: %d pump %d", Client::cnt++, clients.back()->position);
//    refresh();
//    pthread_mutex_unlock(&mutex_refresh);

}

void Station::refresh_view() {
//    pthread_mutex_lock(&mutex_refresh);
    getmaxyx(stdscr,rows,cols);
    start_color();

    init_pair(1,COLOR_WHITE, COLOR_RED);
    init_pair(2,COLOR_WHITE, COLOR_GREEN);
    init_pair(3,COLOR_WHITE, COLOR_YELLOW);
    init_pair(4,COLOR_WHITE, COLOR_BLUE);
    init_pair(5,COLOR_WHITE, COLOR_MAGENTA);
    init_pair(6,COLOR_WHITE, COLOR_CYAN);
    init_pair(7,COLOR_WHITE, COLOR_BLACK);
    init_pair(8,COLOR_BLACK, COLOR_WHITE);

    attron(COLOR_PAIR(7));

    mvprintw(rows-3, 0, "Dystrybutor 1: ");
    mvprintw(rows-4, 0, "Dystrybutor 2: ");
    mvprintw(rows-5, 0, "Dystrybutor 3: ");

    mvprintw(rows-7, 0, "Kasa: ");
    mvprintw(rows-9, 0, "Paliwa w zbiorniku: %d", Client::fuel_state);
    mvprintw(rows-10,0, "Miejsce dla cysterny: ");

    int p[3];
    p[0]=p[1]=p[2] = 0;

    /*while(clients.front()->position == none)
        clients.pop_front();*/

    for(Client * client : clients){

        if (client -> position == cash){
            attron(COLOR_PAIR(client->color));
            mvprintw(rows-7, 7, "%02d", client -> id);
        }

        else if (client -> position > none  ){
            attron(COLOR_PAIR(client->color));
            mvprintw(rows-(client->position)-2, 15 + 4*p[client->position-1]++, "%02d", client -> id);
        }

    }

    attron(COLOR_PAIR(7));
    refresh();
//    pthread_mutex_unlock(&mutex_refresh);
}

void* Station::thread_new_clients(void *obj) {
    while (1) {
    ((Station *) obj)->new_client();

    usleep(600000);
    }
}

void* Station::thread_cistern(void *obj) {
    while (1) {
       // pthread_mutex_lock(&mutex_refresh);
        //mvprintw(1,0,"cistern1");
       // pthread_mutex_unlock(&mutex_refresh);
        pthread_mutex_lock(&Client::mutex_fuel);
        Client::fuel_state += 100;
        pthread_cond_broadcast(&Client::empty);
        pthread_mutex_unlock(&Client::mutex_fuel);
//        pthread_mutex_lock(&mutex_refresh);
//        mvprintw(1,0,"cistern2");
//        pthread_mutex_unlock(&mutex_refresh);
        usleep(600000);
    }
}

void* Station::thread_refresh(void *obj){
    while (1) {
        ((Station *) obj)->refresh_view();
        usleep(10000);
    }
}


Station::~Station(){
    /*
    for(Client * client : pump1) delete(client);
    for(Client * client : pump2) delete(client);
    for(Client * client : pump3) delete(client);
     */

    for(Client * client : clients) {
        delete(client);
    }

    pthread_join(th_new_clients, NULL);
    pthread_join(th_refresh, NULL);
    pthread_join(th_cistern, NULL);


    endwin();
}

