//
//  History.h
//  main
//
//  Created by Janis Chen on 1/9/19.
//  Copyright © 2019 Test Project. All rights reserved.
//

#ifndef History_h
#define History_h

#include "globals.h"

class Arena;

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    
private:
    char    m_grids[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    
};

#endif
