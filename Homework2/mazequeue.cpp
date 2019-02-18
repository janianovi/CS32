//
//  mazequeue.cpp
//  homework3
//
//  Created by Janis Chen on 1/30/19.
//  Copyright © 2019 Test Project. All rights reserved.
//

#include <queue>
#include <string>
#include <iostream>
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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    // Return true if there is a path from (sr,sc) to (er,ec)
    // through the maze; return false otherwise
    
    queue<Coord> cordQueue;
    cordQueue.push(Coord(sr, sc));
    
    maze[sr][sc] = 'A';
    
    while (!cordQueue.empty())
    {
        Coord cord = cordQueue.front();
        cordQueue.pop();
        
        if (cord.r() == er && cord.c() == ec)
            return true;
        
        if (maze[cord.r()-1][cord.c()] == '.') //North
        {
            cordQueue.push(Coord(cord.r()-1, cord.c()));
            maze[cord.r()-1][cord.c()] = 'A';
        }
        
        if (maze[cord.r()][cord.c()+1] == '.') //East
        {
            cordQueue.push(Coord(cord.r(), cord.c()+1));
            maze[cord.r()][cord.c()+1] = 'A';
        }
        
        if (maze[cord.r()+1][cord.c()] == '.') //South
        {
            cordQueue.push(Coord(cord.r()+1, cord.c()));
            maze[cord.r()+1][cord.c()] = 'A';
        }
        
        if (maze[cord.r()][cord.c()-1] == '.') //West
        {
            cordQueue.push(Coord(cord.r(), cord.c()-1));
            maze[cord.r()][cord.c()-1] = 'A';
        }
    }
    
    
    return false;
}


int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X....X...X",
        "X.XX.XX..X",
        "XXX....X.X",
        "X.XXX.XXXX",
        "X.X...X..X",
        "X...X.X..X",
        "XXXXX.X.XX",
        "X........X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 3,5, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}

