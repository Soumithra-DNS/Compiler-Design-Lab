#include <bits/stdc++.h>
using namespace std;

int precedence(char ch);
string infixToPostfix(string infix);

string solve(string infix) {
    string temp = "", postfix = "";
    stack<string> stk;

    for(char ch : infix) {
        if(ch != ' ') {
            temp += ch;
        } 
        else {
            if(temp == "") continue;

            if(temp == "then") { temp = ""; continue; }

            if(temp == "if") {
                stk.push("if");
            }
            else if(temp == "else") {
                stk.push("else");
            }
            else {
                postfix += infixToPostfix(temp);

                while(!stk.empty() && stk.top() == "else") {
                    stk.pop(); // else
                    if(!stk.empty() && stk.top() == "if") stk.pop(); // if
                    postfix += "?";
                }
            }
            temp = "";
        }
    }
    return postfix;
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

int main() {
    ifstream fin("Q-17.input.txt");
    string infix;
    cout << "Enter conditional expression:\n";
    getline(fin, infix);
    cout << solve(infix);
    return 0;
}
