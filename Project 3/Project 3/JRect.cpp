//
//  JRect.cpp
//  JView
//
//  Created by Jin on 4/28/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#include "JRect.h"


JRect::JRect():size(),origin(){};

JRect::JRect(point2D o,size2D s):size(s),origin(o){}

JRect::JRect(int x,int y, int width,int height){
    origin = point2D(x, y);
    size = size2D(width, height);
}

point2D JRect::center() const{
    return point2D(origin.x+size.width/2, origin.y+size.height/2);
}
