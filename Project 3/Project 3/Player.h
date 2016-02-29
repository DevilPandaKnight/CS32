//
//  Player.h
//  Project 3
//
//  Created by Jin on 5/22/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#ifndef __Project_3__Player__
#define __Project_3__Player__
#include "Actors.h"
#include <vector>
#include <iostream>
using namespace std;

class Scrolls;
class GameObjects;
class Weapons;

//the player class inherit from Actors class
//it react from the game input that is from user
//and call the cooresponding method.
class Player:public Actors{
    
public:
    Player(string name);
    virtual ~Player();
    
    //the follwing 2 functions are properties of the player class
    //they provide user to get an set the private variables of the class.
    bool win() const;
    void setWin(bool w);
    
    bool lose() const;
    void setLose(bool l);
    
    //the following 5 functions coorespond the input from user.
    //pick --> g
    //read --> r
    //showInventory --> i
    //wield --> w
    //cheat --> c
    virtual void pick();
    virtual void read();
    void showInventory();
    void wield();
    void cheat();
    
    //when player is standing at the stair of the dungeon and
    //press '>' the goNextLevel will be called, which cause the
    //dungeon generate a new level
    void goNextLevel();
    
    //since player cannot drop items when it died, so the function is blank
    virtual void dropItem(){};
    
    
    //the move up, down, left, right overwrite the Actors' moves.
    //when the move* function is called, it first call Actors move*
    //then if Actors move* return true, then return true.
    //if the Actors move* return false, then check if is a monster
    //at that position and attack. then return false since the player did not move.
    virtual bool moveUp();
    virtual bool moveDown();
    virtual bool moveLeft();
    virtual bool moveRight();
    
private:
    bool _win;
    bool _lose;
    vector<GameObjects*> items;
    void showItems();
};

#endif /* defined(__Project_3__Player__) */
