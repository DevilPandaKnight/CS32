//
//  History.cpp
//  Project 1
//
//  Created by Jin on 4/4/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

//implementation of constructor
History::History(int nRows,int nCols){
    _rows = nRows;
    _cols = nCols;
    _numberOfCoordinates = 0;
    _coordinates = new Coordinate[MAXSNAKES];
}


//implementation of record
bool History::record(int r, int c) {
    //check if is within bound
    if (r >_rows || r < 1 || c > _cols || c < 1) {
        return false;
    }
    //check if out of max number of snakes
    if (_numberOfCoordinates == MAXSNAKES) {
        return false;
    }
    //record the location of snake
    Coordinate coord = {r,c};
    _coordinates[_numberOfCoordinates++] = coord;
    return true;
}


//implementation of display
void History::display() const{
    char grid[MAXROWS][MAXCOLS];
    
    for (int i = 0; i<_rows; i++) {
        for (int j = 0; j < _cols; j++) {
            grid[i][j] = '.';
        }
    }
    
    for (int i = 0;i<_numberOfCoordinates;i++) {
        Coordinate coord = _coordinates[i];
        char& c = grid[coord.row-1][coord.col-1];
        switch (c) {
            case '.': c = 'A'; break;
            case 'Z':break;
            default:
                c++;
        }
    }
    
    clearScreen();
    for (int r = 0; r < _rows; r++)
    {
        for (int c = 0; c < _cols; c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
}


History::~History(){
    delete []_coordinates;
}