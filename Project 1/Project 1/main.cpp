//
//  main.cpp
//  Project 1
//
//  Created by Jin on 4/4/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "History.h"
using namespace std;


int main()
{
    // Initialize the random number generator.  (You don't need to
    // understand how this works.)
    srand(static_cast<unsigned int>(time(0)));
    
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 3, 2);
    Game g(9, 10, 20);
    
    // Play the game
    g.play();
}