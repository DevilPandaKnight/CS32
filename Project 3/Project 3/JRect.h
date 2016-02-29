//
//  JRect.h
//  JView
//
//  Created by Jin on 4/28/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#ifndef __JView__JRect__
#define __JView__JRect__
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

//all the geometry stuff about the game are in this file.

//point2D record the position of the room, player, monster and all game objects.
struct point2D {
    int x;
    int y;
    point2D(){x = 0;y=0;}
    point2D(int x,int y){this->x = x;this->y = y;}
    float distance(point2D p){return pow((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y),0.5);}
    int stepsToPoint(point2D p){return abs(x-p.x)+abs(y - p.y);}
    bool operator==(point2D other){return x==other.x && y == other.y;}
};

//size2D record the width and the height of the room in dungeon
struct size2D {
    int width;
    int height;
    size2D(){}
    size2D(int width,int height){this->width = width;this->height = height;}
};

//JRect is the actual room in dungeon
struct JRect {
    JRect();
    JRect(point2D origin,size2D size);
    JRect(int x,int y, int width,int height);
    
    point2D center() const;
    
    //properties
    point2D origin;
    size2D size;
};



#endif /* defined(__JView__JRect__) */
