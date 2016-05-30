//
// Created by krzysztof on 25.05.16.
//

#include "Client.h"

Client::Client(char color, unsigned fuel_tank) {
    this -> color = color;
    this -> fuel_tank = fuel_tank;
    printw("Client\n");
}