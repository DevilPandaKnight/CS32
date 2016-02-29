#include "Dictionary.h"
#include "Time.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

static string testBasicCorrectness();
static string testThoroughCorrectness(size_t limit, const vector<string>& words,
                                      const vector<string>& probes);
static bool readWords(vector<string>& words, const char* wordFileName);
static void setupProbes(const vector<string>& words, vector<string>& probes);
static string doLookup(const Dictionary& d, string probe,
                       const vector<string>& expected);
double measureTime(size_t limit, const vector<string>& words,
                   const vector<string>& probes);

int main(int argc, char* argv[])
{
    const char* wordFileName = "/Users/jin/OneDrive/C++/CS32/Project 4/Project 4/words.txt";
    vector<string> words;
    if (!readWords(words, wordFileName))
    {
        cout << "Cannot open " << wordFileName << ", so cannot do thorough "
        << "correctness or performance tests!" << endl;
        return 1;
    }
    

    
    vector<string> probes;
    setupProbes(words, probes);

    string msg = testThoroughCorrectness(20, words, probes);
    if (msg.empty())
        cout << "Passed" << endl;
    
    double elapsed = measureTime(20, words, probes);
    cout << elapsed << " milliseconds" << endl;
}

//========================================================================
// Basic Correctness testing
//========================================================================

static string testBasicCorrectness()
{
    const auto data = {
        "cat", "dog", "rat", "MoUsE", "!bat!",
        "eel", "pig", "dodo", "cod", "tar"
    };
    struct Test
    {
        const char* probe;
        vector<string> expected;
    };
    const vector<Test> tests = {
        { "ta b@", { "bat" } },
        { "OSEum", { "mouse" } },
        { "art",   { "rat", "tar" } },
        { "doc",   { "cod" } },
        { "dddo",  { } },
        { "dooo",  { } },
    };

    Dictionary dict;
    for (char c = 'a'; c <= 'z'; c++)
        dict.insert(string(1,c));
    for (auto s : data)
        dict.insert(s);

    string msg;

    for (char c = 'a'; c <= 'z'; c++)
    {
        string s(1, c);
        msg = doLookup(dict, s, { s });
        if (!msg.empty())
            return msg;
    }

    msg = doLookup(dict, "aa", {});
    if (!msg.empty())
        return msg;

    for (const auto& t : tests)
    {
        string msg = doLookup(dict, t.probe, t.expected);
        if (!msg.empty())
            return msg;
    }

    dict.insert("fox");
    dict.insert("act");
    msg = doLookup(dict, "xof", { "fox" });
    if (!msg.empty())
        return msg;
    msg = doLookup(dict, "cat", { "act", "cat" });
    if (!msg.empty())
        return msg;

    return "";
}

//========================================================================
// Thorough Correctness testing
//========================================================================

// The thorough correctness test uses a global vector to record items passed
// to the callback function by the CorrectDictionary

vector<string> expected;

static void recordExpected(string s)
{
    expected.push_back(s);
}

static string testThoroughCorrectness(size_t limit, const vector<string>& words,
                                      const vector<string>& probes)
{
    Dictionary correctDict;
    Dictionary dict;
    for (const auto& w : words)
    {
        if (w.size() <= limit)
        {
            correctDict.insert(w);
            dict.insert(w);
        }
    }
    for (const auto& p : probes)
    {
        if (p.size() <= limit)
        {
            expected.clear();
            correctDict.lookup(p, recordExpected);
            sort(expected.begin(), expected.end());
            string msg = doLookup(dict, p, expected);
            if (!msg.empty())
                return msg;
        }
    }
    return "";
}



//========================================================================
// Read words
//========================================================================

static bool readWords(vector<string>& words, const char* wordFileName)
{
    ifstream wordFile(wordFileName);
    if ( ! wordFile)
        return false;

    words.reserve(26000);

    string word;
    while (getline(wordFile, word))
    {
        if (word.empty())
	    continue;
        if (word.back() == '\r')
        {
            word.pop_back();
            if (word.empty())
                continue;
        }
        words.push_back(word);
    }
    return true;
}

//========================================================================
// Set up probes
//========================================================================

static void setupProbes(const vector<string>& words, vector<string>& probes)
{
    probes.clear();
    probes.reserve(1 + 11 * words.size() / 10);

    for (size_t k = 0; k < words.size(); k++)
    {
        if (words[k].size() == 1)
                continue;
        string probe(words[k]);
        random_shuffle(probe.begin(), probe.end());
        probes.push_back(probe);
        if (k % 10 == 0  &&  probe[0] != 'z')
        {
            probe[0]++;
            probes.push_back(probe);
        }
    }
}

//========================================================================
// Do lookup
//========================================================================

// The correctness tests uses a global vector to record items passed
// to the callback function by the Dictionary being tested

static vector<string> actual;

static void recordAnagram(string s)
{
    actual.push_back(s);
}

  // Expected array must be sorted
static string doLookup(const Dictionary& d, string probe,
                                        const vector<string>& expected)
{
    actual.clear();
    d.lookup(probe, recordAnagram);
    sort(actual.begin(), actual.end());
    auto end = expected.begin() + min(expected.size(), actual.size());
    auto pr = mismatch(expected.begin(), end, actual.begin());
    string msg;
    if (pr.first == expected.end()  &&  pr.second == actual.end())
        return msg;
    msg.reserve(80);
    msg.append("Probe \"").append(probe);
    if (pr.first != expected.end()  &&
		(pr.second == actual.end()  ||  *pr.first < *pr.second))
            msg.append("\" failed to find \"").append(*pr.first);
    else if (pr.second != actual.begin()  &&  *pr.second == *(pr.second-1))
            msg.append("\" mistakenly found too many \"").append(*pr.second);
    else
            msg.append("\" mistakenly found \"").append(*pr.second);
    return msg.append("\"");
}

//========================================================================
// Measure time
//========================================================================

// The callback function for time measurement does nothing

static void doNothing(string)
{
}

double measureTime(size_t limit, const vector<string>& words,
                                                const vector<string>& probes)
{
    Dictionary dict;
    for (const auto& w : words)
        if (w.size() <= limit)
            dict.insert(w);
    Timer timer;
    for (const auto& p : probes)
    {
        if (p.size() <= limit)
            dict.lookup(p, doNothing);
    }
    return timer.elapsed();
}
