//
//  Actors.cpp
//  Project 3
//
//  Created by Jin on 5/22/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#include "Actors.h"
#include <iostream>
#include "Weapons.h"
#include "GameObjects.h"
#include "Scrolls.h"
#include "Dungeon.h"
#include "GameObjects.h"
#include "utilities.h"
#include "Weapons.h"
#include <string>

#define ifIsBtw0To99(n) if( n < 0 || n > 99)return;

Actors::Actors(string name){
    this->_name = name;
    _maxHitPoint = 99;
    _weapon = nullptr;
    _dungeon = nullptr;
    _sleepTime = 0;
    _sym = 0;
}

string Actors::name() const{
    return _name;
}

void Actors::setName(string n){
    _name = n;
}

point2D Actors::position() const{
    return _position;
}

void Actors::setPosition(point2D p){
    _position = p;
}

int Actors::hitPoint() const{
    return _hitPoint;
}

void Actors::setHitpoint(int h){
    if (h>_maxHitPoint) {
        _hitPoint = _maxHitPoint;
    }
    else{
        _hitPoint = h;
    }
}

const Weapons* Actors::weapon() const{
    return _weapon;
}

void Actors::setWeapon(Weapons* w){
    _weapon = w;
}

int Actors::armorPoints() const{
    return _armorPoints;
}

void Actors::setArmorpoints(int a){
    ifIsBtw0To99(a)
    _armorPoints = a;
}

int Actors::strengthPoints() const{
    return _strengthPoints;
}

void Actors::setStrengthpoints(int s){
    ifIsBtw0To99(s)
    _strengthPoints = s;
}

int Actors::dexterityPoints() const{
    return _dexterityPoints;
}

void Actors::setDexteritypoints(int d){
    ifIsBtw0To99(d)
    _dexterityPoints = d;
}

int Actors::sleepTime() const{
    return _sleepTime;
}

void Actors::setSleeptime(int s){
    if (s<0 || s>9) {
        return;
    }
    _sleepTime = s;
}

int Actors::maxHitPoint() const{
    return _maxHitPoint;
}

void Actors::setMaxHitPoint(int m){
    _maxHitPoint = m;
}


void Actors::attack(Actors* other){
    if (_hitPoint<=0) {return;}
    if (randInt(attackerPoints()) >= randInt(other->defenderPoints())){
        other->_hitPoint -= damage();
        if (other->_hitPoint <= 0) {
            _dungeon->addActionMessage(_name+" "+_weapon->actionString()+" "+other->_name+" dealing a final blow.");
            other->dropItem();
            return;
        }
        _dungeon->addActionMessage(_name+" "+_weapon->actionString()+" "+other->_name+" and hits.");
        if (_weapon->name() == "magic fangs of sleep" && trueWithProbability(0.2)) {
            _dungeon->addActionMessage(_name+" "+_weapon->actionString()+" "+other->_name+" and hits, putting "+other->_name+" to sleep.");
            int sleepTime = rand()%5+2;
            other->_sleepTime = (sleepTime>other->_sleepTime)? sleepTime:other->_sleepTime;
        }
    }
    else{
        _dungeon->addActionMessage(_name+" "+_weapon->actionString()+" "+other->_name+" and misses.");
    }
    
}

Actors::~Actors(){
    //cout<<"actor class destroying weapon."<<endl;
    delete _weapon;
}

Dungeon* Actors::dungeon() const{
    return _dungeon;
}

void Actors::setDungeon(Dungeon* d){
    _dungeon = d;
}

char Actors::sym() const{
    return _sym;
}

void Actors::setSym(char s){
    _sym = s;
}

void Actors::increamentHitPoint(){
    if (trueWithProbability(0.1)) {
        setHitpoint(hitPoint()+1);
    }
}

void Actors::draw() const{
    if (_dungeon) {
        _dungeon->setSymbolAtPosition(_sym, _position);
    }
}

bool Actors::moveToPoint(point2D p){
    if (_sleepTime != 0) {_sleepTime--;return true;}
    if (_dungeon && !_dungeon->isWall(p) && !_dungeon->isMonster(p) && !_dungeon->isPlayer(p)) {
        _dungeon->setSymbolAtPosition(' ', _position);
        _position = p;
        draw();
        return true;
    }
    return false;
}

void Actors::clearCurrentPosition(){
    dungeon()->setSymbolAtPosition(' ',_position);
}

bool Actors::moveUp(){
    point2D p = point2D(_position.x, _position.y-1);
    return moveToPoint(p);
}

bool Actors::moveDown(){
    point2D p = point2D(_position.x, _position.y+1);
    return moveToPoint(p);
}

bool Actors::moveLeft() {
    point2D p = point2D(_position.x-1, _position.y);
    return moveToPoint(p);
}

bool Actors::moveRight() {
    point2D p = point2D(_position.x+1, _position.y);
    return moveToPoint(p);
}

int Actors::attackerPoints() const{
    return _dexterityPoints + _weapon->dexBonus();
}

int Actors::defenderPoints() const{
    return _dexterityPoints + _armorPoints;
}

int Actors::damage() const{
    return randInt(_strengthPoints + _weapon->damage());
}

