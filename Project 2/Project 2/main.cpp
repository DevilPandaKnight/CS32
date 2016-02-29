//
//  main.cpp
//  Project 2
//
//  Created by Jin on 4/19/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#include <iostream>
using namespace std;

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s;
    assert(s.empty());
    assert(s.find("laobing") == -1);
    s.insert("laobing");
    assert(s.size() == 1  &&  s.find("laobing") == 0);
    cout << "Passed all tests" << endl;
}