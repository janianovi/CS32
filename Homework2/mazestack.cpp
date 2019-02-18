//
//  mazestack.cpp
//  homework3
//
//  Created by Janis Chen on 1/29/19.
//  Copyright © 2019 Test Project. All rights reserved.
//

#include <stack>
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
    
    stack<Coord> cordStack;
    cordStack.push(Coord(sr, sc));
    
    maze[sr][sc] = 'A';
    
    while (!cordStack.empty())
    {
        Coord cord = cordStack.top();
        cordStack.pop();
        
        if (cord.r() == er && cord.c() == ec)
            return true;
        
        if (maze[cord.r()-1][cord.c()] == '.') //North
        {
            Coord nor(cord.r()-1, cord.c());
            cordStack.push(nor);
            maze[cord.r()-1][cord.c()] = 'A';
        }
        
        if (maze[cord.r()][cord.c()+1] == '.') //East
        {
            Coord eas(cord.r(), cord.c()+1);
            cordStack.push(eas);
            maze[cord.r()][cord.c()+1] = 'A';
        }
        
        if (maze[cord.r()+1][cord.c()] == '.') //South
        {
            Coord sou(cord.r()+1, cord.c());
            cordStack.push(sou);
            maze[cord.r()+1][cord.c()] = 'A';
        }
        
        if (maze[cord.r()][cord.c()-1] == '.') //West
        {
            Coord wes(cord.r(), cord.c()-1);
            cordStack.push(wes);
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








