//
//  ScoreList.cpp
//  HW1
//
//  Created by Jin on 4/12/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#include "ScoreList.h"

ScoreList::ScoreList():seq(){
    
}

void ScoreList::print(){
    unsigned long l;
    for (int i = 0; i<seq.size(); i++) {
        seq.get(i, l);
        cout<<"Score:"<<l<<endl;
    }
}


bool ScoreList::add(unsigned long score){
    if ((long)score < 0 || score > 100) {
        return false;
    }
    return seq.insert(score);
}

bool ScoreList::remove(unsigned long score){
    int pos;
    pos = seq.find(score);
    if (pos == -1) {
        return false;
    }
    return seq.erase(pos);
}

int ScoreList::size() const{
    return seq.size();
}


unsigned long ScoreList::minimum() const{
    if (seq.empty()) {
        return NO_SCORE;
    }
    unsigned long min;
    seq.get(0, min);
    return min;
}

unsigned long ScoreList::maximum() const{
    if (seq.empty()) {
        return NO_SCORE;
    }
    unsigned long max;
    seq.get(seq.size()-1, max);
    return max;
}


