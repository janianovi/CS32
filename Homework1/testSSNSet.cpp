//
//  testSSNSet.cpp
//  Set
//
//  Created by Janis Chen on 1/19/19.
//  Copyright © 2019 Test Project. All rights reserved.
//

#include "SSNSet.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
    SSNSet set;
    
    set.add(5678);
    set.add(1234);
    set.print();
    
    assert(set.size() == 2);
    
    
    assert(set.add(567)== true);
    assert(set.add(123) == true);

    assert(set.size() == 4);
    set.print();
    
  
}

