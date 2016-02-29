//
//  main.cpp
//  HW1
//
//  Created by Jin on 4/11/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//
#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;



int main()
{
    Sequence s;
    assert(s.empty());
    assert(s.find(42) == -1);
    s.insert(42);
    assert(s.size() == 1  &&  s.find(42) == 0);
    cout << "Passed all tests" << endl;
}