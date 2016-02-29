//
//  Dungeon.h
//  Project 3
//
//  Created by Jin on 5/19/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#ifndef __Project_3__Dungeon__
#define __Project_3__Dungeon__

#include <iostream>
#include <vector>
#include "JRect.h"


using namespace std;

class Actors;
class Player;
class Monsters;
class GameObjects;

//dungeon max width and height
#define MAXROW 18
#define MAXCOL 70

//the dungeon class is the most important class in this game.
//it draws all game objects, player, monsters each time when user press a key
//the dungeon will take player status and monster status
//status like picking up an item, attack, or read a scroll
//and display all the status at once, kind like radio station.
//the dungeon will generate monsters, rooms and game object each time
//when a new level is generated.
class Dungeon {
public:
    Dungeon();
    ~Dungeon();
    
    //the draw dungeon funciton will be called each time user
    //press a key on key borad. and refresh the dungeon drawing
    void drawDungeon();
    
    //the 4 add.. function adds game elements in the dundeon and
    //display them in the position specifiied.
    void addPlayer(Player* p);
    void addActionMessage(string msg);
    void addMonster(Monsters* m);
    void addGameObject(GameObjects* object,point2D position);
    
    //the is... function return true if the object you are
    //looking for is at that position
    bool isWall(point2D position);
    bool isMonster(point2D position);
    bool isGameObject(point2D position);
    bool isPlayer(point2D position);
    bool isStaires(point2D position);
    bool isGold(point2D position);
    
    //these are utilities function that user can interact with
    //objects in the dungeon.
    GameObjects* removeObjAtPosition(point2D position);
    void putActorInRandomPlace(Actors* a);
    Monsters* MonsterAtPosition(point2D position);
    void setSymbolAtPosition(char sym, point2D position);
    void monsterMove();
    void mapCopyWithSpaceAndWall(char map[MAXROW][MAXCOL]);
    void addGoblinSmellDistance(int d);
    void generateNewLevel();
    
private:
    int _level;
    bool finishDrawDungeon;
    int _goblinSmellDistance;
    vector<JRect> rooms;
    vector<string> actionMessage;
    vector<GameObjects*> obj;
    vector<Monsters*> monsters;
    Player* player;
    char content[MAXROW][MAXCOL];
    
    void prepareDungeonDrawing();
    void updateDungeonDrawing();
    void generateRooms();
    void generatePathBetweenRooms();
    void drawLineBetweenPoints(point2D p1, point2D p2);
    void generateRoomAtSection(int numberOfRoomInSection,int section,vector<JRect>& rooms);
    void generateWeapons(int max);
    void generateScrolls(int max);
    void generateGameObject(int max);
    void putGameObjInRandomPlace(GameObjects* g);
    void drawGameObject();
    void addStairsAndGold();
    void clearAll();
    void generateMonsters();
    Monsters* randomMonsterBasedOnLevel(int level);
    void cleanDeadMonsters();
};

#endif /* defined(__Project_3__Dungeon__) */
