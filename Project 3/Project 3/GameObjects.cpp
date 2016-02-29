//
//  GameObjects.cpp
//  Project 3
//
//  Created by Jin on 5/22/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#include "GameObjects.h"
GameObjects::GameObjects(string n, point2D p):_name(n),_position(p){}


point2D GameObjects::position() const{
    return _position;
}

void GameObjects::setPosition(point2D p){
    _position = p;
}

string GameObjects::name() const{
    return _name;
}

void GameObjects::setName(string n){
    _name = n;
}

char GameObjects::sym() const{
    return _sym;
}

void GameObjects::setSym(char s){
    _sym = s;
}


string GameObjects::description() const{
    return _description;
}

void GameObjects::setDescription(string d){
    _description = d;
}