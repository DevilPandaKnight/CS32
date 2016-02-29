//
//  Player.cpp
//  Project 3
//
//  Created by Jin on 5/22/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#include "Player.h"
#include "utilities.h"
#include "Weapons.h"
#include "Scrolls.h"
#include "Dungeon.h"

Player::Player(string name):Actors(name){
    setMaxHitPoint(20);
    setHitpoint(maxHitPoint());
    ShortSwords *s = new ShortSwords("short sword",position());
    items.push_back(s);
    setWeapon(s);
    setArmorpoints(2);
    setStrengthpoints(2);
    setDexteritypoints(2);
    setSym('@');
    setWin(false);
}


void Player::pick(){
    if (!dungeon()->isGold(position()) && items.size() >= 26) {
        dungeon()->addActionMessage("Your knapsack is full; you can't pick that up.");
        return;
    }
    if (dungeon() && dungeon()->isGameObject(position())) {
        GameObjects* obj = dungeon()->removeObjAtPosition(position());
        items.push_back(obj);
        if (obj->sym() == ')' && items.size() < 26) {
            dungeon()->addActionMessage("You pick up "+obj->name());
        }
        else if (obj->sym() == '?' && items.size() < 26){
            dungeon()->addActionMessage("You pick up a scroll called "+obj->name());
        }
        else if (obj->sym() == '&'){
            dungeon()->addActionMessage("You pick up "+obj->name());
            dungeon()->addActionMessage("Congratulations, you won!");
            setWin(true);
        }
    }
}

void Player::read(){
    showItems();
    char c = getCharacter();
    if (isalpha(tolower(c))) {
        int index = c-'a';
        if (index < items.size()) {
            if (items[index]->sym() == '?') {
                Scrolls* s = (Scrolls*)items[index];
                items.erase(items.begin()+index);
                s->putMagicOnActor(this);
                dungeon()->addActionMessage("You read the scroll called "+s->name());
                dungeon()->addActionMessage(s->effectString());
                delete s;
            }
            else{
                dungeon()->addActionMessage("You can't read a "+items[index]->name());
            }
        }
    }
}

void Player::showItems(){
    clearScreen();
    cout<<"Inventory:"<<endl;
    for (int i = 0; i<items.size(); i++) {
        cout<<" "<<(char)(i+'a')<<". "<<items[i]->description()<<endl;
    }
}

void Player::showInventory(){
    showItems();
    getCharacter();
}

void Player::wield(){
    showItems();
    char c = getCharacter();
    if (isalpha(tolower(c))) {
        int index = c-'a';
        if (index < items.size()) {
            if (items[index]->sym() == ')') {
                setWeapon((Weapons*)items[index]);
                dungeon()->addActionMessage("You are wielding "+items[index]->name());
            }
            else{
                dungeon()->addActionMessage("You can't wield "+items[index]->name());
            }
        }
    }
}

void Player::goNextLevel(){
    if (dungeon() && dungeon()->isStaires(position())){
        dungeon()->generateNewLevel();
    }
}

bool Player::win() const{
    return _win;
}

void Player::setWin(bool w){
    _win = w;
}

bool Player::lose() const{
    return _lose;
}

void Player::setLose(bool l){
    _lose = l;
}

Player::~Player(){
    for (vector<GameObjects*>::iterator iter = items.begin(); iter != items.end(); iter++) {
        delete *iter;
    }
    setWeapon(nullptr);
}

void Player::cheat(){
    setMaxHitPoint(50);
    setHitpoint(50);
    setStrengthpoints(9);
}


bool Player::moveUp(){
    if(Actors::moveUp()){return true;}
    
    point2D p = point2D(position().x, position().y-1);
    Monsters* m = dungeon()->MonsterAtPosition(p);
    if (m) {
        attack((Actors*)m);
    }
    return false;
}

bool Player::moveDown(){
    if(Actors::moveDown()){return true;}
    
    point2D p = point2D(position().x, position().y+1);
    Monsters* m = dungeon()->MonsterAtPosition(p);
    if (m) {
        attack((Actors*)m);
    }
    return false;
}

bool Player::moveLeft() {
    if(Actors::moveLeft()){return true;}
    
    point2D p = point2D(position().x-1, position().y);
    Monsters* m = dungeon()->MonsterAtPosition(p);
    if (m) {
        attack((Actors*)m);
    }
    return false;
}

bool Player::moveRight() {
    if(Actors::moveRight()){return true;}
    
    point2D p = point2D(position().x+1, position().y);
    Monsters* m = dungeon()->MonsterAtPosition(p);
    if (m) {
        attack((Actors*)m);
    }
    return false;
}