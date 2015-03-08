#include "provided.h"
#include <string>
#include <vector>
using namespace std;


const size_t BITS_PER_UNSIGNED_SHORT = 16;

string convertNumberToBitString(unsigned short number);
bool convertBitStringToNumber(string bitString, unsigned short& number);


string BinaryConverter::encode(const vector<unsigned short>& numbers)
{
    string encoding="";
    for(int i=0; i<numbers.size(); i++)
    {
        string s=convertNumberToBitString(numbers[i]);
        for(int i=0; i<s.size(); i++)
        {
            if(s[i]=='1')
                encoding+='\t';
            else if(s[i]=='0')
                encoding+=' ';
        }
    }
  return encoding;  // This compiles, but may not be correct
}

bool BinaryConverter::decode(const string& bitString, vector<unsigned short>& numbers)
{
    if(bitString.size()%16!=0)
        return false;
    
    for(int i=0; i<bitString.size(); i++)
    {
        if(bitString[i]!='\t'&& bitString[i]!=' ')
            return false;
    }
    
    unsigned short size=numbers.size();
    for(int i=size-1; i>=0; i--)
        numbers.erase(numbers.begin()+i);
    
    string newBitString="";
    
    for(int i=0; i<bitString.size(); i++)
    {
        if(bitString[i]=='\t')
            newBitString+='1';
        else if(bitString[i]==' ')
            newBitString+='0';
    }
    
    int count=0;
    string partBitString="";
    for(int i=count; i<newBitString.size(); i++)
    {
        count++;
        partBitString+=newBitString[i];
        if(partBitString.size()==16)
        {
            unsigned short num=0;
            
            convertBitStringToNumber(partBitString, num);
            numbers.push_back(num);
            partBitString="";
        }
    }
    
    return true;
}

string convertNumberToBitString(unsigned short number)
{
    string result(BITS_PER_UNSIGNED_SHORT, '0');
    for (size_t k = BITS_PER_UNSIGNED_SHORT; number != 0; number /= 2)
    {
        k--;
        if (number % 2 == 1)
            result[k] = '1';
    }
    return result;
}

bool convertBitStringToNumber(string bitString, unsigned short& number)
{
    if (bitString.size() != BITS_PER_UNSIGNED_SHORT)
        return false;
    number = 0;
    for (size_t k = 0; k < bitString.size(); k++)
    {
        number *= 2;
        if (bitString[k] == '1')
            number++;
        else if (bitString[k] != '0')
            return false;
    }
    return true;
}
