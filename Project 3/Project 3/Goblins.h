//
//  Goblins.h
//  Project 3
//
//  Created by Jin on 5/25/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#ifndef __Project_3__Goblins__
#define __Project_3__Goblins__
#include "Monsters.h"
#include "JRect.h"
#include "Dungeon.h"

//the Goblins inherit from monster class
//its has own moving method that is different
//from other monsters.
class Goblins:public Monsters{
public:
    Goblins(int goblinSmellDistance,string name="Goblin");
    
    //since goblin will drop two different weapon,
    //i made the itemToDrop virtual so it will be
    //different from other monsters.
    virtual GameObjects* itemToDrop();
    
    //the goblin's move function is this moveToPlayer function
    //this function is actually based on the canSmellPlayer function
    //the canSmellPlayer setup the weighted map that represent steps
    //a Goblin takes from it own position to each position around its.
    //after the map is done, then is easy to see that the best choice of
    //movement for the Goblin to move.
    virtual void moveToPlayer(Player* p);
    virtual bool canSmellPlayer(Player* p);
    
private:
    //all the variables and function are helper variables for
    //moveToPlayer and canSmellPlayer functions.
    point2D pointToGo;
    bool findPlayer;
    char weight[MAXROW][MAXCOL];
    bool canSmell(char maze[MAXROW][MAXCOL],int sr, int sc, int er, int ec);
    void nextMove();
};

#endif /* defined(__Project_3__Goblins__) */
