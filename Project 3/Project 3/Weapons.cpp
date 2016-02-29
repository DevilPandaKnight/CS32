//
//  Weapons.cpp
//  Project 3
//
//  Created by Jin on 5/22/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#include "Weapons.h"
#include <iostream>

Weapons::Weapons(string n, point2D p):GameObjects(n,p){setSym(')');setDescription(name());}

string Weapons::actionString() const{
    return _actionString;
}

void Weapons::setActionString(string a){
    _actionString = a;
}

int Weapons::damage() const{
    return _damage;
}

void Weapons::setDamage(int d){
    _damage = d;
}

int Weapons::dexBonus() const{
    return _dexBonus;
}

void Weapons::setDexBonus(int d){
    _dexBonus = d;
}