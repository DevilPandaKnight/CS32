//
//  Snake.h
//  Project 1
//
//  Created by Jin on 4/4/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#ifndef __Project_1__Snake__
#define __Project_1__Snake__

class Pit;  // This is needed to let the compiler know that Pit is a
// type name, since it's mentioned in the Snake declaration.

class Snake
{
public:
    // Constructor
    Snake(Pit* pp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    
private:
    Pit* m_pit;
    int  m_row;
    int  m_col;
};

#endif /* defined(__Project_1__Snake__) */
