//
//  SSNSet.cpp
//  Set
//
//  Created by Janis Chen on 1/17/19.
//  Copyright © 2019 Test Project. All rights reserved.
//

#include "SSNSet.h"
#include <iostream>
using namespace std;


SSNSet::SSNSet()
{
    //default
}
// Create an empty SSN set.

bool SSNSet::add(unsigned long ssn)
{
    return newSet.insert(ssn);
}

int SSNSet::size() const
{
    return newSet.size();
}

void SSNSet::print() const
{
    for(int i = 0; i < newSet.size(); i++)
    {
        unsigned long value;
        newSet.get(i, value);
        cout << value << endl;
    }
}
// Write every SSN in the SSNSet to cout exactly once, one per
// line.  Write no other text.
