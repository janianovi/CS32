#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <fstream>

using namespace std;

class Genome;
class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
    
private:
    string geneName;
    string geneString;
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    geneName = nm;
    geneString = sequence;
}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes)
{
    genomes.clear(); //clears if not empty
    
    char c;
    string empty;
    string name = "";
    string sequence = "";
    getline(genomeSource, empty);
    
    if (empty[0] != '>')
        return false;
    name = empty.substr(1); //set name to after >
    
    char placeholder = 'x';
    while (genomeSource.get(c))
    {
        if (c == '\n' && placeholder == '\n') //check that none of them are empty lines
            return false;
        placeholder = c;
        if (c != '>')
        {
            c = toupper(c);
            if (c == 'A' || c == 'C' || c == 'T' || c == 'G' || c == 'N') //add to sequence if these are the characters
                sequence += (c);
            else if (c != '\n')
                return false;
        }
        else
        {
            genomes.push_back(Genome(name, sequence)); //push back the sequence
            getline(genomeSource, empty);
            if (empty.size() == 0)
                return false;
            name = empty; //reset the variables
            sequence = "";
        }
    }
    
    Genome g(name, sequence);
    genomes.push_back(g);
    
    return true;
}

int GenomeImpl::length() const
{
    return static_cast<int>(geneString.size());
}

string GenomeImpl::name() const
{
    return geneName;
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    if (geneString.size() < position + length || position < 0 || length < 0)
        return false;
    
    fragment = geneString.substr(position, length);
    return true;
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes)
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}
