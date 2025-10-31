/*
Write a program to implement a shift reducing parsing.

4
E->E+E
E->E*E
E->(E)
E->a
a+a*(a+a)+a
*/

#include <bits/stdc++.h>
using namespace std;

map<string, string> rules;
string stk = "", input;

void reduce()
{
    for (auto rule : rules)
    {
        if (stk.find(rule.first) != std::string::npos)
        {
            int pos = stk.find(rule.first);
            stk.erase(pos, rule.first.length());
            stk.insert(pos, rule.second);
            cout << left << setw(13) << "$" + stk << right << setw(13) << input + "$" << right << setw(12) << "Reduce " << rule.second << "-->" << rule.first << "\n";
            reduce();
        }
    }
    return;
}

int main()
{
    //ifstream fin("10.input.txt");
    string production;
    char startSymbol;
    int n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++)
    {
        getline(cin, production);
        rules[production.substr(3)] = production[0];
        if (i == 0)
            startSymbol = production[0];
    }

    getline(cin, input);
    cout << "Stack             " << "Input             " << "Action             " << "\n";
    cout << left << setw(13) << "$" << right << setw(13) << input + "$" << "\n";

    while (!input.empty())
    {
        char top = input[0];
        stk += top;
        input.erase(0, 1);
        cout << left << setw(13) << "$" + stk << right << setw(13) << input + "$" << right << setw(13) << "Shift-->" << top << "\n";
        reduce();
    }

    if (stk == string(1, startSymbol))
        cout << "Accepted";
    else
        cout << "Rejected";

    return 0;
}