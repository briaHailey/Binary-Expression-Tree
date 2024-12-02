#include <sstream>
#include <stack>
#include "bet.h"

using namespace std;

bool isOp(string in);

// Default constructor. Simply set root to be nullptr.
BET::BET() {
    root = nullptr;
}

// One param constructor. Build tree.
BET::BET(const string &postfix) {
    if (buildFromPostfix(postfix)) {
        cout << "Successfully built the tree given " << postfix << endl;
    }
}

// Copy constructor
BET::BET(const BET & copy) {
    root = clone(copy.root);
}

// Destructor
BET::~BET() {
    makeEmpty(root);
}

bool BET::buildFromPostfix(const string &postfix) {
    // Create a string stream so getline can be used as wanted
    string currentChar;
    istringstream input(postfix);

    // Create stack for managing inputs
    stack<BinaryNode*> bigStack;

    // Loop through all characters in the string
    while (getline(input, currentChar, ' ')) {
        // Check if the current char is a operator
        if (isOp(currentChar)) {
            // currentChar is an operator
            // Pop two from stack
            // Ensure that this is possible
            if (bigStack.size() >= 2) {
                // Possible, continue
                // Pop top two
                BinaryNode* one = bigStack.top();
                bigStack.pop();
                BinaryNode* two = bigStack.top();
                bigStack.pop();
                // Push a new node to the stack
                bigStack.push(new BinaryNode(currentChar, two, one));
            } else {
                // Not possible, invalid input
                return false;
            }
        } else {
            // currentChar is operand
            // push to stack
            bigStack.push(new BinaryNode(currentChar, nullptr, nullptr));
        }
    }
    // If the tree was properly constructed, the stack should only have one element
    if (bigStack.size() > 1) {
        cout << "Cannot build the tree based on " << postfix << "\n";
        return false;
    } else {
        root = bigStack.top();
        return true;
    }
}

const BET &BET::operator=(const BET & right) {
    if (this != &right) {
        makeEmpty(root);
        root = clone(right.root);
    }
    return *this;
}

BET::BinaryNode *BET::clone(BET::BinaryNode *t) {
    if (t == nullptr)
        return nullptr;
    else
        return new BinaryNode(t->element, clone(t->left), clone(t->right));
}

void BET::printInfixExpression() const {
    cout << "\b";
    printInfixExpression(root);
    cout << endl;
}

void BET::printPostfixExpression() const {
    cout << "\b";
    printPostfixExpression(root);
    cout << endl;
}

size_t BET::size() const {
    return size(root);
}

size_t BET::leaf_nodes() const {
    return leaf_nodes(root);
}

bool BET::empty() const {
    if (root == nullptr) {
        return true;
    } else {
        return false;
    }
}

void BET::printInfixExpression(BET::BinaryNode *n) const {
    if (n != nullptr){
        bool needPar = false;
        if (n->left != nullptr && (n->element == "+" || n->element ==  "-")) {
            needPar = true;
        }
        if (n->left != nullptr && n->right != nullptr && (n->element == "*" || n->element ==  "/")) {
            if (n->left->element ==  "+" || n->left->element ==  "-" || n->right->element ==  "+" || n->right->element ==  "-"){
                needPar = true;
            }
        }
        if (needPar){
            cout << " (";
        }
        printInfixExpression(n->left);
        cout << ' ' << n->element;
        printInfixExpression(n->right);
        if (needPar) {
            cout << " )";
        }
    }
}

void BET::makeEmpty(BET::BinaryNode *&t) {
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

void BET::printPostfixExpression(BET::BinaryNode *n) const {
    if (n != nullptr) {
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        cout << " ";
        cout << n->element;
    }
}

size_t BET::size(BET::BinaryNode *t) const {
    if (t == nullptr) {
        return 0;
    }
    return 1+size(t->left)+ size(t->right);
}

size_t BET::leaf_nodes(BET::BinaryNode *t) const {
    if (t != nullptr && t->left == nullptr && t->right == nullptr) {
        return 1;
    } else if (t != nullptr) {
        return leaf_nodes(t->left) + leaf_nodes(t->right);
    }
    return 0;
}


bool isOp(string in) {
    if (in == "+" || in == "-" || in == "*" || in == "/") {
        return true;
    } else {
        return false;
    }
}