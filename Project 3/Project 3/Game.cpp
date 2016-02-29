// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>
#include "Player.h"
#include "Dungeon.h"
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance){
    _goblinSmellDistance = goblinSmellDistance;
}


// this function require user to enter the character 'q' so that the
// game exist when the player died or wins.
char getQ(){
    char c;
    while ((c=getCharacter()) != 'q') {
        c = getCharacter();
    }
    return c;
}


void Game::play()
{
	
    Dungeon d;
    d.addGoblinSmellDistance(_goblinSmellDistance);
    Player* p = new Player("Player");
    d.addPlayer(p);
    d.drawDungeon();
    char c = getCharacter();
    bool looping = true;
    while (looping){
        switch (c) {
            case 'k':
                p->moveUp();
                break;
            case 'j':
                p->moveDown();
                break;
            case 'h':
                p->moveLeft();
                break;
            case 'l':
                p->moveRight();
                break;
            case 'g':
                p->pick();
                break;
            case 'w':
                p->wield();
                break;
            case 'r':
                p->read();
                break;
            case '>':
                p->goNextLevel();
                break;
            case 'c':
                p->cheat();
                break;
            case 'i':
                p->showInventory();
                break;
            case 'q':
                looping = false;
                continue;
            default:
                break;
        }
        if (p->win()) {
            d.drawDungeon();
            cout << "Press q to exit game." << endl;
            c = getQ();
            looping = false;
            continue;
        }
        p->increamentHitPoint();
        d.monsterMove();
        d.drawDungeon();
        if (p->lose()) {
            cout << "Press q to exit game." << endl;
            c = getQ();
            looping = false;
            continue;
        }
        c = getCharacter();
    }
    delete p;
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
