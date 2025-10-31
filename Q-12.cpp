/*
Write a program to build a lexical analyzer implementing the following regular
expressions. It takes a text as input from a file (e.g. input.txt) and display output in
console mode: E -> EAE|(E)|ID
              A -> + | - | * | /
              ID -> any valid identifier | any valid integer

2+3*5
2+3*+5
2*(3+5)
id+5
3+((4+4))
6.7+3
(9*66(
(5)
_id+5id*5
()a+b
)(a+b
5+6+
)4+5)
8+(5+)8
8(*)5

*/


#include <bits/stdc++.h>
using namespace std;
string input;

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool checkParentheses(const string& expr) {
    stack<char> stk;
    for (char c : expr) {
        if (c == '(') stk.push(c);
        else if (c == ')') {
            if (stk.empty()) return false;
            stk.pop();
        }
    }
    return stk.empty();
}


bool isInteger(const string& str){
  static const regex int_regex(R"(^\d+$)");
  return regex_match(str, int_regex);
}


bool isValidIdentifier(const string& str){
  static const regex id_regex(R"(^[_a-zA-Z]\w*$)");
  static const vector<string> keywords = {
    "int", "float", "double", "char", "if", "else", "for", "while", "return", "void", "break", "continue"
  };
  if(!regex_match(str, id_regex)) return false;
  for(auto key : keywords){
    if(str == key) return false;
  }
  return true;
}


bool isValidExpression(const string& str){
  if(!checkParentheses(str)) return false;
  vector<string>tokens;
  string token;
  for(auto c : str){
    if(isOperator(c) || c == '(' || c == ')'){
      if(!token.empty()){
        tokens.push_back(token);
        token.clear();
      }
      if (isOperator(c)) tokens.push_back(string(1, c));
    }else if(!isspace(c)){
      token += c;
    }
  }
  
  if(!token.empty()) tokens.push_back(token);
  
  int opCount = 0, idCount = 0;
  for(const auto& t : tokens){
    if(isOperator(t[0]) && t.size() == 1) opCount++;
    else if(isValidIdentifier(t) || isInteger(t)) idCount++;
    else return false;
  }
  
  return idCount > 0 && (idCount - 1 == opCount);
}



int main()
{
  ifstream fin("Q-12.input.txt");
  string str;
  while(getline(cin, str)){
  cout << (isValidExpression(str) ? "Valid" : "Invalid") << endl;
  }
}