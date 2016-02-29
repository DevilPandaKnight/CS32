//
//  Monsters.cpp
//  Project 3
//
//  Created by Jin on 5/23/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#include "Monsters.h"
#include "Scrolls.h"
#include "Dungeon.h"

Monsters::Monsters(string name):Actors(name){_itemToDrop = nullptr;_maxSmellDistance = 1;_dropProbability = 0;}

Monsters::~Monsters(){
    delete _itemToDrop;
}

void Monsters::moveToPlayer(Player* p){
    int dx = (p->position().x > position().x)? 1:-1;
    int dy = (p->position().y > position().y)? 1:-1;
    point2D moveX(position().x+dx,position().y);
    point2D moveY(position().x, position().y+dy);
    if (p->position() == moveX || p->position() == moveY) {
        attack(p);
        return;
    }
    if (position().x == p->position().x){
        moveToPoint(moveY);
        return;
    }
    if (position().y == p->position().y) {
        moveToPoint(moveX);
        return;
    }
    if (moveToPoint(moveX)) {
        return;
    }
    else{
        moveToPoint(moveY);
    }
}


GameObjects* Monsters::itemToDrop(){
    if (!_itemToDrop) {
        switch (rand()%5) {
            case 0:
                _itemToDrop = new Teleportation();
                break;
            case 1:
                _itemToDrop = new EnhanceArmor();
                break;
            case 2:
                _itemToDrop = new EnhanceHealth();
                break;
            case 3:
                _itemToDrop = new EnhanceDexterity();
                break;
            case 4:
                _itemToDrop = new Strength();
            default:
                break;
        }
    }
    return _itemToDrop;
}

void Monsters::setItemToDrop(GameObjects* i){
    if (_itemToDrop) {
        delete _itemToDrop;
    }
    _itemToDrop = i;
}

float Monsters::dropProbability() const{
    return _dropProbability;
}

void Monsters::setDropProbability(float d){
    _dropProbability = d;
}

int Monsters::maxSmellDistance() const{
    return _maxSmellDistance;
}

void Monsters::setMaxSmellDistance(int m){
    _maxSmellDistance = m;
}


void Monsters::dropItem(){
    if (!dungeon()->isGameObject(position()) && trueWithProbability(dropProbability())) {
        dungeon()->addGameObject(itemToDrop(),position());
        _itemToDrop = nullptr;
    }
}

bool Monsters::canSmellPlayer(Player *p){
    if(position().stepsToPoint(p->position()) <= _maxSmellDistance){
        return true;
    }
    return false;
}