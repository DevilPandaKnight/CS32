//
//  mazestack.cpp
//  HW2
//
//  Created by Jin on 4/24/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#ifndef __MAZESTACK__
#define __MAZESTACK__

#include <iostream>
#include <stack>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool canMoveTo(char maze[18][70],int r,int c){
    if (r > 17 || r < 0 || c > 69 || c < 0) {
        return false;
    }
    if (maze[r][c] != ' ') {
        return false;
    }
    maze[r][c]='#';
    return true;
}


bool pathExists(char maze[18][70], int sr, int sc, int er, int ec){
    stack<Coord> cod;
    cod.push(Coord(sr, sc));
    maze[sr][sc] = '#';
    Coord point(0,0);
    int r,c;
    while (!cod.empty()) {
        point = cod.top();
        cod.pop();
        r = point.r();
        c = point.c();
        
        if (r==er && c==ec) {
            return true;
        }
        if (canMoveTo(maze,r-1,c)) {
            cod.push(Coord(r-1, c));
        }
        if (canMoveTo(maze,r,c+1)) {
            cod.push(Coord(r, c+1));
        }
        if (canMoveTo(maze,r+1,c)) {
            cod.push(Coord(r+1, c));
        }
        if (canMoveTo(maze,r,c-1)) {
            cod.push(Coord(r, c-1));
        }
    }
    return false;
}

#endif /* defined(__MAZESTACK__) */

