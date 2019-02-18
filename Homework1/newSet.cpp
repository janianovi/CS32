//
//  newSet.cpp
//  Set
//
//  Created by Janis Chen on 1/19/19.
//  Copyright © 2019 Test Project. All rights reserved.
//

#include "newSet.h"


Set::Set()
{
    m_size = 0;
    m_max = DEFAULT_MAX_ITEMS;
    m_sets = new ItemType[DEFAULT_MAX_ITEMS];
}

Set::Set(int maximum)
{
    //maybe something here?
    
    m_max = maximum;
    m_size = 0;
    m_sets = new ItemType[m_max];
    
}

Set::Set(const Set& src)
{
    m_size = src.m_size;
    m_max = src.m_max;
    m_sets = new ItemType[m_max];
    for (int i = 0; i < m_size; i++)
        m_sets[i] = src.m_sets[i];
}

Set::~Set()
{
    delete [] m_sets;
}

Set& Set::operator= (const Set& src)
{
    if (&src == this)
        return *this;
    
    delete [] m_sets;
    m_size = src.m_size;
    m_max = src.m_max;
    m_sets = new ItemType[m_max];
    for (int i = 0; i < m_size; i++)
        m_sets[i] = src.m_sets[i];
    
    return *this;
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
    if (m_size >= m_max)
        return false;
    
    for(int i = 0; i < m_size; )
    {
        if(contains(value))
            return false;
        if(value > m_sets[i])
            i++;
        else
        {
            for(int j= m_size; j > i; j--)
            {
                m_sets[j] = m_sets[j-1];
            }
            m_sets[i] = value;
            m_size++;
            return true;
        }
        i++;
    }
    m_sets[m_size] = value;
    m_size++;
    return true;
}

bool Set::erase(const ItemType& value)
{
    int temp;
    
    for (temp = 0; temp < size(); temp++)
    {
        if (value == m_sets[temp])
        {
            for (int i = temp; i < size() - 1; i++)
                m_sets[i] = m_sets[i+1];
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
        if (value == m_sets[i])
            return true;
    }
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    if (i < 0 || i >= size())
        return false;
    
    value = m_sets[i];
    
    return true;
}


void Set::swap(Set& other)
{
    Set secSet = *this;
    *this = other;
    other = secSet;
    
}



