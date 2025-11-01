/*
Write a program to generate a parse tree of predictive parser using the following parsing
table:
      id          +          *          (          )          $
E   E->TE'                            E->TE'
E'             E'->+TE'                          E'->@      E'->@
T   T->FT'                            T->FT'
T'              T'->@      T'->*FT'              T'->@      T'->@
F   F->id                             F->(E)

i+i+i*(i+i)
*/


#include <bits/stdc++.h>
using namespace std;

map<pair<char, char>, string> table;

void createTable()
{
    table[{'E', 'i'}] = "TP";
    table[{'E', '('}] = "TP";

    table[{'P', '+'}] = "+TP";
    table[{'P', ')'}] = "@";
    table[{'P', '$'}] = "@";

    table[{'T', 'i'}] = "FQ";
    table[{'T', '('}] = "FQ";

    table[{'Q', '*'}] = "*FQ";
    table[{'Q', '+'}] = "@";
    table[{'Q', ')'}] = "@";
    table[{'Q', '$'}] = "@";

    table[{'F', 'i'}] = "i";
    table[{'F', '('}] = "(E)";
}

bool solve(string str)
{
    stack<pair<int, char>> stk;
    stk.push({0, 'E'}); // (indentation level, symbol)

    for (int i = 0; i < str.size();)
    {
        if (stk.empty())
            break;

        int space = stk.top().first;
        char top = stk.top().second;
        stk.pop();

        if (top == '@')
            continue; // epsilon
        if (top == str[i])
        {
            i++;
            continue;
        }

        string prod = table[{top, str[i]}];
        if (prod.empty())
        {
            cout << "No rule for (" << top << ", " << str[i] << ")\n";
            return false;
        }

        // print the rule (parse tree step)
        for (int j = 0; j < space; j++)
            cout << " ";
        cout << top << " -----> " << prod << "\n";

        // push production RHS in reverse
        for (int j = prod.size() - 1; j >= 0; j--)
        {
            if (prod[j] != '@')
                stk.push({space + 5, prod[j]});
        }
    }

    return true;
}

int main()
{
    createTable();

    string str = "i+i*i$";
    cout << "Input: " << str << "\n\n";

    if (solve(str))
        cout << "\n✅ Accepted\n";
    else
        cout << "\n❌ Rejected\n";

    return 0;
}