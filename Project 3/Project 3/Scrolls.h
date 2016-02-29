//
//  Scrolls.h
//  Project 3
//
//  Created by Jin on 5/22/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#ifndef __Project_3__Scrolls__
#define __Project_3__Scrolls__
#include "GameObjects.h"
#include "JRect.h"
#include "Actors.h"
#include "Dungeon.h"
#include <string>

//the Scrolls totally inherit from GameObject class
//it does not need to implement anything except setting
//its some properties.
class Scrolls:public GameObjects {
public:
    Scrolls(string name, point2D position);
    
    //the putMagicOnActor is the function that will be called when
    //the player reading the scroll, and it will be implemented by it
    //subclasses.
    virtual void putMagicOnActor(Actors* a) = 0;
    virtual ~Scrolls(){}
    
    //the effectString will return the string when reading the scroll.
    //like 'Your muscles bulge.'
    string effectString() const;
    void setEffectString(string e);
private:
    string _effectString;
};


//the Teleportation totally inherit from Scrolls class
//it does not need to implement anything except setting
//its some properties.
class Teleportation:public Scrolls {
public:
    Teleportation(string name="scroll of teleportation",point2D position = point2D()):Scrolls(name,position){setEffectString("You feel your body wrenched in space and time.");}
    virtual void putMagicOnActor(Actors* a){a->clearCurrentPosition();a->dungeon()->putActorInRandomPlace(a);};
};

//the Strength totally inherit from Scrolls class
//it does not need to implement anything except setting
//its some properties.
class Strength:public Scrolls {
public:
    Strength(string name="scroll of strength",point2D position = point2D()):Scrolls(name,position){setEffectString("Your muscles bulge.");}
    virtual void putMagicOnActor(Actors* a){a->setStrengthpoints(a->strengthPoints()+rand()%3+1);}
};

//the EnhanceArmor totally inherit from Scrolls class
//it does not need to implement anything except setting
//its some properties.
class EnhanceArmor:public Scrolls {
public:
    EnhanceArmor(string name="scroll of enhance armor",point2D position = point2D()):Scrolls(name,position){setEffectString("Your armor glows blue.");}
    virtual void putMagicOnActor(Actors* a){a->setArmorpoints(a->armorPoints()+rand()%3+1);}
};

//the EnhanceHealth totally inherit from Scrolls class
//it does not need to implement anything except setting
//its some properties.
class EnhanceHealth:public Scrolls {
public:
    EnhanceHealth(string name="scroll of enhance health",point2D position = point2D()):Scrolls(name,position){setEffectString("You feel your heart beating stronger.");}
    virtual void putMagicOnActor(Actors* a){a->setMaxHitPoint(a->maxHitPoint()+rand()%6+3);}
};

//the EnhanceDexterity totally inherit from Scrolls class
//it does not need to implement anything except setting
//its some properties.
class EnhanceDexterity:public Scrolls {
public:
    EnhanceDexterity(string name="scroll of enhance dexterity",point2D position = point2D()):Scrolls(name,position){setEffectString("You feel like less of a klutz.");}
    virtual void putMagicOnActor(Actors* a){a->setDexteritypoints(a->defenderPoints()+1);}
};

#endif /* defined(__Project_3__Scrolls__) */
