/*
Write a program that will check an English sentence given in present indefinite form 
to justify whether it is syntactically valid or invalid according to the following Chomsky 
Normal Form: 
S -> SUB PRED 
SUB -> PN | P 
PRED -> V | V N 
PN -> Sagor | Selim | Salma | Nipu 
P -> he | she | i | we | you | they 
N -> book | cow | dog | home | grass | rice | mango 
V -> read | eat | take | run | write

Nipu read book
Nipu read book.
nipu read book
nipu read mango book
Salma take mango
I eat grass
cow eat grass
Selim run
we read book
read book
Sagor mango eat
*/


#include <bits/stdc++.h>
using namespace std;
vector<string> sub = {"Sagor", "Selim", "Salma", "Nipu", "he", "she", "I", "we", "you", "they"};
vector<string> verb = {"read", "eat", "take", "run", "write"};
vector<string> noun = {"book", "cow", "dog", "home", "grass", "rice", "mango"};

int main()
{
    ifstream fin("Q-09.input.txt");
    
    string input;
    while (getline(fin, input))
    {
        string word;
        vector<string> words;
        for (char c : input)
        {
            if (c != ' ')
            {
                word += c;
            }
            else
            {
                words.push_back(word);
                word = "";
            }
        }

        words.push_back(word);

        bool isValid = true;

        if (words.size() > 3 || words.size() < 2)
        {
            isValid = false;
        }
        else
        {
            if (find(sub.begin(), sub.end(), words[0]) == sub.end())
                isValid = false;
            if (find(verb.begin(), verb.end(), words[1]) == verb.end())
                isValid = false;
            if (words.size() == 3)
            {
                if (find(noun.begin(), noun.end(), words[2]) == noun.end())
                    isValid = false;
            }
        }

        if (isValid)
            cout << input << " : Valid\n";
        else
            cout << input << " : Invalid\n";
    }
    return 0;
}



/*
g++ -o Q-09 Q-09.cpp
.\Q-09.exe
*/