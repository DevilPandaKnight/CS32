//
//  Monsters.h
//  Project 3
//
//  Created by Jin on 5/23/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#ifndef __Project_3__Monsters__
#define __Project_3__Monsters__
#include "Actors.h"
#include "utilities.h"
#include "Weapons.h"
#include "Player.h"


//Monsters class inherit from Actors.
//the monsters moves basic on if it can smell player
//if its smell the player, then it moves, otherwise it will not move.
class Monsters:public Actors {
public:
    Monsters(string name);
    virtual ~Monsters();
    
    //the moveToPlayer works for Bogeymen, Snakewomen and Dragons
    //they will only move toward the place where the player is and
    //will never move farther from player.
    virtual void moveToPlayer(Player* p);
    
    //the can smell return true if the steps take from monster is
    //smaller or equal to the steps specified in the project spec.
    //the dragon in this case is 1, so it will only move when the
    //player is next to its. but since player is occupying that
    //position, the dragon cannot move to that point, so it will
    //always stand where its is.
    virtual bool canSmellPlayer(Player* p);
    
    //since monsters cannot pick up an item or read a scroll
    //so i will leave it blank.
    virtual void pick(){};
    virtual void read(){};
    
    //the drop item function will add the item that monster carries
    //to the dungeon based on the probabilities that is in the
    //project 3 spec.
    virtual void dropItem();
    
    //the following 6 functions are properties function of the
    //class. it provide a way that user can get and set the class
    //private variables.
    virtual GameObjects* itemToDrop();
    void setItemToDrop(GameObjects* i);
    int maxSmellDistance() const;
    void setMaxSmellDistance(int m);
    float dropProbability() const;
    void setDropProbability(float d);
    

private:
    //the item to drop stores the item will be dropped
    //describled in the project 3 spec.
    GameObjects* _itemToDrop;
    
    //the monster will smell a player based on the value of
    //_maxSmellDistance that is in the spec. so dragon will
    //be 1 and Goblin will be the value passed in from game class
    int _maxSmellDistance;
    
    float _dropProbability;
};

//the Bogeymen totally inherit from monster class
//it does not need to implement anything except setting
//its some properties.
class Bogeymen:public Monsters{
public:
    Bogeymen(string name="Bogeymen"):Monsters(name){
        setHitpoint(randInt(6)+5);
        setWeapon(new ShortSwords());
        setStrengthpoints(randInt(2)+2);
        setDexteritypoints(randInt(2)+2);
        setArmorpoints(2);setSym('B');
        setMaxSmellDistance(5);
        setItemToDrop(new MagicAxes());
        setDropProbability(0.1);
    }
};

//the Snakewomen totally inherit from monster class
//it does not need to implement anything except setting
//its some properties.
class Snakewomen:public Monsters{
public:
    Snakewomen(string name="Snakewomen"):Monsters(name){
        setHitpoint(randInt(4)+3);
        setWeapon(new MagicFangsOfSleep());
        setStrengthpoints(2);
        setDexteritypoints(3);
        setArmorpoints(3);
        setSym('S');
        setMaxSmellDistance(3);
        setItemToDrop(new MagicFangsOfSleep());
        setDropProbability(1.0/3);
    }
};

//the Dragons totally inherit from monster class
//it does not need to implement anything except setting
//its some properties.
class Dragons:public Monsters{
public:
    Dragons(string name="Dragon"):Monsters(name){
        setHitpoint(randInt(6)+20);
        setWeapon(new LongSwords());
        setStrengthpoints(4);
        setDexteritypoints(4);
        setArmorpoints(4);
        setSym('D');
        setDropProbability(1);
    }
};




#endif /* defined(__Project_3__Monsters__) */
