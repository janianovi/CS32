#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>
#include <set>

template<typename ValueType>
class Trie
{
public:
    Trie();
    ~Trie();
    void reset();
    void insert(const std::string& key, const ValueType& value);
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;
    
    // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
private:
    struct Node
    {
        Node(char IDS)
        {
            ID = IDS;
        }
        
        std::vector<ValueType> value;
        std::vector<Node*> branch;
        char ID;
    };
    Node* root;
    void deleteNode(Node* deletion);
    std::vector<ValueType> exactMatch(const std::string& key, Node* exact) const;
    std::vector<ValueType> SnipMatch(const std::string& key, Node* exact, int error) const;
};


template<typename ValueType>
Trie<ValueType>::Trie()
{
    root = new Node(' ');
}

template<typename ValueType>
Trie<ValueType>::~Trie()
{
    deleteNode(root);
}


template<typename ValueType>
void Trie<ValueType>::reset()
{
    deleteNode(root);
    root = new Node;
}

template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value)
{
    Node* exact = root;
    
    for(int i = 0; i < key.length(); i++) //going through the length of key
    {
        bool found = false;
        
        for (int j = 0; j < exact->branch.size(); j++)
        {
            if (key[j] == exact->branch[j]->ID) //if key matches ID
            {
                found = true;
                exact = exact->branch[j];
                break;
            }
        }
        
        if (!found)
        {
            Node* add = new Node(key[i]); //if not found, include a new node
            exact->branch.push_back(add);
            exact = add;
        }
        
    }
    exact->value.push_back(value);
}


template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const
{
    if(exactMatchOnly)
        return exactMatch(key, root);
    
    return SnipMatch(key, root, 0);
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::exactMatch(const std::string& key, Node* exact) const
{
    std::vector<ValueType> gene;
    
    if (root->branch.size() == 0)
        return gene;
    
    if (key.size() == 0) //if there is no key, return value
        return exact->value;
    
    //going through to check each branch
    for (int i = 0; i < exact->branch.size(); i++)
    {
        if (exact->branch[i]->ID == key[0]) //return match if found
        {
            return exactMatch(key.substr(1), exact->branch[i]);
        }
    }
    return gene;
    
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::SnipMatch(const std::string& key, Node* exact, int error) const
{
    std::vector<ValueType> gene;
    std::vector<ValueType> finalGene;
    
    if (error > 1 || (root->branch.size() == 0))
        return gene; //too many errors
    
    if (key.size() == 0)
        return exact->value;
    
    //check to see which other ones match
    for (int i = 0; i < exact->branch.size(); i++)
    {
        int temp = error;
        if (exact->branch[i]->ID != key[0])
            temp++;
        if (exact == root && temp != 0) //no errors in the beginning
            continue;
        
        std::vector<ValueType> snip = SnipMatch(key.substr(1), exact->branch[i], temp);
        finalGene.insert(finalGene.end(), snip.begin(), snip.end()); //insert in function
    }
    return finalGene;
    
}


template<typename ValueType>
void Trie<ValueType>::deleteNode(Node* deletion)
{
    if (deletion == nullptr)
        return;
    
    for(int i = 0; i < deletion->branch.size(); i++)
    {
        deleteNode(deletion->branch[i]);
    }
    
    delete deletion;
}












#endif // TRIE_INCLUDED
