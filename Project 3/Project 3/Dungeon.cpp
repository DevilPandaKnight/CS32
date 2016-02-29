//
//  Dungeon.cpp
//  Project 3
//
//  Created by Jin on 5/19/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#include "Dungeon.h"
#include <stdlib.h>
#include "utilities.h"
#include "mazestack.h"
#include "Monsters.h"
#include "Player.h"
#include "Weapons.h"
#include "GameObjects.h"
#include "Scrolls.h"
#include "Goblins.h"
#include <time.h>

Dungeon::Dungeon(){
    srand((int)time(0));
    player = nullptr;
    _level = 0;
    finishDrawDungeon = false;
    _goblinSmellDistance = -1;
}

void Dungeon::addGoblinSmellDistance(int d){
    _goblinSmellDistance = d;
}

void Dungeon::generateRoomAtSection(int numberOfRoomInSection,int section,vector<JRect>& rooms){
    int w,h,x,y;
    vector<JRect>::iterator iter;
    switch (numberOfRoomInSection) {
        case 1:
            h = rand()%10+5;
            w = rand()%6+7;
            x = rand()%(13-w)+14*section+1;
            y = rand()%(17-h)+1;
            rooms.push_back(JRect(x, y, w, h));
            break;
        case 2:
            for (int i = 0; i<2; i++) {
                h = rand()%5+3;
                w = rand()%6+7;
                x = rand()%(13-w)+14*section+1;
                y = rand()%(8-h)+i*9+1;
                rooms.push_back(JRect(x, y, w, h));
            }
            iter = rooms.end();
            drawLineBetweenPoints((--iter)->center(),(--iter)->center());
            break;
        default:
            break;
    }
}



void Dungeon::generatePathBetweenRooms(){
    point2D mid = rooms.at(rooms.size()/2).center();
    point2D current;
    char temp[MAXROW][MAXCOL];
    for (int i = 0; i<rooms.size(); i++) {
        current = rooms[i].center();
        memcpy(temp, content, sizeof(content));
        if (!pathExists(temp, current.y, current.x, mid.y, mid.x)) {
            drawLineBetweenPoints(current, mid);
        }
    }
}

void Dungeon::drawLineBetweenPoints(point2D p1, point2D p2){
    int increX = (p1.x > p2.x)? -1:1;
    int increY = (p1.y > p2.y)? -1:1;
    while (p1.x != p2.x || p1.y != p2.y) {
        int direction = rand()%2;
        if (p1.x == p2.x) {
            p1.y += increY;
            content[p1.y][p1.x] = ' ';
            continue;
        }
        if (p1.y == p2.y) {
            p1.x += increX;
            content[p1.y][p1.x] = ' ';
            continue;
        }
        switch (direction) {
            case 0:
                p1.y += increY;
                content[p1.y][p1.x] = ' ';
                break;
            case 1:
                p1.x += increX;
                content[p1.y][p1.x] = ' ';
                break;
            default:
                break;
        }
    }
}

void Dungeon::generateRooms(){
    for (int i = 0;i<5 ; i++) {
        generateRoomAtSection(rand()%2+1,i,rooms);
    }
}

void Dungeon::generateGameObject(int max){
    if (max<=0) {
        return;
    }
    while (max !=0) {
        switch (rand()%2) {
            case 0:
                generateWeapons(1);
                max--;
                break;
            case 1:
                generateScrolls(1);
                max--;
                break;
            default:
                break;
        }
    }
}

void Dungeon::generateWeapons(int max){
    for (int i = 0; i<max; i++) {
        switch (rand()%3) {
            case 0:
                obj.push_back(new Maces());
                break;
            case 1:
                obj.push_back(new ShortSwords());
                break;
            case 2:
                obj.push_back(new LongSwords());
                break;
            default:
                break;
        }
    }
}

void Dungeon::generateScrolls(int max){
    for (int i = 0; i<max; i++) {
        switch (rand()%4) {
            case 0:
                obj.push_back(new Strength());
                break;
            case 1:
                obj.push_back(new EnhanceArmor());
                break;
            case 2:
                obj.push_back(new EnhanceDexterity());
                break;
            case 3:
                obj.push_back(new EnhanceHealth());
                break;
            default:
                break;
        }
    }
}

