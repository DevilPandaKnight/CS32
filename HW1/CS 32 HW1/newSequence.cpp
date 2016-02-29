//
//  newSequence.cpp
//  HW1
//
//  Created by Jin on 4/12/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#include "newSequence.h"
enum SHIFTDIRECTION{
    FORWARD,
    BACKWARD
};

#define checkPos(p) if(p<0 || p>length){return false;}

Sequence::Sequence(long capa){
    if (capa < 0) {
        cout<<"initialize Sequence with negative capacity."<<endl;
        exit(-1);
    }
    length = 0;
    capacity = capa;
    array = new ItemType[capa];
}

Sequence::Sequence(const Sequence& other){
    capacity = other.capacity;
    length = other.length;
    array = new ItemType[capacity];
    for (int i = 0; i<length; i++) {
        array[i] = other.array[i];
    }
}

Sequence& Sequence::operator=(const Sequence &other){
    if (this != &other) {
        Sequence temp(other);
        swap(temp);
    }
    return *this;
}

Sequence::~Sequence(){
    delete []array;
}

int Sequence::size() const{
    return length;
}

bool Sequence::empty() const{
    return length==0;
}

bool Sequence::insert(int pos, const ItemType &value){
    if (pos<0 || pos>length || pos>=capacity || length==capacity) {
        return false;
    }
    if (pos!=length) {
        shiftArray(FORWARD, pos);
    }
    array[pos] = value;
    length++;
    return true;
}

void Sequence::shiftArray(int direction, int index){
    if (direction == FORWARD) {
        for (int i = length-1; i>=index; i--) {
            array[i+1] = array[i];
        }
    }
    else{
        for (int i = index; i<length-1; i++) {
            array[i] = array[i+1];
        }
    }
}

bool Sequence::insert(const ItemType &value){
    if (length==capacity) {
        return false;
    }
    int i = 0;
    for (; i<length; i++) {
        if (array[i]>=value) {
            shiftArray(FORWARD, i);
            break;
        }
    }
    array[i] = value;
    length++;
    return true;
}

bool Sequence::erase(int pos){
    checkPos(pos)
    shiftArray(BACKWARD, pos);
    length--;
    return true;
}

void Sequence::printArray(){
    for (int i = 0; i<length; i++) {
        cout<<array[i]<<endl;
    }
    cout<<endl;
}



int Sequence::remove(const ItemType &value){
    int pos;
    int count = 0;
    while ((pos = find(value))!=-1) {
        erase(pos);
        count++;
    }
    return (count==0)? -1:count;
}

bool Sequence::get(int pos, ItemType &value) const{
    checkPos(pos)
    value = array[pos];
    return true;
}

bool Sequence::set(int pos, const ItemType &value){
    checkPos(pos)
    array[pos] = value;
    return true;
}

int Sequence::find(const ItemType &value) const{
    int i = 0;
    for (; i<length; i++) {
        if (array[i]==value) {
            return i;
        }
    }
    return -1;
}

void Sequence::swap(Sequence &other){
    ItemType* tempArray = other.array;
    size_t tempCapa = other.capacity;
    int tempLen = other.length;
    
    other.array = array;
    other.length = length;
    other.capacity = capacity;
    
    array = tempArray;
    capacity = tempCapa;
    length = tempLen;
}