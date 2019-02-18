//
//  SSNSet.h
//  Set
//
//  Created by Janis Chen on 1/17/19.
//  Copyright © 2019 Test Project. All rights reserved.
//

#ifndef SSNSet_h
#define SSNSet_h

#include "Set.h"

class SSNSet
{
public:
    SSNSet();
    
    bool add(unsigned long ssn);
    
    int size() const;
    
    void print() const;

    
private:
    Set newSet;
};

#endif /* SSNSet_h */
