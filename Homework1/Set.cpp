//
//  main.cpp
//  Set
//
//  Created by Janis Chen on 1/16/19.
//  Copyright © 2019 Test Project. All rights reserved.
//

#include "Set.h"
#include <iostream>
#include <string>
using namespace std;


Set::Set()
{
    m_size = 0;
}

bool Set::empty() const
{
    if (m_size == 0)
        return true;
    else
        return false;
}

int Set::size() const
{
    return m_size;
}

bool Set::insert(const ItemType& value)
{
    if (size() >= DEFAULT_MAX_ITEMS)
        return false;
    
    for (int i = 0; i < size();)
    {
        if (contains(value))
            return false;
        if (value > sets[i])
            i++;
        else
        {
            for (int k = m_size; k > i; k--)
                sets[k] = sets[k-1];
            sets[i] = value;
            m_size++;
            return true;
        }
        i++;
    }
    
    sets[m_size] = value;
    m_size++;
    return true;
}

bool Set::erase(const ItemType& value)
{
    int temp;
    
    for (temp = 0; temp < size(); temp++)
    {
        if (value == sets[temp])
        {
            for (int i = temp; i < size() - 1; i++)
                sets[i] = sets[i+1];
            m_size--;
            return true;
        }
    }
    
    return false;
}


bool Set::contains(const ItemType& value) const
{
    for (int i = 0; i < size(); i++)
    {
        if (value == sets[i])
            return true;
    }
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    if (i < 0 || i >= size())
        return false;
    
    value = sets[i];
    
    return true;
}


void Set::swap(Set& other)
{
    m_size = other.m_size;
    
    for (int i = 0; i < m_size; i++)
    {
        sets[i] = other.sets[i];
    }
    
}




