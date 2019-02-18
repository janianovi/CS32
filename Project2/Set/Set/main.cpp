//
//  main.cpp
//  Set
//
//  Created by Janis Chen on 1/25/19.
//  Copyright © 2019 Test Project. All rights reserved.
//
#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Set colors;
    assert(colors.size() == 0 && colors.empty());
    
    // test contains
    assert(!colors.contains("blue"));    // empty set contains nothing
    colors.insert("blue");
    assert(colors.contains("blue"));    // set contains item
    assert(!colors.contains("Blue"));    // set contains item in different cases
    assert(!colors.contains("red"));    // set doesn't contain item
    
    // test insert
    Set animals;
    assert(animals.insert("cat"));        // empty set
    assert(animals.insert("baffoon"));        // insert in front of one-item set
    // animals: baffoon cat
    assert(animals.insert("aardvark"));    // insert in front of set
    assert(animals.insert("bat") && animals.size() == 4);    // insert in middle of set
    
    Set birds;
    birds.insert("cockatiel");
    assert(birds.insert("conure"));        // insert in back of one-item set
    assert(birds.insert("owl"));        // insert in back of set
    assert(!birds.insert("conure") && birds.size() == 3);    // item already in set
    
    // test erase
    Set countries;
    assert(!countries.erase("america") && countries.size() == 0); // empty set
    
    assert(!colors.erase("red"));        // no matching item in one item set
    assert(colors.erase("blue") && colors.size() == 0); // erase item in one item set
    
    assert(birds.erase("cockatiel") && birds.size() == 2);    // erase first item in set
    
    assert(animals.erase("baffoon"));        // erase middle item in set
    assert(animals.erase("cat"));        // erase last item in set
    assert(!animals.erase("zebra") && animals.size() == 2);     // no matching item in set
    
    // test get
    ItemType item = "banana";
    assert(!countries.get(5, item) && item == "banana");    // empty set
    
    assert(birds.get(0, item) && item == "conure");        // get 0th item
    
    animals.insert("parrot");
    assert(animals.get(1, item) && item == "bat");        // get middle item
    assert(animals.get(2, item) && item == "parrot");    // get last item
    assert(!animals.get(5, item) && item == "parrot");    // get invalid item
    
    // test swap
    animals.swap(birds);                // normal swap
    assert(animals.size() == 2 && birds.size() == 3);
    
    animals.swap(birds);
    animals.swap(colors);            // swap with empty set
    assert(animals.size() == 0 && colors.size() == 3);
    
    // test copy constructor
    Set bipeds = birds;                // copy non-empty set
    Set continents = countries;            // copy empty set
    
    // test assignment operator
    animals = bipeds;                // normal assignment
    animals = countries;                // assignment to empty set
    birds = birds;                // assignment to self
    
    // test unite
    Set s1, s2, result;
    unite(s1, s2, result);            // empty sets
    assert(result.size() == 0);
    
    s1.insert("a");
    s1.insert("b");
    s1.insert("c");
    s1.insert("d");
    s1.insert("e");
    
    s2.insert("a");
    s2.insert("b");
    s2.insert("c");
    s2.insert("d");
    s2.insert("e");
    
    unite(s1, s2, result);            // s1 and s2 are same
    assert(result.size() == 5);
    
    s1.insert("f");
    s1.insert("g");
    unite(s1, s2, result);            // s1 has items s2 doesn't have
    assert(result.size() == 7);
    
    s2.insert("h");
    s2.insert("i");
    unite(s1, s2, result);            // s2 has items s1 doesn't have
    assert(result.size() == 9);
    
    s1.insert("j");
    s2.insert("k");
    unite(s1, s2, result);            // s1 and s2 both have unique items
    assert(result.size() == 11);
    
    unite(s1, s2, s1);                // s1 and result are the same
    assert(s1.size() == 11);
    
    s1.erase("a");
    s2.erase("b");
    
    unite(s1, s2, s2);                // s2 and result are the same
    assert(s2.size() == 11);
    
    unite(s1, s1, result);            // s2 and s1 are the same
    assert(result.size() == 10);
    
    // testing subtract
    Set alpha, beta, alphabeta;
    subtract(alpha, beta, alphabeta);    // empty sets
    
    
    alpha.insert("a");
    alpha.insert("b");
    alpha.insert("c");
    alpha.insert("d");
    alpha.insert("e");
    
    beta.insert("d");
    beta.insert("e");
    
    
    subtract(alpha, beta, alphabeta);    // subtract s2 from s1 with leftovers
    assert(alphabeta.size() == 3);
    
    
    alpha.insert("d");
    alpha.insert("e");
    
    beta.insert("a");
    beta.insert("b");
    beta.insert("c");
    
    
    subtract(alpha, beta, alphabeta);    // subtract s2 from s1 with nothing left
    assert(alphabeta.size() == 0);
    
    alpha.insert("a");
    alpha.insert("b");
    alpha.insert("c");
    
    subtract(alpha, beta, alphabeta);    // s2 has more items than in s1
    assert(alphabeta.size() == 0);
    
    
    alpha.insert("a");
    alpha.insert("b");
    alpha.insert("c");
    alpha.insert("d");
    alpha.insert("e");
    alpha.insert("f");
    
    subtract(alpha, beta, alpha);        // s1 is the same as result
    assert(alpha.size() == 1);
    
    alpha.insert("a");
    alpha.insert("b");
    alpha.insert("c");
    
    subtract(alpha, beta, beta);        // s2 is the same as result
    assert(beta.size() == 1);
    
    cerr << "Passed all tests" << endl;
}

