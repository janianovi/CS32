//
//  History.cpp
//  main
//
//  Created by Janis Chen on 1/9/19.
//  Copyright © 2019 Test Project. All rights reserved.
//

#include <iostream>

#include "globals.h"
#include "History.h"
#include "Arena.h"

using namespace std;

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    for (int i = 0; i < MAXROWS; i++)
    {
        for (int j = 0; j < MAXCOLS; j++)
        {
            m_grids[i][j] = '.';
        }
    }
}

bool History::record(int r, int c)
{
    if (r < 1 || c < 1 || r > m_rows || c > m_cols)
        return false;
    
    if (m_grids[r-1][c-1] == '.')
        m_grids[r-1][c-1] = 'A';
    else if (m_grids[r-1][c-1] < 'Z')
        m_grids[r-1][c-1] += 1;
    
    return true;
}

void History::display() const
{
    
    clearScreen();
    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_cols; c++)
        {
            cout << m_grids[r][c];
        }
        
        cout << endl;
    }
    cout << endl;
}

