//
// Created by krzysztof on 25.05.16.
//

#include "Client.h"
#include "Station.h"

int Client::cnt = 0;

pthread_mutex_t Client::mutex_distr1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t Client::mutex_distr2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t Client::mutex_distr3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t Client::mutex_cash = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t Client::mutex_fuel = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t Client::empty = PTHREAD_COND_INITIALIZER;

int Client::fuel_state = 0;

Client::Client(char color, unsigned fuel_tank, place position) {
    this -> color = color;
    this -> fuel_tank = fuel_tank;
    this -> position = position;
    this -> id = Client::cnt++ % 100;
    pthread_create(&th_tank, NULL, Client::thread_tank, (void*)this);
}

void* Client::thread_tank(void *obj) {
    Client * client = (Client*) obj;
    client -> tank(client);
}

void Client::tank(Client *client) {
    int time_cash = 50000;
    int time_tank = 100000;
    if (client -> position == distr1){
        pthread_mutex_lock(&mutex_distr1);

        for (int i = 0; i < 20; i++){

            pthread_mutex_lock(&mutex_fuel);
//            while (fuel_state <= 0){
//                //mvprintw(2,0, "low fuel 1 %d", fuel_state);
//                pthread_cond_wait(&empty, &mutex_fuel);
//            }
            //mvprintw(2,0, "    fuel 1 %d", fuel_state);
            fuel_state--;
            pthread_mutex_unlock(&mutex_fuel);
            usleep(time_tank);
        }

        Station::pump1--;
        pthread_mutex_unlock(&mutex_distr1);

        pthread_mutex_lock(&mutex_cash);
        client ->  position = cash;
        usleep(time_cash);
        client -> position = none;
        pthread_mutex_unlock(&mutex_cash);


    }

    if (client -> position == distr2){
        pthread_mutex_lock(&mutex_distr2);

        for (int i = 0; i < 20; i++){
            pthread_mutex_lock(&mutex_fuel);
//            while (fuel_state <= 0){
//                //mvprintw(2,0, "low fuel 2 %d", fuel_state);
//                pthread_cond_wait(&empty, &mutex_fuel);
//            }
            //mvprintw(2,0, "    fuel 2 %d", fuel_state);
            fuel_state--;

            pthread_mutex_unlock(&mutex_fuel);
            usleep(time_tank);
        }
        Station::pump2--;
        pthread_mutex_unlock(&mutex_distr2);

        pthread_mutex_lock(&mutex_cash);
        client -> position = cash;
        usleep(time_cash);
        client -> position = none;
        pthread_mutex_unlock(&mutex_cash);




    }

    if (client -> position == distr3){
        pthread_mutex_lock(&mutex_distr3);

        for (int i = 0; i < 20; i++){
            pthread_mutex_lock(&mutex_fuel);
//            while (fuel_state <= 0){
//                //mvprintw(2,0, "low fuel 3 %d", fuel_state);
//                pthread_cond_wait(&empty, &mutex_fuel);
//            }
            //mvprintw(2,0, "    fuel 3 %d", fuel_state);
            fuel_state--;
            pthread_mutex_unlock(&mutex_fuel);
            usleep(time_tank);
        }
        Station::pump3--;
        pthread_mutex_unlock(&mutex_distr3);

        pthread_mutex_lock(&mutex_cash);
        client -> position = cash;
        usleep(time_cash);
        client -> position = none;
        pthread_mutex_unlock(&mutex_cash);



    }
}

Client::~Client() {
    pthread_join(th_tank,NULL);
}