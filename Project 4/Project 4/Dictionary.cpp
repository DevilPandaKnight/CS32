// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <algorithm>  // for swap
#include <iostream>
using namespace std;

#define MAXBUCKETS 50000

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

  // This class does the real work of the implementation.


class DictionaryImpl
{
  public:
    DictionaryImpl() {}
    ~DictionaryImpl() {/*delete all node*/}
    void insert(string word);
    void lookup(string letters, void callback(string));
  private:
    list<string> table[MAXBUCKETS];
    unsigned hashString(string& s);
};



unsigned DictionaryImpl::hashString(string& s){
//	unsigned h = s[0];
//	unsigned a = 524287;
//	unsigned p = 2147483647;
//	for (int i = 1; i < s.length(); i++){
//		h = ((h*a) + s[i])%p;
//	}
//	return h%MAXBUCKETS;
    
    size_t len = s.length();
    unsigned h = s[0];
    for (int i = 1; i<len; i++) {
        h += s[i]<<len;
    }
    return h%MAXBUCKETS;
}

void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
    string temp;
	if (!word.empty()){
        temp = word;
        //sort(temp.begin(), temp.end());
        table[hashString(temp)].push_back(word);
	}
}



void DictionaryImpl::lookup(string letters, void callback(string)) 
{
    if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;
    //sort(letters.begin(), letters.end());
    list<string> l = table[hashString(letters)];

    string temp;
    //cout<<l.size()<<endl;
    for (auto iter = l.begin(); iter!=l.end(); iter++) {
        if ((*iter).length() == letters.length()) {
            temp = *iter;
            //sort(temp.begin(), temp.end());
            if (temp == letters) {
                callback(*iter);
            }
        }
    }
}
    
void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop off everything from "to" to end.
} 

  // Each successive call to this function generates the next permutation of the
  // characters in the parameter.  For example,
  //    string s = "eel";
  //    generateNextPermutation(s);  // now s == "ele"
  //    generateNextPermutation(s);  // now s == "lee"
  //    generateNextPermutation(s);  // now s == "eel"
  // You don't have to understand this function's implementation.
void generateNextPermutation(string& permutation)
{
    string::iterator last = permutation.end() - 1;
    string::iterator p;

    for (p = last; p != permutation.begin()  &&  *p <= *(p-1); p--)
        ;
    if (p != permutation.begin())
    {
        string::iterator q;
        for (q = p+1; q <= last  &&  *q > *(p-1); q++)
            ;
        swap(*(p-1), *(q-1));
    }
    for ( ; p < last; p++, last--)
        swap(*p, *last);
}

//******************** Dictionary functions **********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code.

Dictionary::Dictionary()
{
    m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters, callback);
}
