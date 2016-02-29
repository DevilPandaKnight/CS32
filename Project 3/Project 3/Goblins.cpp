//
//  Goblins.cpp
//  Project 3
//
//  Created by Jin on 5/25/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#include "Goblins.h"
#include "Weapons.h"
#include <stack>
#include "JRect.h"

Goblins::Goblins(int goblinSmellDistance, string name):Monsters(name){
    setHitpoint(randInt(6)+15);
    setWeapon(new ShortSwords());
    setStrengthpoints(3);
    setDexteritypoints(1);
    setArmorpoints(1);
    setSym('G');
    setDropProbability(1.0/3);
    if (goblinSmellDistance<1) {
        goblinSmellDistance = 15;
    }
    setMaxSmellDistance(goblinSmellDistance);
}

GameObjects* Goblins::itemToDrop(){
    switch (rand()%2) {
        case 0:
            setItemToDrop(new MagicAxes());
            break;
        case 1:
            setItemToDrop(new MagicFangsOfSleep());
            break;
        default:
            break;
    }
    return Monsters::itemToDrop();
}

void printWeight(char weight[MAXROW][MAXCOL]){
    clearScreen();
    for (int i = 0; i<MAXROW; i++) {
        for (int j = 0; j<MAXCOL; j++) {
            if (weight[i][j] == -1) {
                cout<<'w'<<" ";
            }
            else{
                if(weight[i][j]>9){cout<<(int)weight[i][j];}
                else {cout<<(int)weight[i][j]<<" ";}
            }
        }
        cout<<endl;
    }
}

bool Goblins::canSmell(char maze[MAXROW][MAXCOL],int sr, int sc, int er, int ec){
    //printWeight(weight);
    if (weight[sr][sc] > maxSmellDistance()) {
        return false;
    }
    if (sr == er && sc == ec) {
        findPlayer = true;
        pointToGo = point2D(sc,sr);
        return findPlayer;
    }
    if (weight[sr][sc] == -1) {
        weight[sr][sc] = 0;
    }
    if (maze[sr-1][sc] == ' ') {
        if (weight[sr-1][sc] == -1 || weight[sr-1][sc] > weight[sr][sc]) {
            weight[sr-1][sc] = weight[sr][sc]+1;
        }
    }
    if (maze[sr+1][sc] == ' ') {
        if (weight[sr+1][sc] == -1 || weight[sr+1][sc] > weight[sr][sc]) {
            weight[sr+1][sc] = weight[sr][sc]+1;
        }
    }
    if (maze[sr][sc-1] == ' ') {
        if (weight[sr][sc-1] == -1 || weight[sr][sc-1] > weight[sr][sc]) {
            weight[sr][sc-1] = weight[sr][sc]+1;
        }
    }
    if (maze[sr][sc+1] == ' ') {
        if (weight[sr][sc+1] == -1 || weight[sr][sc+1] > weight[sr][sc]) {
            weight[sr][sc+1] = weight[sr][sc]+1;
        }
    }
    
    if (maze[sr-1][sc] == ' ' && weight[sr-1][sc] > weight[sr][sc]) {canSmell(maze, sr-1, sc, er, ec);}
    if (maze[sr+1][sc] == ' ' && weight[sr+1][sc] > weight[sr][sc]) {canSmell(maze, sr+1, sc, er, ec);}
    if (maze[sr][sc-1] == ' ' && weight[sr][sc-1] > weight[sr][sc]) {canSmell(maze, sr, sc-1, er, ec);}
    if (maze[sr][sc+1] == ' ' && weight[sr][sc+1] > weight[sr][sc]) {canSmell(maze, sr, sc+1, er, ec);}
    
    return findPlayer;
}

void Goblins::nextMove(){
    int w = weight[pointToGo.y][pointToGo.x];
    while (w != 1) {
        if (weight[pointToGo.y-1][pointToGo.x] != -1 && weight[pointToGo.y-1][pointToGo.x] < w) {
            pointToGo = point2D(pointToGo.x, pointToGo.y-1);
        }
        else if (weight[pointToGo.y+1][pointToGo.x] != -1 && weight[pointToGo.y+1][pointToGo.x] < w){
            pointToGo = point2D(pointToGo.x, pointToGo.y+1);
        }
        else if (weight[pointToGo.y][pointToGo.x-1] != -1 && weight[pointToGo.y][pointToGo.x-1] < w){
            pointToGo = point2D(pointToGo.x-1, pointToGo.y);
        }
        else if (weight[pointToGo.y][pointToGo.x+1] != -1 && weight[pointToGo.y][pointToGo.x+1] < w){
            pointToGo = point2D(pointToGo.x+1, pointToGo.y);
        }
        w = weight[pointToGo.y][pointToGo.x];
    }
}

bool Goblins::canSmellPlayer(Player *p){
    char map[MAXROW][MAXCOL];
    dungeon()->mapCopyWithSpaceAndWall(map);
    map[position().y][position().x] = ' ';
    memset(weight, -1, sizeof(weight));
    pointToGo = point2D(-1, -1);
    findPlayer = false;
    if (canSmell(map, position().y, position().x, p->position().y, p->position().x) && weight[pointToGo.y][pointToGo.x] < maxSmellDistance()) {
		return true;
    }
    return false;
}

void Goblins::moveToPlayer(Player *p){
    if(!findPlayer){
        return;
    }
    nextMove();
    if (moveToPoint(pointToGo)) {
        return;
    }
    if (p->position() == pointToGo) {
        attack(p);
    }
}
