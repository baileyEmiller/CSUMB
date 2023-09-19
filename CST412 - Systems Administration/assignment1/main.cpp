// Bailey Miller
// 9 September 2023
// C++ program compiled with g++ meant to break ceaser cipher through brute force
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <bits/stdc++.h>
using namespace std;

static const string FILENAME = "sample-secret-message-caesar-ciphertext.txt";
static const string DICTIONARY = "en-US.dic";
static const string OUTPUT_FILE = "output.txt";
#define MAX_INPUT_SZ 64 // maximum number of messages that can be deciphered in a single file

///////////////////////////////////////////////////////////////////////////////////////////////
// begin geeks for geeks code https://www.geeksforgeeks.org/trie-insert-and-search/
const int ALPHABET_SIZE = 26;

// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];

    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}

// Returns true if key presents in trie, else
// false
bool search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl->isEndOfWord);
}
// end geeks for geeks code https://www.geeksforgeeks.org/trie-insert-and-search/
///////////////////////////////////////////////////////////////////////////////////

int main()
{
    // opening dictionary
    ifstream dictionary;
    try
    {
        dictionary.open(DICTIONARY);
    }
    catch (exception e)
    {
        cerr << "Couldn't open file " << DICTIONARY << endl;
        return 1;
    }

    // cout << "Loading dictionary (this may take a minute)...\n";

    TrieNode *root = getNode(); // using trie data structure, built for tasks like this
    string orig, built, apo = "'";
    while (dictionary.is_open() && dictionary.good())
    {
        getline(dictionary, orig);
        for (int i = 0; i < orig.length(); i++)
        {
            if (orig[i] >= 'A' && orig[i] <= 'Z')
            {
                orig[i] += 32; // shifts a capital letter to it's corresponding lower letter in ASCII
            }
            if (orig[i] >= 'a' && orig[i] <= 'z' && orig[i] != apo[0]) // ensures only lowercase letters are recorded
            {
                built += orig[i];
            }
        }
        insert(root, built);

        orig.clear();
        built.clear();
    }
    dictionary.close();
    apo.clear();

    cout << "Enter file name (! for sample file): ";
    string user_filename;
    cin >> user_filename;
    int numberofmessages = 4;
    // open file
    ifstream ciphertext;
    try
    {
        if (user_filename[0] == '!')
        {
            ciphertext.open(FILENAME);
            cout << "Reading in ciphertext from file " << FILENAME << endl;
        }
        else
        {
            ciphertext.open(user_filename);
            cout << "Reading in ciphertext from file " << user_filename << endl;
        }
    }
    catch (exception e)
    {
        cerr << "Couldn't open file " << user_filename << endl;
        return 1;
    }

    // create vector
    vector<vector<string>> cipheredMessages;

    string line;

    int outerLoopCount = 0;
    while (getline(ciphertext, line))
    {
        vector<string> x;
        cipheredMessages.push_back(x);
        int innerLoopCount = 0;
        string word;
        while (line[innerLoopCount] != '\0')
        {
            if (line[innerLoopCount] != ' ')
            {
                word += line[innerLoopCount];
            }
            else
            {
                cipheredMessages.at(outerLoopCount).push_back(word);
                word.clear();
            }
            innerLoopCount++;
        }
        cipheredMessages.at(outerLoopCount).push_back(word);
        line.clear();
        word.clear();
        outerLoopCount++;
    }
    numberofmessages = outerLoopCount;
    ciphertext.close();

    // print ciphertext
    // for (int i = 0; i < numberofmessages; i++)
    // {
    //     for (int k = 0; k < cipheredMessages.at(i).size(); k++)
    //     {
    //         cout << cipheredMessages.at(i).at(k) << " ";
    //     }
    //     cout << endl;
    // }

    int key[MAX_INPUT_SZ];
    bool encrypted = true;
    for (int i = 0; i < numberofmessages; i++)
    {
        key[i] = -1;
    }
    for (int i = 0; i < numberofmessages; i++)
    { // for each message
        string shiftingWord;
        for (int k = 0; k < cipheredMessages.at(i).size(); k++)
        { // for each word in message
            map<int, int> m;
            for (int p = 0; p < ALPHABET_SIZE; p++)
            { // for each possible shift
                shiftingWord = cipheredMessages.at(i).at(k);
                for (int h = 0; h < shiftingWord.length(); h++)
                { // for each letter in word
                    int temp = shiftingWord[h] - 'a';
                    temp += p;
                    temp = temp % ALPHABET_SIZE; // use modulus operator to wrap around to beginning of alphabet
                    temp += 'a';
                    shiftingWord[h] = temp;
                }
                if (search(root, shiftingWord))
                {
                    if (m.find(p) == m.end())
                    {
                        m.emplace(p, 1);
                    }
                    else
                    {
                        m.at(p) += 1;
                    }
                    if (shiftingWord.length() > 5)
                    { // we give additional weight to words over 5 characters in length as there are going to be less possible alternatives
                        m.at(p) += 1;
                    }
                }
            }
            int largestFreq = 0;
            for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
            { // each word is deciphered individually and we use frequency analysis to determine which key is the correct one
                if (largestFreq < it->second)
                {
                    largestFreq = it->second;
                    key[i] = it->first;
                }
            }
        }
    }

    //opening output file
    ofstream output;
    try
    {
        output.open(OUTPUT_FILE, ios::out | ios::trunc); // truncate flag used to clear previous input
        // https://stackoverflow.com/questions/17032970/clear-data-inside-text-file-in-c
        cout << "writing the following to " << OUTPUT_FILE << endl;
    }
    catch (exception e)
    {
        cerr << "Couldn't open file " << OUTPUT_FILE << endl;
        return 1;
    }

    //printing out/writing to output file
    for (int i = 0; i < numberofmessages; i++)
    {
        cout << key[i] << ";";
        output << key[i] << ";";
        for (int k = 0; k < cipheredMessages.at(i).size(); k++)
        {
            for (int u = 0; u < cipheredMessages.at(i).at(k).length(); u++)
            {
                int temp = cipheredMessages.at(i).at(k)[u] - 'a';
                temp += key[i];
                temp = temp % ALPHABET_SIZE; // use modulus operator to wrap around to beginning of alphabet
                temp += 'a';
                cipheredMessages.at(i).at(k)[u] = temp;
            }
            cout << cipheredMessages.at(i).at(k) << " ";
            output << cipheredMessages.at(i).at(k) << " ";
        }
        cout << endl;
        output << endl;
    }
    output.close();

    return 0;
}
