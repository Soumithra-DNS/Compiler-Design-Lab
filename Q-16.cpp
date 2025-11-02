/*
Write a program that converts the C++ expression to an intermediate code of 
Post-fix notation form.

(a-b)*(d/e)
*/
#include <bits/stdc++.h>
using namespace std;

int precedence(char ch);
string infixToPostfix(string infix);

int main() {
    ifstream fin("Q-16.input.txt");
    string infix;
    getline(fin, infix);
    cout << infixToPostfix(infix);
    return 0;
}

string infixToPostfix(string infix) {
    string postfix = "";
    stack<char> stk;

    for(char ch : infix) {
        if( (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ) {
            postfix += ch;
        }
        else if(ch == '(') stk.push(ch);
        else if(ch == ')') {
            while(!stk.empty() && stk.top() != '(') {
                postfix += stk.top();
                stk.pop();
            }
            stk.pop();
        }
        else if(ch != ' ') {
            while(!stk.empty() && precedence(ch) <= precedence(stk.top())) {
                postfix += stk.top();
                stk.pop();
            }
            stk.push(ch);
        }
    }
    while(!stk.empty()) {
        postfix += stk.top();
        stk.pop();
    }
    return postfix;
}

int precedence(char ch) {
    if(ch == '^') return 3;
    if(ch == '*' || ch == '/') return 2;
    if(ch == '+' || ch == '-') return 1;
    return 0;
}