Monsters* Dungeon::randomMonsterBasedOnLevel(int level){
    int dies = 0;
    switch (level) {
        case 0:
        case 1:
            dies = rand()%2;
            if (dies == 0) {return new Goblins(_goblinSmellDistance);}
            else if(dies == 1){return new Snakewomen();}
            break;
        case 2:
            dies = rand()%3;
            if (dies == 0) {return new Goblins(_goblinSmellDistance);}
            else if(dies == 1){return new Snakewomen();}
            else if(dies == 2){return new Bogeymen();}
            break;
        case 3:
            dies = rand()%4;
            if (dies == 0) {return new Goblins(_goblinSmellDistance);}
            else if(dies == 1){return new Snakewomen();}
            else if(dies == 2){return new Bogeymen();}
            else if(dies == 3){return new Dragons();}
            break;
        case 4:
            dies = rand()%4;
            if (dies == 0) {return new Goblins(_goblinSmellDistance);}
            else if(dies == 1){return new Snakewomen();}
            else if(dies == 2){return new Bogeymen();}
            else if(dies == 3){return new Dragons();}
            break;
        default:
            break;
    }
    return nullptr;
}

void Dungeon::generateMonsters(){
    int m = 2 + randInt(5*(_level+1));
    for (int i = 0; i<m; i++) {
        addMonster(randomMonsterBasedOnLevel(_level));
    }
    
}

//set up the Dungeon map
void Dungeon::prepareDungeonDrawing(){
    for (int row = 0; row<18; row++) {
        for (int col = 0; col < 70; col++) {
            content[row][col] = '#';
        }
    }
    
    //draw all the rooms
    rooms.clear();
    generateRooms();
    JRect room;
    for (size_t i = 0, len = rooms.size(); i<len; i++) {
        room = rooms[i];
        for (int width = 0; width < room.size.width; width++) {
            for (int height = 0; height < room.size.height; height++) {
                content[room.origin.y+height][room.origin.x+width] = ' ';
            }
        }
    }
    generatePathBetweenRooms();
    
    generateGameObject(rand()%2+2);
    addStairsAndGold();
    for (size_t i = 0,len = obj.size(); i<len; i++) {
        putGameObjInRandomPlace(obj[i]);
    }
    
    generateMonsters();
    finishDrawDungeon = true;
}

void Dungeon::drawDungeon(){
    if (!finishDrawDungeon) {
        prepareDungeonDrawing();
        updateDungeonDrawing();
    }
    else{
        updateDungeonDrawing();
    }
}

void Dungeon::drawGameObject(){
    GameObjects* g_obj;
    for (size_t i = 0,len = obj.size(); i<len; i++) {
        g_obj = obj[i];
        if (!isPlayer(g_obj->position()) && !isMonster(g_obj->position())) {
            content[g_obj->position().y][g_obj->position().x] = g_obj->sym();
        }
    }
}

void Dungeon::cleanDeadMonsters(){
    Monsters* m;
    for (vector<Monsters*>::iterator iter = monsters.begin(); iter != monsters.end();) {
        if ((*iter)->hitPoint() <= 0) {
            m = *iter;
            m->clearCurrentPosition();
            iter = monsters.erase(iter);
            delete m;
        }
        else{
            iter++;
        }
    }
}

void Dungeon::updateDungeonDrawing(){
    clearScreen();
    cleanDeadMonsters();
    drawGameObject();
    for (int row = 0; row<18; row++) {
        for (int col = 0; col < 70; col++) {
            cout<<content[row][col];
        }
        cout<<endl;
    }
    cout<<"Dungeon Level: "<<_level<<", Hit points: "<<player->hitPoint()<<", Armor: "<<player->armorPoints()<<", Strength: "<<player->strengthPoints()<<", Dexterity: "<<player->dexterityPoints()<<endl;
    
    vector<string>::iterator iter = actionMessage.begin();
    cout<<endl;
    while (iter != actionMessage.end()) {
        cout<<*iter<<endl;
        iter = actionMessage.erase(iter);
    }
}

void Dungeon::putActorInRandomPlace(Actors *a){
    JRect room = rooms[randInt((int)rooms.size())];
    point2D point( randInt(room.size.width)+room.origin.x ,randInt(room.size.height)+room.origin.y);
    while (isPlayer(point) || isMonster(point)) {
        room = rooms[randInt((int)rooms.size())];
        point = point2D(randInt(room.size.width)+room.origin.x ,randInt(room.size.height)+room.origin.y);
    }
    a->setPosition(point);
    a->draw();
}

