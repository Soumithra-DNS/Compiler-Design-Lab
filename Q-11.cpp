/*
Write a program to generate a syntax tree for the sentence a+b*c with the following 
grammar: E —> E+E|E-E|E*E|E/E|(E)|a|b|c 

a+b*(c*d)
*/
#include <bits/stdc++.h>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

bool isOperand(char c);
bool isOperator(char c);
int precedence(char c);
string infixToPostfix(const string& infix);
Node* parse(const string& str);
void deleteTree(Node* root);
void print(Node* root, int space = 0, int indent = 4) { // Inorder traversal of tree (rotated)
    if (root == nullptr) return;
    space += indent;
    print(root->right, space);
    cout<<endl;
    for (int i = indent; i < space; i++) {
        cout << " ";
    }
    cout << root->data;
    print(root->left, space);
}

int main() {
    string str;
    if (!getline(cin, str)) return 0; // read whole line (handles spaces)
    // trim leading/trailing spaces (optional)
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return 0;
    size_t last = str.find_last_not_of(" \t\r\n");
    str = str.substr(first, last - first + 1);

    string postfix = infixToPostfix(str);
    if (postfix.empty()) {
        cerr << "Error: Invalid expression (e.g., mismatched parentheses).\n";
        return 1;
    }

    Node* tree = parse(postfix);
    if (!tree) {
        cerr << "Error: failed to build syntax tree (malformed expression).\n";
        return 1;
    }

    print(tree);
    cout<<endl;

    deleteTree(tree); // Free the allocated memory
    return 0;
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

bool isOperand(char c) {
    return isalnum(static_cast<unsigned char>(c));
}

int precedence(char c) {
    switch (c)
    {
    case '^':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

string infixToPostfix(const string& infix) {
    string postfix;
    stack<char> stk;
    for (char ch : infix) {
        if (isspace(static_cast<unsigned char>(ch))) continue;
        if (isOperand(ch)) {
            postfix += ch;
        }
        else if (ch == '(') {
            stk.push(ch);
        }
        else if (ch == ')') {
            while (!stk.empty() && stk.top() != '(') {
                postfix += stk.top();
                stk.pop();
            }
            if (stk.empty()) {
                return ""; // Mismatched parentheses error
            }
            stk.pop(); // Pop the '('
        }
        else if (isOperator(ch)) {
            // Pop while top of stack is an operator with higher precedence,
            // or equal precedence and the current operator is left-associative.
            while (!stk.empty() && isOperator(stk.top())) {
                int pTop = precedence(stk.top());
                int pCur = precedence(ch);
                bool topHigher = pTop > pCur;
                bool topEqualAndLeftAssoc = (pTop == pCur && ch != '^'); // '^' is right-assoc
                if (topHigher || topEqualAndLeftAssoc) {
                    postfix += stk.top();
                    stk.pop();
                } else break;
            }
            stk.push(ch);
        }
    }
    while (!stk.empty()) {
        if (stk.top() == '(') {
            return ""; // Mismatched parentheses error
        }
        postfix += stk.top();
        stk.pop();
    }
    return postfix;
}

Node* parse(const string& str) {
    stack<Node*> st;
    for (char ch : str) {
        if (isOperand(ch)) {
            st.push(new Node(ch));
        }
        else if (isOperator(ch)) {
            if (st.size() < 2) {
                while(!st.empty()) { delete st.top(); st.pop(); }
                return nullptr; // Malformed expression
            }
            Node* right = st.top(); st.pop();
            Node* left = st.top(); st.pop();
            
            Node* node = new Node(ch);
            node->left = left;
            node->right = right;
            st.push(node);
        }
    }
    if (st.size() != 1) {
        while(!st.empty()) { delete st.top(); st.pop(); }
        return nullptr; // Malformed expression
    }
    return st.top();
}

void deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}