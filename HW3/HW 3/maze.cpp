//
//  main.cpp
//  HW3
//
//  Created by Jin on 5/2/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

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
#include <cassert>
using namespace std;



bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    if (sr == er  &&  sc == ec)
        return true;
    
    maze[sr][sc] = '@';  // anything non-'.' will do
    
    if (maze[sr-1][sc] == '.'  &&  pathExists(maze, sr-1, sc, er, ec))
        return true;
    if (maze[sr+1][sc] == '.'  &&  pathExists(maze, sr+1, sc, er, ec))
        return true;
    if (maze[sr][sc-1] == '.'  &&  pathExists(maze, sr, sc-1, er, ec))
        return true;
    if (maze[sr][sc+1] == '.'  &&  pathExists(maze, sr, sc+1, er, ec))
        return true;
    
    return false;
}

#endif /* defined(__MAZESTACK__) */



int main(int argc, const char * argv[]) {
static char maze1[10][10] = {
          { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
          { 'X', '.', 'X', '.', '.', 'X', '.', '.', '.', 'X' },
          { 'X', '.', 'X', 'X', '.', 'X', '.', 'X', 'X', 'X' },
          { 'X', '.', '.', '.', '.', 'X', '.', 'X', '.', 'X' },
          { 'X', 'X', '.', 'X', '.', 'X', '.', '.', '.', 'X' },
          { 'X', 'X', 'X', '.', '.', 'X', '.', 'X', '.', 'X' },
          { 'X', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X' },
          { 'X', '.', 'X', 'X', '.', '.', 'X', '.', 'X', 'X' },
          { 'X', '.', '.', '.', '.', 'X', '.', '.', '.', 'X' },
          { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
        };
        
        static char maze2[10][10] = {
          { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
          { 'X', '.', 'X', '.', '.', 'X', '.', '.', '.', 'X' },
          { 'X', '.', 'X', 'X', '.', 'X', '.', 'X', 'X', 'X' },
          { 'X', '.', '.', '.', '.', 'X', '.', 'X', '.', 'X' },
          { 'X', 'X', '.', 'X', '.', 'X', '.', '.', '.', 'X' },
          { 'X', 'X', 'X', '.', 'X', 'X', '.', 'X', '.', 'X' },
          { 'X', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X' },
          { 'X', '.', 'X', 'X', '.', '.', 'X', '.', 'X', 'X' },
          { 'X', '.', '.', '.', '.', 'X', '.', '.', '.', 'X' },
          { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
        };
        
        static char maze3[10][10] = {
          { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
          { 'X', 'X', '.', '.', '.', '.', '.', 'X', 'X', 'X' },
          { 'X', '.', '.', 'X', 'X', '.', '.', '.', '.', 'X' },
          { 'X', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X' },
          { 'X', '.', 'X', '.', 'X', 'X', 'X', '.', '.', 'X' },
          { 'X', 'X', 'X', 'X', '.', '.', 'X', '.', '.', 'X' },
          { 'X', 'X', '.', '.', '.', '.', 'X', '.', '.', 'X' },
          { 'X', '.', '.', '.', '.', '.', '.', '.', 'X', 'X' },
          { 'X', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
          { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
        };
        
        static char maze4[10][10] = {
          { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
          { 'X', 'X', '.', '.', '.', '.', '.', 'X', 'X', 'X' },
          { 'X', '.', '.', 'X', 'X', '.', '.', '.', '.', 'X' },
          { 'X', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X' },
          { 'X', '.', 'X', '.', 'X', 'X', 'X', '.', '.', 'X' },
          { 'X', 'X', 'X', 'X', '.', '.', 'X', '.', '.', 'X' },
          { 'X', 'X', '.', '.', '.', '.', 'X', '.', '.', 'X' },
          { 'X', '.', '.', '.', '.', '.', 'X', '.', 'X', 'X' },
          { 'X', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
          { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
        };

    assert(pathExists(maze1, 8, 6, 1, 1));
    return 0;
}

