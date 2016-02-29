//
//  Sequence.cpp
//  HW1
//
//  Created by Jin on 4/11/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#include "Sequence.h"



Sequence::Sequence(){
    length = 0;
    next = nullptr;
    prev = nullptr;
    last = this;
}

int Sequence::size() const{
    return length;
}

bool Sequence::empty() const{
    return length==0;
}

//delete all the cells that followed the list, only called in destructor.
void Sequence::deleteAllCell(){
    Sequence* temp = last;
    while (last!=this) {
        last = temp->prev;
        delete temp;
        temp = last;
    }
    next = nullptr;
}

Sequence::~Sequence(){
    deleteAllCell();
}

Sequence::Sequence(const Sequence& other){
    next = nullptr;
    prev = nullptr;
    last = this;
    Sequence* temp = other.next;
    length = other.length;
    for (int i = 0; i<length; i++) {
        duplicateCell(temp);
        temp = temp->next;
    }
}


Sequence& Sequence::operator=(const Sequence &other){
    if (this!=&other) {
        Sequence temp(other);
        swap(temp);
    }
    return *this;
}

//copy a cell from other linklist and append to the end of it own list.
void Sequence::duplicateCell(Sequence* cell){
    Sequence* temp = new Sequence();
    temp->value = cell->value;
    temp->prev = last;
    last->next = temp;
    last = temp;
}

//get the cell at index specified
Sequence* Sequence::getCellAtIndex(int pos){
    if (pos<0 || pos>=length) {
        return nullptr;
    }
    Sequence* temp = next;
    for (int i = 0; i<pos; i++) {
        temp = temp->next;
    }
    return temp;
}

bool Sequence::insert(int pos, const ItemType &value){
    if (pos<0 || pos>length) {
        return false;
    }
    Sequence* temp = new Sequence();
    temp->value = value;
    Sequence* current = (pos==length)? last:getCellAtIndex(pos);
    if (pos == length) {
        temp->prev = current;
        current->next = temp;
        last = temp;
    }
    else{
        temp->next = current;
        temp->prev = current->prev;
        current->prev->next = temp;
        current->prev = temp;
    }
    length++;
    return true;
}



bool Sequence::insert(const ItemType &value){
    return insert(length, value);
}

bool Sequence::erase(int pos){
    if (length==0 || pos<0 || pos>=length) {
        return false;
    }
    Sequence* temp = getCellAtIndex(pos);
    temp->prev->next = temp->next;
    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    }
    else{
        last = temp->prev;
    }
    delete temp;
    length--;
    return true;
}

//debugging tool, print the list..
void Sequence::printArray(){
    Sequence* temp = this;
    for (int i = 0; i<length; i++) {
        temp = temp->next;
        cout<<temp->value<<endl;
    }
}


int Sequence::remove(const ItemType &value){
    int pos;
    int count = 0;
    while ((pos = find(value)) != -1) {
        erase(pos);
        count++;
    }
    return (count==0)? -1:count;
}

bool Sequence::get(int pos, ItemType &value) const{
    if (pos<0 || pos>=length) {
        return false;
    }
    Sequence* temp = next;
    for (int i = 0; i<pos; i++) {
        temp = temp->next;
    }
    value = temp->value;
    return true;
}

bool Sequence::set(int pos, const ItemType &value){
    if (pos<0 || pos>=length) {
        return false;
    }
    Sequence* temp = getCellAtIndex(pos);
    temp->value = value;
    return true;
}

int Sequence::find(const ItemType &value) const{
    Sequence* temp = next;
    for (int i = 0; i<length; i++) {
        if (temp->value == value) {
            return i;
        }
        temp = temp->next;
    }
    return -1;
}

void Sequence::swap(Sequence &other){
    Sequence* tempNext = other.next;
    Sequence* tempLast = other.last;
    int tempLen = other.length;
    
    other.next = next;
    if (other.next != nullptr) {
        other.next->prev = &other;
        other.last = last;
    }
    else{
        other.last = &other;
    }
    other.length = length;
    
    
    next = tempNext;
    if (next != nullptr) {
        next->prev = this;
        last = tempLast;
    }
    else{
        last = this;
    }
    length = tempLen;
}

//compare s1 and s2. starting at position p in s1,
//and see the consecutive content are the same with s2
bool compareAtPosition(int p,const Sequence& s1,const Sequence& s2){
    ItemType sq_1;
    ItemType sq_2;
    for (int i = 0; i<s2.size(); i++) {
        s1.get(p+i, sq_1);
        s2.get(i, sq_2);
        if (sq_1 != sq_2) {
            return false;
        }
    }
    return true;
}

int subsequence(const Sequence& seq1, const Sequence& seq2){
    if (seq2.size() > seq1.size() || seq2.size()==0 || seq1.size() == 0) {
        return -1;
    }
    int i = 0;
    bool find = false;
    for (int len = seq1.size()-seq2.size();i<=len;i++) {
        if (compareAtPosition(i,seq1,seq2)) {
            find = true;
            break;
        }
    }
    return (find)? i:-1;
}


void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result){
    Sequence s = Sequence();
    int minLen =(seq1.size()<seq2.size())? seq1.size():seq2.size();
    int i = 0;
    ItemType s1;
    ItemType s2;
    for (; i<minLen; i++) {
        seq1.get(i, s1);
        seq2.get(i, s2);
        s.insert(s1);
        s.insert(s2);
    }
    for (; i<seq1.size(); i++) {
        seq1.get(i, s1);
        s.insert(s1);
    }
    for (; i<seq2.size(); i++) {
        seq2.get(i, s2);
        s.insert(s2);
    }
    result = s;
}













