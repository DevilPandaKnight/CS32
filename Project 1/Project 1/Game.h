//
//  Game.h
//  Project 1
//
//  Created by Jin on 4/4/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#ifndef __Project_1__Game__
#define __Project_1__Game__
class Pit;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nSnakes);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Pit* m_pit;
};

#endif /* defined(__Project_1__Game__) */
