/*
Write a program to generate a FOLLOW set and parsing table using the following LL(1) 
grammar and FIRST set: 
Grammar      FIRST set 
E -> TE'     {id, (} 
E'-> +TE'|@  {+, @} 
T -> FT'     {id, (} 
T'-> *FT'|@  {*, @}
F -> (E)|id  {id, (} 
*/


#include <bits/stdc++.h>
using namespace std;

vector<char> order;
map<pair<char, char>, string> table;
map<char, set<char>> first;
map<char, set<char>> follow;
map<char, vector<string>> grammar;

// FOLLOW calculation
void computeFollow() {
    follow[order[0]].insert('$'); // Start symbol gets '$'

    bool changed = true;
    while (changed) {
        changed = false;
        for (auto lf : order) {
            for (auto rh : grammar[lf]) {
                for (int i = 0; i < rh.size(); i++) {
                    char B = rh[i];
                    if (B >= 'A' && B <= 'Z') {
                        bool eps = false;
                        int j = i + 1;
                        for (; j < rh.size(); j++) {
                            char next = rh[j];
                            if (next >= 'A' && next <= 'Z') {
                                for (auto f : first[next]) {
                                    if (f != '@') {
                                        if (follow[B].insert(f).second)
                                            changed = true;
                                    } else eps = true;
                                }
                                if (!eps) break;
                            } else { // terminal
                                if (follow[B].insert(next).second)
                                    changed = true;
                                eps = false;
                                break;
                            }
                        }
                        if (j == rh.size() || eps) { // if last or epsilon chain
                            for (auto f : follow[lf]) {
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

// PARSE TABLE generation
void computeTable() {
    for (char row : order) {
        for (char col : first[row]) {
            if (col != '@') {
                bool isSet = false;
                for (auto str : grammar[row]) {
                    if (str[0] == col) {
                        table[{row, col}] = string(1, row) + "->" + str;
                        isSet = true;
                    }
                }
                if (!isSet)
                    table[{row, col}] = string(1, row) + "->" + grammar[row][0];
            }
        }
        if (first[row].find('@') != first[row].end()) {
            for (char col : follow[row]) {
                table[{row, col}] = string(1, row) + "->@";
            }
        }
    }
}

int main() {
    // Grammar & FIRST initialization
    order = {'E', 'P', 'T', 'Q', 'F'};
    grammar['E'] = {"TP"};
    grammar['P'] = {"+TP", "@"};
    grammar['T'] = {"FQ"};
    grammar['Q'] = {"*FQ", "@"};
    grammar['F'] = {"(E)", "i"};

    first['E'] = {'(', 'i'};
    first['P'] = {'+', '@'};
    first['T'] = {'(', 'i'};
    first['Q'] = {'*', '@'};
    first['F'] = {'(', 'i'};

    // Display Grammar
    cout << "_____Grammar_____\n";
    for (auto c : order) {
        cout << c << " -> ";
        for (auto x : grammar[c]) cout << x << " | ";
        cout << "\n";
    }

    // Display FIRST sets
    cout << "\n_____FIRST_____\n";
    for (char c : order) {
        cout << c << " = { ";
        for (auto x : first[c]) cout << x << " ";
        cout << "}\n";
    }

    // Compute FOLLOW sets
    computeFollow();

    // Display FOLLOW sets
    cout << "\n_____FOLLOW_____\n";
    for (char c : order) {
        cout << c << " = { ";
        for (auto x : follow[c]) cout << x << " ";
        cout << "}\n";
    }

    // Compute Parse Table
    computeTable();

    // Print Parse Table
    cout << "\n_____Parse Table_____\n";
    vector<char> column = {'i', '+', '*', '(', ')', '$'};

    cout << setw(5) << " ";
    for (auto col : column) cout << setw(10) << col;
    cout << "\n";

    for (auto row : order) {
        cout << setw(5) << row;
        for (auto col : column) {
            if (!table[{row, col}].empty()) {
                cout << setw(10) << table[{row, col}];
            } else {
                cout << setw(10) << "-";
            }
        }
        cout << "\n";
    }

    return 0;
}



