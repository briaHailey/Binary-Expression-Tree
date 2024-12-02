#ifndef BET_H
#define BET_H

#include <iostream>
#include <string>

using namespace std;
//using namespace cop4530;

class BET {
public:
    // Default constructor. Builds an empty tree and sets up the root.
    BET();

    // One parameter constructor. Postfix is a string containing a postfix expression.
    // This function calls buildFromPostfix
    BET(const string& postfix);

    // Copy constructor. Makes a deep copy of the tree.
    // This function calls clone function.
    BET(const BET&);

    // Destructor. Cleans up dynamic space in the tree.
    // Calls the makeEmpty function.
    ~BET();

    // Builds a tree based on a postfix expression
    bool buildFromPostfix(const string& postfix);

    //Assignment operator. Makes a deep copy.
    const BET & operator=(const BET &);

    //Prints out the infix expression.
    void printInfixExpression() const;

    //Prints out the postfix expression.
    void printPostfixExpression() const;

    // Returns the number of nodes in the tree.
    size_t size() const;

    // Return the number of leaf nodes in the tree.
    size_t leaf_nodes() const;

    // Return true if the tree is empty, return false otherwise.
    bool empty() const;

private:
    struct BinaryNode {
        BinaryNode *left;
        BinaryNode *right;
        string element;

        // BinaryNode constructors
        BinaryNode(const string &theElement, BinaryNode *lt, BinaryNode *rt) : element{theElement}, left{lt}, right{rt} {}
        BinaryNode(string &&theElement, BinaryNode *lt, BinaryNode *rt) : element{std::move(theElement)}, left{lt}, right{rt} {}
    };

    // Print the infix expression of the subtree that n is pointing to.
    void printInfixExpression(BinaryNode *n) const;

    // Delete all the nodes in the subtree that t is pointing to.
    void makeEmpty(BinaryNode* &t);

    // Clone all nodes in the subtree that t is pointing to
    BinaryNode * clone(BinaryNode *t);

    // Print the postfix expression of the subtree that n is pointing to.
    void printPostfixExpression(BinaryNode *n) const;

    // Return the number of nodes in the subtree that t is pointing to.
    size_t size(BinaryNode *t) const;

    // Return the number of leaf nodes in the subtree that t is pointing to.
    size_t leaf_nodes(BinaryNode *t) const;

    // PRIVATE DATA
    BinaryNode* root;
};

#endif // BET_H