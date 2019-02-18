//
//  main.cpp
//  Set
//
//  Created by Janis Chen on 1/23/19.
//  Copyright © 2019 Test Project. All rights reserved.
//

#include "Set.h"

Set::Set() //constructor
{
    //creating an empty set
    m_size = 0;
    head = nullptr;
    tail = nullptr;
}


Set::~Set() //destructor
{
    Node *ptr = head;
    while (ptr != nullptr)
    {
        Node *kill = ptr;
        ptr = ptr->next;
        delete kill;
    }
}

Set::Set(const Set& src) //copy constructor
{
    m_size = 0; //create a new set
    head = nullptr;
    tail = nullptr;
    Node *ptr = src.head;
    while (ptr != nullptr)
    {
        insert(ptr->search);
        ptr = ptr->next;
    }
}

Set& Set::operator= (const Set& src) //assignment operator
{
    if (&src == this)
        return *this; //do nothing
    
    Node *ptr = head;
    while (ptr != nullptr) //delete all nodes
    {
        Node *now = ptr->next;
        delete ptr;
        ptr = now;
    }
    
    head = nullptr; //make empty list
    tail = nullptr;
    m_size = 0;
    
    Node *second = src.head; //new node to head
    while (second != nullptr) //fill list
    {
        insert(second->search);
        second = second->next;
    }
    
    return *this;
}


bool Set::empty() const //returns if list is empty
{
    if (m_size == 0 && head == nullptr)
        return true;
    else
        return false;
}

int Set::size() const //returns size of list
{
    return m_size;
}

bool Set::insert(const ItemType& value)
{
    if (contains(value) || m_size >= DEFAULT_MAX_ITEMS) //checks for bad inputs
        return false;
    
    Node *ptr = new Node;
    ptr->search = value;
    m_size++;
    
    if (head == nullptr) //if empty set
    {
        ptr->next = nullptr;
        ptr->prev = nullptr;
        head = ptr; //assign head and tail to new value
        tail = ptr;
    }
    if (m_size >= 1) //if not empty set
    {
        tail->next = ptr; //add value to the end of list
        ptr->prev = tail;
        ptr->next = nullptr;
        tail = ptr;
    }
    
    return true;
}

bool Set::erase(const ItemType& value)
{
    if (head == nullptr || !contains(value)) //checks boundary
        return false;
    
    if (head->search == value) //if only one node
    {
        Node *kill = head;
        head = kill->next;
        delete kill;
        m_size--;
        return true;
    }
    
    Node *ptr = head;
    
    while (ptr != nullptr) //for all other nodes
    {
        if (ptr->next != nullptr && ptr->next->search == value)
        {
            Node *kill = ptr->next; //set kill node to the erase node
            ptr->next = kill->next;
            delete kill;
            m_size--;
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}


bool Set::contains(const ItemType& value) const
{
    if (head == nullptr) //bad inputs or empty set
        return false;
    
    for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) //loop through list
    {
        if (ptr->search == value) //if found value
            return true;
    }
    return false;
}

bool Set::get(int pos, ItemType& value) const
{
    if (pos >= m_size || head == nullptr || pos < 0) //check for bad pos value or empty list
        return false;
    
    Node *ptr = head; //create node
    
    while (ptr != nullptr)
    {
        Node *free = head; //create new Node to compare with ptr
        int counter = 0; //create variable to match with pos
        while (free != nullptr) //run through entire list
        {
            if (ptr->search > free->search) //if value of ptr is greater than value of free
                counter++; //add to counter
            free = free->next;
        }
        if (counter == pos) //if counter matches pos
        {
            value = ptr->search;
            return true; //return true
        }
        ptr = ptr->next;
    }
    return false;
}


void Set::swap(Set& other)
{
    if (head == nullptr) //empty set
        return;
    
    Node* tempSet = head; //swaps head, tail, and size
    head = other.head;
    other.head = tempSet;
    
    tempSet = tail;
    tail = other.tail;
    other.tail = tempSet;
    
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
    
}

//Set Algorithms

void unite(const Set& s1, const Set& s2, Set& result)
{
    ItemType temp; //create new ItemType and Set
    Set newSet;
    
    for (int i = 0; i < s1.size(); i++)
    {
        s1.get(i, temp);
        newSet.insert(temp); //add all s1 values into new set
    }
    
    for (int i = 0; i < s2.size(); i++)
    {
        s2.get(i, temp);
        if (!newSet.contains(temp))
            newSet.insert(temp); //add remaining s2 values not in s1 into new set
    }
    result = newSet;
}

void subtract(const Set& s1, const Set& s2, Set& result)
{
    ItemType temp; //create new ItemType and Set
    Set newSet;
    
    for (int i = 0; i < s1.size(); i++)
    {
        s1.get(i, temp);
        newSet.insert(temp); //add all s1 values into new set
    }
    
    for (int i = 0; i < s2.size(); i++)
    {
        s2.get(i, temp);
        if (newSet.contains(temp))
            newSet.erase(temp); //delete s2 values found in s1
    }
    result = newSet;
}










