//
//  Set.h
//  Set
//
//  Created by Janis Chen on 1/23/19.
//  Copyright © 2019 Test Project. All rights reserved.
//

#ifndef Set_h
#define Set_h
#include <string>

const int DEFAULT_MAX_ITEMS = 250;

using ItemType = std::string;

class Set
{
public:
    Set();
    //constructor
    
    ~Set();
    //destructor
        
    Set(const Set& src);
    //copy constructor
    
    Set& operator=(const Set& src);
    //assignment operator
    
    bool empty() const;
    //returns if set is empty
    
    int size() const;
    //returns size of set
    
    bool insert(const ItemType& value);
    // Insert value into the set if it is not already present.
    
    bool erase(const ItemType& value);
    // Remove the value from the set if present.
    
    bool contains(const ItemType& value) const;
    // Return true if the value is in the set, otherwise false.
    
    bool get(int pos, ItemType& value) const;
    // opy into value the item in the set that is strictly greater than exactly i items in the set and return true.
    
    void swap(Set& other);
    // Exchange the contents of this set with the other one.
    
    
private:
    struct Node
    {
        ItemType search;
        Node* next;
        Node* prev;
    };
    int m_size;
    Node* head;
    Node* tail;
};

void unite(const Set& s1, const Set& s2, Set& result);
//adds sets together into one set

void subtract(const Set& s1, const Set& s2, Set& result);
//subtracts similar values from both sets


#endif /* Set_h */
