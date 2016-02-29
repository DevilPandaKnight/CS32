//
//  Weapons.h
//  Project 3
//
//  Created by Jin on 5/22/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#ifndef __Project_3__Weapons__
#define __Project_3__Weapons__
#include "GameObjects.h"
#include <string>
using namespace std;

class Weapons:public GameObjects{
    
public:
    Weapons(string name, point2D position);
    virtual ~Weapons(){}
    
    string actionString() const;
    void setActionString(string a);
    
    int damage() const;
    void setDamage(int d);
    
    int dexBonus() const;
    void setDexBonus(int d);
private:
    string _actionString;
    int _damage;
    int _dexBonus;
};


class Maces:public Weapons{
public:
    Maces(string name="mace", point2D position=point2D()):Weapons(name,position){setDexBonus(0);setDamage(2);setActionString("swings mace at");}
};

class ShortSwords:public Weapons{
public:
    ShortSwords(string name="short sword", point2D position=point2D()):Weapons(name,position){setDexBonus(0);setDamage(2);setActionString("slashes short sword at");}
};


class LongSwords:public Weapons{
public:
    LongSwords(string name="long sword", point2D position=point2D()):Weapons(name,position){setDexBonus(2);setDamage(4);setActionString("swings long sword at");}
};

class MagicAxes:public Weapons{
public:
    MagicAxes(string name="magic axes", point2D position=point2D()):Weapons(name,position){setDexBonus(5);setDamage(5);setActionString("chops magic axe at");}
};

class MagicFangsOfSleep:public Weapons{
public:
    MagicFangsOfSleep(string name="magic fangs of sleep", point2D position=point2D()):Weapons(name,position){setDexBonus(3);setDamage(2);setActionString("strikes magic fangs at");}
};



#endif /* defined(__Project_3__Weapons__) */
