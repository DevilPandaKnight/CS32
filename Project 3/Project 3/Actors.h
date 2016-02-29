//
//  Actors.h
//  Project 3
//
//  Created by Jin on 5/22/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#ifndef __Project_3__Actors__
#define __Project_3__Actors__
#include "JRect.h"
#include <string>
using namespace std;

class Dungeon;
class Scrolls;
class GameObjects;
class Weapons;

//the Actors class is the base class for monster and player
//most of player and monster's function calls delegates to
//the Actors class to perform, so the player and monster
//class will not need to implement those method.
class Actors {
public:
    Actors(string name);
    virtual ~Actors();
    
    //the following 22 functions are properties for the private variables,
    //provide the user to get and set private variables of the Actors class
    string name() const;
    void setName(string n);
    
    point2D position() const;
    void setPosition(point2D p);
    
    int hitPoint() const;
    void setHitpoint(int h);
    
    const Weapons* weapon() const;
    void setWeapon(Weapons* w);
    
    int armorPoints() const;
    void setArmorpoints(int a);
    
    int strengthPoints() const;
    void setStrengthpoints(int s);
    
    int dexterityPoints() const;
    void setDexteritypoints(int d);
    
    int sleepTime() const;
    void setSleeptime(int s);
    
    int maxHitPoint() const;
    void setMaxHitPoint(int m);
    
    Dungeon* dungeon() const;
    void setDungeon(Dungeon* d);
    
    char sym() const;
    void setSym(char s);
    
    //the increamentHitPoint increase the Actors hit point
    //every 1 out 10 chance when user press a key on the keyboard.
    //the player and dragon will need to call this function, but
    //other monsters does not.
    virtual void increamentHitPoint();
    
    //the draw function will put the Actors' own symbal like '@' or 'G'
    //on the position that is standing in the dungeon.
    void draw() const;
    
    //the moveToPoint function will put the actor to a given point in
    //the dungeon and draw itself at that position and clear its old position
    //the moveToPoint will return false if the actor is blocked by wall or other actors.
    //and will return true if the actor can be placed at that position.
    //notice that the function will return true if the actor is in sleeping
    //because it does not been block by wall or other actor.
    bool moveToPoint(point2D p);
    
    //the moveUp, down, left, right function will return true if
    //the actor can move one step up, down, left or right
    //and are not blocked by wall or other actor object
    //it will also return true even if the actor is in sleeping,
    //because it does not been block by wall or other actor.
    virtual bool moveUp();
    virtual bool moveDown();
    virtual bool moveLeft();
    virtual bool moveRight();
    
    //the clearCurrentPosition function set the symbal at actors' current
    //position to be blank.
    void clearCurrentPosition();
    
    //the attack function takes an another actor as argument and
    //attack that actor based on the formular from project 3 spec.
    //the attack status will be collected by dungeon and will be
    //displayed next time when the drawdungeon method is called.
    void attack(Actors* other);
    
    //the attackerPoints, defenderPoints and damage are the implementation
    //of the formular in the project 3 spec.
    int attackerPoints() const;
    int defenderPoints() const;
    int damage() const;
    
    //the following three functions are based on the class
    //which implement these functions, so for now they are absctrct.
    virtual void pick() = 0;
    virtual void read() = 0;
    virtual void dropItem() = 0;
    
private:
    string _name;
    point2D _position;
    int _hitPoint;
    Weapons* _weapon;
    int _armorPoints;
    int _strengthPoints;
    int _dexterityPoints;
    int _sleepTime;
    int _maxHitPoint;
    Dungeon* _dungeon;
    char _sym;
};

#endif /* defined(__Project_3__Actors__) */
