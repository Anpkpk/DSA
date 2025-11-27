#include <bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    Node *root;

public:
    BinaryTree() : root(nullptr) {}
    
    ~BinaryTree() {
        deleteTree(root);
    }
    
    void setRoot(Node *node) { 
        root = node; 
    }
    
    Node *createNode(int val) {
        Node *new_node = new Node(val);
        return new_node;
    }                
    
    Node *insertRoot(int val) {
        root = createNode(val);
    }                

    Node *insertLeft(Node *parent, int val) {
        parent->left = createNode(val);
        return parent;
    }  

    Node *insertRight(Node *parent, int val) {
        parent->right = createNode(val);
        return parent;
    }

    Node *getLeftChild(Node *parent) {
        return parent->left;
    }
    
    Node *getRightChild(Node *parent) {
        return parent->right;
    }
    
    Node *getParent(Node *node, Node *target) {
        if (node == nullptr or target == nullptr) 
            return nullptr;
        
        if (node->left == target or node->right == target) 
            return node;

        Node *left = getParent(node->left, target);
        if (left != nullptr) 
            return left;
        
        return getParent(node->right, target);
    }

    int getSize(Node* node) {
        if (node == nullptr) return 0;

        int l = getSize(node->left);
        int r = getSize(node->right);
        return 1 + l + r;
    }

    int getHeight(Node* node) {
        if (node == nullptr) return 0;

        int l = getHeight(node->left);
        int r = getHeight(node->right);
        
        return 1 + max(l, r);
    }

    int getDepth(Node* root, Node* target, int depth=0) {
        if (!root or !target) return -1;

        if (root == target)
            return depth;

        int l = getDepth(root->left, target, depth + 1);
        if (l != -1)
            return l;

        return getDepth(root->right, target, depth + 1);
    }

    int countLeaves(Node* node) {
        if (node == nullptr) return 0;

        if (node->left == nullptr and node->right == nullptr)
            return 1;

        int l = countLeaves(node->left);
        int r = countLeaves(node->right);

        return l + r;
    }

    bool isBalanced(Node* node) {
        if (!node) return true;

        return abs(getHeight(node->left) - getHeight(node->right)) <= 1
            && isBalanced(node->left)
            && isBalanced(node->right);
    }

    bool isFull(Node* node) {
        if (!node) return true;

        if ((node->left == nullptr) != (node->right == nullptr))
            return false;

        return isFull(node->left) && isFull(node->right);
    }

    bool isComplete(Node *node) {
        if (!node) return true;

        
    }


    void deleteTree(Node *node) {
        if (!node)
            return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
};

int main() {

}