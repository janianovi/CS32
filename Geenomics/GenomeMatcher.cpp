#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Trie.h"
#include <map>
#include <utility>

using namespace std;

class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
    int searchLength;
    vector<Genome> genomeList;
    Trie<pair<int, int>> geneTrie;
    
};


GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    searchLength = minSearchLength;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    //push back the genome
    genomeList.push_back(genome);
    for (int i = 0; i <= genome.length() - searchLength; i++)
    {
        string gene = "";
        genome.extract(i, searchLength, gene);
        pair<int, int> sequence(genomeList.size()-1, i);
        geneTrie.insert(gene, sequence); //insert the extracted genome into pair

    }
}

int GenomeMatcherImpl::minimumSearchLength() const
{
    return searchLength;
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    
    if (fragment.length() < minimumLength || minimumLength < searchLength)
        return false;
    
    //store genome into a vector pair
    string fragEnd = fragment.substr(searchLength);
    vector<pair<int, int>> genomePair = geneTrie.find(fragment.substr(0, searchLength), exactMatchOnly);
    
    
    for (int i = 0; i < genomePair.size(); i++)
    {
        //hold the position of the genome
        Genome gene = genomeList[genomePair[i].first];
        int genePosition = genomePair[i].second;
        string geneSequence = "";
        string geneEnd = "";
        int totalWord = genePosition + searchLength;
        //variables used for testing for matches
        int searchMin = searchLength;
        bool goodGene = true;
        bool error = true;
        
        //extracting the genes into the first sequence of minimum length and total length
        gene.extract(genePosition, searchLength, geneSequence);
        gene.extract(totalWord, gene.length() - totalWord, geneEnd);
        
        if (fragment.substr(0, searchLength) == geneSequence) //checks to see if the first sequence is the same
            error = false;
        
        
        for (int k = 0; k < fragEnd.length(); k++)
        {
            if (fragEnd.at(k) != geneEnd.at(k)) //check if there are any unmatching characters
            {
                if (exactMatchOnly)
                {
                    if (searchMin < minimumLength) //break if not a valid genome
                    {
                        goodGene = false;
                    }
                    break;
                }
                
                if (!error) //check for one error within gene string
                {
                    searchMin++;
                    error = true;
                    continue;
                }
                
                if (error && (searchMin < minimumLength)) //not a match, too many errors
                {
                    goodGene = false;
                }
                break;
            }
            searchMin++; //continue to the next letter
        }
        
        if (!goodGene) //break out of current iteration if not a good genome
            continue;
        
        //push back the genome that is accurate
        DNAMatch DNAgene;
        DNAgene.genomeName = gene.name();
        DNAgene.length = searchMin;
        DNAgene.position = genePosition;
        
        matches.push_back(DNAgene);
    }
    
    return true;
    
}


bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    if (fragmentMatchLength < searchLength)
        return false;
    
    //map containing the genome and position
    map<string, int> genomePair;
    string temp;
    
    for (int i = 0; i < genomeList.size(); i++)
    {
        genomePair[genomeList[i].name()] = 0; //sets the name
    }
    
    int queryPercent = query.length() / fragmentMatchLength; //calculate percentage
    
    for (int i = 0; i < queryPercent; i++)
    {
        
        query.extract(i * fragmentMatchLength, fragmentMatchLength, temp);
        vector<DNAMatch> simGenes;//create vector to hold the matches
        
        if (!findGenomesWithThisDNA(temp, fragmentMatchLength, exactMatchOnly, simGenes)) //if no match
        {
            return false;
        }
        
        for (int k = 0; k < simGenes.size(); k++)
        {
            genomePair[simGenes[k].genomeName]++;
        }
    }
    
    // for inserting the genomes in order
    for (int i = 0; i < genomeList.size(); i++)
    {
        double percentage = (static_cast<double>(genomePair[genomeList[i].name()]) / queryPercent) * 100;
        
        if (percentage > matchPercentThreshold)
        {
            //create a new GenomeMatch to push in
            GenomeMatch DNAgene;
            DNAgene.genomeName = genomeList[i].name();
            DNAgene.percentMatch = percentage;
            
            if (results.size() == 0) //push back the percentage
            {
                results.push_back(DNAgene);
                continue;
            }
            
            //check which element should go into the vector
            int position = 0; //keeps track of the position of the inserted element
            while (results[position].percentMatch >= percentage)
            {
                position++;
            }
            
            //compares name if similar percentages
            if (results[position].percentMatch == percentage && results[position].genomeName < genomeList[i].name())
            {
                position++;
            }
            
            results.insert(results.begin() + position, DNAgene); //insert gene into vector
        }
    }
    
    return true;
}



//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
