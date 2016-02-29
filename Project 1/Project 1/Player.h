//
//  Player.h
//  Project 1
//
//  Created by Jin on 4/4/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#ifndef __Project_1__Player__
#define __Project_1__Player__

class Pit;

class Player
{
public:
    // Constructor
    Player(Pit *pp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;
    
    // Mutators
    void   stand();
    void   move(int dir);
    void   setDead();
    
private:
    Pit*  m_pit;
    int   m_row;
    int   m_col;
    int   m_age;
    bool  m_dead;
};

#endif /* defined(__Project_1__Player__) */