GameObjects* Dungeon::removeObjAtPosition(point2D position){
    for (int i = 0; i<obj.size(); i++) {
        if (obj[i]->position() == position) {
            GameObjects* o = obj[i];
            obj.erase(obj.begin()+i);
            return o;
        }
    }
    return nullptr;
}

void Dungeon::putGameObjInRandomPlace(GameObjects *g){
    JRect room = rooms[randInt((int)rooms.size())];
    point2D point( randInt(room.size.width)+room.origin.x ,randInt(room.size.height)+room.origin.y);
    while (isGameObject(point)) {
        room = rooms[randInt((int)rooms.size())];
        point = point2D(randInt(room.size.width)+room.origin.x ,randInt(room.size.height)+room.origin.y);
    }
    g->setPosition(point);
}

void Dungeon::addPlayer(Player *p){
    player = p;
    player->setDungeon(this);
    if (!finishDrawDungeon) {
        prepareDungeonDrawing();
    }
    putActorInRandomPlace(p);
}

void Dungeon::addMonster(Monsters* m){
    monsters.push_back(m);
    m->setDungeon(this);
    putActorInRandomPlace(m);
}


void Dungeon::setSymbolAtPosition(char sym, point2D position){
    content[position.y][position.x] = sym;
}

bool Dungeon::isWall(point2D position){
    return content[position.y][position.x] == '#';
}

bool Dungeon::isMonster(point2D position){
    for (int i = 0; i<monsters.size(); i++) {
        if (position == monsters[i]->position()) {
            return true;
        }
    }
    return false;
}

bool Dungeon::isGameObject(point2D position){
    for (int i = 0; i<obj.size(); i++) {
        if (position == obj[i]->position()) {
            return true;
        }
    }
    return false;
}

bool Dungeon::isPlayer(point2D position){
    if (player) {
        return position == player->position();
    }
    return false;
}

bool Dungeon::isStaires(point2D position){
    for (int i = 0; i<obj.size(); i++) {
        if (obj[i]->position() == position && obj[i]->sym() == '>') {
            return true;
        }
    }
    return false;
}

bool Dungeon::isGold(point2D position){
    for (int i = 0; i<obj.size(); i++) {
        if (obj[i]->position() == position && obj[i]->sym() == '&') {
            return true;
        }
    }
    return false;
}

Monsters* Dungeon::MonsterAtPosition(point2D position){
    for (int i = 0; i<monsters.size(); i++) {
        if (position == monsters[i]->position()) {
            return monsters[i];
        }
    }
    return nullptr;
}

void Dungeon::generateNewLevel(){
    finishDrawDungeon = false;
    _level++;
    clearAll();
    rooms.clear();
    actionMessage.clear();
    prepareDungeonDrawing();
    putActorInRandomPlace(player);
}

void Dungeon::addActionMessage(string msg){
    actionMessage.push_back(msg);
}

void Dungeon::addGameObject(GameObjects *object, point2D position){
    object->setPosition(position);
    obj.push_back(object);
    setSymbolAtPosition(object->sym(), position);
}

void Dungeon::addStairsAndGold(){
    if (_level == 4) {
        obj.push_back(new Gold());
    }
    else{
        obj.push_back(new Stairs());
    }
}


void Dungeon::clearAll(){
    for (vector<GameObjects*>::iterator iter = obj.begin(); iter!=obj.end(); iter++) {
        delete *iter;
    }
    obj.clear();
    for (vector<Monsters*>::iterator iter = monsters.begin(); iter!=monsters.end(); iter++) {
        delete *iter;
    }
    monsters.clear();
}

void Dungeon::monsterMove(){
    cleanDeadMonsters();
    for (int i = 0; i<monsters.size(); i++) {
        if (monsters[i]->canSmellPlayer(player)) {
            monsters[i]->moveToPlayer(player);
        }
        if (monsters[i]->name() == "Dragon") {
            monsters[i]->increamentHitPoint();
        }
        if (player->hitPoint()<=0) {
            player->setLose(true);
            return;
        }
    }
}

void Dungeon::mapCopyWithSpaceAndWall(char map[MAXROW][MAXCOL]){
    memcpy(map, content, sizeof(content));
    for (int i = 0; i<monsters.size(); i++) {
        map[monsters[i]->position().y][monsters[i]->position().x] = '#';
    }
    for (int i = 0; i<obj.size(); i++) {
        map[obj[i]->position().y][obj[i]->position().x] = ' ';
    }
    map[player->position().y][player->position().x] = ' ';
}

Dungeon::~Dungeon(){
    clearAll();
}