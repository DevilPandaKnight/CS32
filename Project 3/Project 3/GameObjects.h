//
//  GameObjects.h
//  Project 3
//
//  Created by Jin on 5/22/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#ifndef __Project_3__GameObjects__
#define __Project_3__GameObjects__
#include "JRect.h"
#include <string>
using namespace std;

//the game object is an obstract class which stores the name, position and symbal
//of an object. and it wil not do any thing usefull.
class GameObjects {
public:
    GameObjects(string name, point2D position);
    virtual ~GameObjects(){}
    
    //the following 8 functions are getters and setters for the
    //class private variable.
    point2D position() const;
    void setPosition(point2D p);
    
    string name() const;
    void setName(string n);
    
    string description() const;
    void setDescription(string d);
    
    char sym() const;
    void setSym(char s);
private:
    string _description;
    point2D _position;
    string _name;
    char _sym;
};


class Stairs:public GameObjects {
public:
    Stairs(string name="stairs",point2D position=point2D()):GameObjects(name,position){setSym('>');}
};

class Gold:public GameObjects {
public:
    Gold(string name="the golden idol",point2D position=point2D()):GameObjects(name,position){setSym('&');}
};

#endif /* defined(__Project_3__GameObjects__) */
