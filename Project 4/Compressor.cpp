#include "provided.h"
#include "substituteHashTable.h"
#include <string>
#include <vector>
using namespace std;

void Compressor::compress(const string& s, vector<unsigned short>& numbers)
{
    unsigned short N= s.length();
    
    unsigned short C;
    if(N/2 + 512)
        C= (N/2)+512;
    else
        C=16384;
        
    HashTable<string, unsigned short> H(C*2, C);
    for(int i=0; i<256; i++)
    {
        char c=static_cast<char>(i);
        string s="";
        s+=c;
        H.set(s, i, true);
    }
    unsigned int nextFreeID=256;
    string runSoFar="";
    
    for(int c=0; c<N; c++)
    {
        string expandedRun=runSoFar + s[c];
        unsigned short value;
        if(H.get(expandedRun, value))
        {
            runSoFar=expandedRun;
            continue;
        }else
        {
            unsigned short x;
            H.get(runSoFar, x);
            numbers.push_back(x);
            H.touch(runSoFar);
            runSoFar="";
            
            unsigned short cv;
            string ch="";
            ch= ch+ s[c];
            H.get(ch, cv);
            numbers.push_back(cv);
            
            if(!H.isFull())
            {
                H.set(expandedRun, nextFreeID);
                nextFreeID++;
            }else
            {
                string key;
                unsigned short val;
                H.discard(key, val);
                H.set(expandedRun, val);
            }
        }
    }
    
    if(runSoFar.size()!=0)
    {
        unsigned short x;
        H.get(runSoFar, x);
        numbers.push_back(x);
    }
    
    numbers.push_back(C);
}

bool Compressor::decompress(const vector<unsigned short>& numbers, string& s)
{
    unsigned short Capacity= numbers.back();
    HashTable<unsigned short, string> H(Capacity*2, Capacity);
    
    for(int i=0; i<256; i++)
    {
        char c=static_cast<char>(i);
        string s="";
        s+=c;
        H.set(i, s, true);
    }
    unsigned int nextFreeID=256;
    string runSoFar="";
    string output="";
    for(int i=0; i<numbers.size()-1; i++)
        {
            unsigned short us= numbers.at(i);
            if(us<=255)
            {
                string val="";
                H.get(us, val);
                output+=val;
                
                if(runSoFar.size()==0)
                {
                    runSoFar+=val;
                    continue;
                }
                else
                {
                   string expandedRun=runSoFar+ val;
                    if(!H.isFull())
                    {
                        H.set(nextFreeID, expandedRun);
                        nextFreeID++;
                    }
                    else
                    {
                        string val;
                        unsigned short key;
                        H.discard(key, val);
                        H.set(key, expandedRun);
                    }
                    runSoFar="";
                    continue;
                }
            }
            else
            {
                string S;
                if(!H.get(us, S))
                {
                    //cout<<"FAILURE";
                    return false;
                }
                else
                {
                    H.touch(us);
                    output+=S;
                    runSoFar=S;
                    continue;
                }
            }
        }
   
    s=output;
    return true;
}
