/*
Write a program to generate FIRST and FOLLOW sets using a given CFG.
E->TP
P->@
P->+TP
T->FQ
Q->@
Q->*FQ
F->i
F->(E)
*/

#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> first;
map<char, set<char>> follow;
vector<char> order;

bool isNonTerminal(char c)
{
    return (c >= 'A' && c <= 'Z');
}

void computeFirst()
{
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (auto lf : order)
        {
            for (auto rh : grammar[lf])
            {
                bool epsilonChain = true;
                for (int i = 0; i < rh.size(); i++)
                {
                    char symbol = rh[i];
                    if (!isNonTerminal(symbol))
                    {
                        if (first[lf].insert(symbol).second)
                            changed = true;
                        epsilonChain = false;
                        break;
                    }
                    else
                    {
                        for (auto f : first[symbol])
                        {
                            if (f != '@')
                            {
                                if (first[lf].insert(f).second)
                                    changed = true;
                            }
                        }
                        if (first[symbol].find('@') == first[symbol].end())
                        {
                            epsilonChain = false;
                            break;
                        }
                    }
                }
                if (epsilonChain)
                {
                    if (first[lf].insert('@').second)
                        changed = true;
                }
            }
        }
    }
}

void computeFollow()
{
    follow[order[0]].insert('$');

    bool changed = true;
    while (changed)
    {
        changed = false;
        for (auto lf : order)
        {
            for (auto rh : grammar[lf])
            {
                for (int i = 0; i < rh.size(); i++)
                {
                    char B = rh[i];
                    if (isNonTerminal(B))
                    {
                        bool eps = false;
                        int j = i + 1;
                        for (; j < rh.size(); j++)
                        {
                            char next = rh[j];
                            if (isNonTerminal(next))
                            {
                                for (auto f : first[next])
                                {
                                    if (f != '@')
                                    {
                                        if (follow[B].insert(f).second)
                                            changed = true;
                                    }
                                    else
                                        eps = true;
                                }
                                if (!eps)
                                    break;
                            }
                            else
                            { // terminal
                                if (follow[B].insert(next).second)
                                    changed = true;
                                eps = false;
                                break;
                            }
                        }
                        if (j == rh.size() || eps)
                        {
                            for (auto f : follow[lf])
                            {
                                if (follow[B].insert(f).second)
                                    changed = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    //freopen("13.input.txt", "r", stdin);
    string production;
    while (getline(cin, production))
    {
        if (production.size() < 4)
            continue;
        char left = production[0];
        string right = production.substr(3);
        grammar[left].push_back(right);
        if (find(order.begin(), order.end(), left) == order.end())
            order.push_back(left);
    }

    cout << "_____Grammar_____\n";
    for (auto c : order)
    {
        cout << c << " -> ";
        for (int i = 0; i < grammar[c].size(); i++)
        {
            cout << grammar[c][i];
            if (i != grammar[c].size() - 1)
                cout << " | ";
        }
        cout << "\n";
    }

    computeFirst();

    cout << "_____FIRST_____\n";
    for (auto c : order)
    {
        cout << c << " = { ";
        for (auto x : first[c])
            cout << x << " ";
        cout << "}\n";
    }

    computeFollow();

    cout << "_____FOLLOW_____\n";
    for (auto c : order)
    {
        cout << c << " = { ";
        for (auto x : follow[c])
            cout << x << " ";
        cout << "}\n";
    }
}
