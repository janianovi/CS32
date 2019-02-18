//
//  main.cpp
//  progress
//
//  Created by Janis Chen on 1/28/19.
//  Copyright © 2019 Test Project. All rights reserved.
//
// test default constructor

#include "Set.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>

using namespace std;

string spaces(string infix) //deletes all spaces from string
{
    string temp = "";
    for (int i = 0; i < infix.size(); i++)
    {
        if (infix[i] != ' ')
            temp += infix[i];
    }
    
    return temp;
}

int prec(char op) //returns an int to represent the order of operator precedence
{
    if (op == '!')
        return 3;
    else if (op == '&')
        return 2;
    else if (op == '|')
        return 1;
    else
        return -1;
}

bool validString(string infix) //checks if the string is valid
{
    infix = spaces(infix); //removes spaces
    
    if (infix.empty())
        return false;
    else if (infix[0] == '&' || infix[0] == '|' || infix[0] == ')') //checks for bad placement of characters
        return false;
    else if (infix[infix.size() - 1] == '&' || infix[infix.size() - 1] == '|' || infix[infix.size() - 1] == '!' || infix[infix.size() - 1] == '(')
        return false;
    
    
    
    int open = 0; //for counting parenthesis
    int close = 0;
    
    for (int i = 0; i < infix.size(); i++)
    {
        if(infix[i] == '(') //error checking for parenthesis
        {
            open++;
            if (infix[i+1] == '&' || infix[i+1] == '|' || infix[i+1] == ')')
                return false;
        }
        else if(infix[i] == ')')
        {
            close++;
            if(infix[i-1] == '&' || infix[i-1] == '|' || infix[i-1] == '!' || infix[i+1] == '(')
                return false;
        }
        else if(isalpha(infix[i])) //error checking for letters
        {
            if(isalpha(infix[i+1]) || infix[i+1] == '(' || infix[i+1] == '!')
                return false;
        }
        else if(infix[i] == '!') //error checking for operators
        {
            if(infix[i+1] == '&' || infix[i+1] == '|')
                return false;
        }
        else if(infix[i] == '|')
        {
            if(infix[i+1] == '|')
                return false;
        }
        else if(infix[i] == '&')
        {
            if(infix[i+1] == '&')
                return false;
        }
    }
    
    if(open != close)
        return false;
    
    return true;
    
}

string inToPost(string infix) //changes from infix to postfix
{
    infix = spaces(infix); //remove spaces
    string postfix = "";
    stack<char> symbols;
    for (int i = 0; i< infix.size(); i++)
    {
        switch(infix[i]) //switch statement from pseudocode
        {
            case '(':
                symbols.push(infix[i]);
                break;
            case ')':
                while(symbols.top() != '(')
                {
                    postfix += symbols.top();
                    symbols.pop();
                }
                symbols.pop();
                break;
            case '!':
            case '&':
            case '|':
                while(!symbols.empty() && symbols.top() != '(' && prec(infix[i]) <= prec(symbols.top()))
                {
                        postfix += symbols.top();
                        symbols.pop();
                }
                symbols.push(infix[i]);
                break;
            default: //anything that is a character and not a operator/parentheses
                postfix += infix[i];
                
        }
    }
    while (!symbols.empty())
    {
        postfix += symbols.top();
        symbols.pop();
    }
    return postfix;
    
}


int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result) //evaluates the string
{
    if (!validString(infix)) //checks for valid string
        return 1;
    
    postfix = inToPost(infix);
    
    stack<bool> operand;
    
    for(int i = 0; i < postfix.size(); i++)
    {
        if(isalpha(postfix[i])) //evaluating operand
        {
            if(trueValues.contains(postfix[i]) && !falseValues.contains(postfix[i]))
                operand.push(true);
            else if(!trueValues.contains(postfix[i]) && falseValues.contains(postfix[i]))
                operand.push(false);
            else if(!trueValues.contains(postfix[i]) && !falseValues.contains(postfix[i]))
                return 2;
            else
                return 3;
        }
        else
        {
            if(postfix[i] == '&' || postfix[i] == '|') //evaluating binary operators
            {
            
                bool second = operand.top();
                operand.pop();
                bool first = operand.top();
                operand.pop();
            
                if(postfix[i] == '&')
                {
                    result = first && second;
                    operand.push(result);
                }
                else if(postfix[i] == '|')
                {
                    result = first || second;
                    operand.push(result);
                }
            }
        }
    }
    
    
    result = operand.top();
    return 0;

}

int main()
{
    string trueChars  = "tywz";
    string falseChars = "fnx";
    Set trues;
    Set falses;
    for (int k = 0; k < trueChars.size(); k++)
        trues.insert(trueChars[k]);
    for (int k = 0; k < falseChars.size(); k++)
        falses.insert(falseChars[k]);
    
    string pf;
    bool answer;
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  answer);
    assert(evaluate("y|", trues, falses, pf, answer) == 1);
    assert(evaluate("n t", trues, falses, pf, answer) == 1);
    assert(evaluate("nt", trues, falses, pf, answer) == 1);
    assert(evaluate("()", trues, falses, pf, answer) == 1);
    assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
    assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
    assert(evaluate("(n&(t|7)", trues, falses, pf, answer) == 1);
    assert(evaluate("", trues, falses, pf, answer) == 1);
    assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
           &&  pf == "ff!tn&&|"  &&  !answer);
    assert(evaluate(" x  ", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  !answer);
    trues.insert('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 3);
    falses.erase('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  answer);
    trues.erase('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 2);
    falses.insert('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  !answer);
    cout << "Passed all tests" << endl;
    
}


