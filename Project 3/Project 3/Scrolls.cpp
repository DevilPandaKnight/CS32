//
//  Scrolls.cpp
//  Project 3
//
//  Created by Jin on 5/22/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#include "Scrolls.h"

Scrolls::Scrolls(string name, point2D position):GameObjects(name,position){setSym('?');setDescription("A scroll called "+ name);}


string Scrolls::effectString() const{
    return _effectString;
}

void Scrolls::setEffectString(string e){
    _effectString = e;
}

