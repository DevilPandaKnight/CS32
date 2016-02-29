//
//  History.h
//  Project 1
//
//  Created by Jin on 4/4/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#ifndef __Project_1__History__
#define __Project_1__History__



class History {
    
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    ~History();
private:
    int _rows;
    int _cols;
    struct Coordinate{
        int row;
        int col;
    };
    Coordinate* _coordinates;
    int _numberOfCoordinates;
};

#endif /* defined(__Project_1__History__) */
