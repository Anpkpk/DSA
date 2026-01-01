#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BST
{
private:
    Node *root;

public:
    BST() : root(nullptr) {}

    ~BST() {
        destroyTree(root);
    }

    void destroyTree(Node *node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    Node *createNode(int value) {
        return new Node(value);
    }

    Node *insert(Node *node, int val) {
        if (!node) {
            node = createNode(val);
        } else if (val < node->data) 
            node->left = insert(node->left, val);
        else 
            node->right = insert(node->right, val);

        return node;
    }

    bool search(Node *node, int value) {
        if (!node) {
            return false;
        } else if (value == node->data)
            return true;
        else if (value > node->data)
            return search(node->right, value);
        else 
            return search(node->left, value);
    }

    Node *findMin(Node *node) {
        if (!node->left) return node;
        return findMin(node->left);
    }

    Node *findMax(Node *node) {
        if (!node->right) return node;
        return findMax(node->right);
    }

    void printPreorder(Node *node) {
        // Visit root
        // traverse left subtree
        // traverse right subtree
        if (!node) return;
        cout << node->data << " ";
        printPreorder(node->left);
        printPreorder(node->right);
    }

    void printPostorder(Node *node) {
        // traverse left subtree
        // traverse right subtree
        // Visit root
        if (!node) return;
        printPostorder(node->left);
        printPostorder(node->right);
        cout << node->data << " ";
    }

    void printInorder(Node * node) {
        // traverse left subtree
        // Visit root
        // traverse right subtree
        if (!node) return;
        printInorder(node->left);
        cout << node->data << " ";
        printInorder(node->right);
    }

    void printLevelorder(Node *node) {
        if (!node) return;

        queue<Node*> q;
        q.push(node);

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                Node *curr = q.front();
                q.pop();
                cout << curr->data << " ";

                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            cout << endl;
        }
    }

    Node *predecessor(Node *x) {
        if (x->left) 
            return findMax(x->left);

        Node* pre = nullptr;
        Node* tmp = root;

        while (tmp) {
            if (x->data > tmp->data) {
                pre = tmp;         
                tmp = tmp->right;
            } else if (x->data < tmp->data)
                tmp = tmp->left;
            else 
                break;          
        }
        return pre;
    }

    Node *successor(Node *root, Node *x) {
        if (!x) return nullptr;

        if (x->right) {
            return findMin(x->right);
        }

        Node *suc = nullptr;
        Node *tmp = root;
        while (tmp) {
            if (x->data < tmp->data) {
                suc = tmp;
                tmp = tmp->left;
            }
            else if (x->data > tmp->data) {
                tmp = tmp->right;
            }
            else break;
        }
        return suc;
    }

    Node *deleteNode(Node *root, int val) {
        if (!root) return nullptr;

        if (val < root->data) 
            root->left = deleteNode(root->left, val);
    
        else if (val > root->data) 
            root->right = deleteNode(root->right, val);
        
        else {
            if (!root->left) {
                Node *tmp = root->right;
                delete root;
                return tmp;
            }
            else if (!root->right) {
                Node *tmp = root->left;
                delete root;
                return tmp;
            }

            Node *pred = root->left;
            while (pred->right)
                pred = pred->right;

            root->data = pred->data; 
            root->left = deleteNode(root->left, pred->data);
        }
        return root;
    }

    bool inorderCheck(Node *node, long long &prev) {
        if (!node) return true;

        if (!inorderCheck(node->left, prev)) return false;

        if (node->data < prev) return false;
        prev = node->data;

        return inorderCheck(node->right, prev);
    }


    bool isBST(Node *node) {
        long long prev = LLONG_MIN;
        return inorderCheck(root, prev);
    }

    void inorder(Node* root, int arr[], int &idx) {
        if (!root) return;

        inorder(root->left, arr, idx);
        arr[idx++] = root->data;
        inorder(root->right, arr, idx);
    }

    void bstSort(int arr[], int n) {
        Node* root = nullptr;

        for (int i = 0; i < n; i++)
            root = insert(root, arr[i]);

        int idx = 0;
        inorder(root, arr, idx);
    }

    void kSmallestUntil(Node *root, int k, int &cnt, Node * &ans) {
        if (!root || ans) return;

        kSmallestUntil(root->left, k, cnt, ans);

        cnt++;
        if (cnt == k) {
            ans = root;
            return;
        }

        kSmallestUntil(root->right, k, cnt, ans);
    }

    Node* findKthSmallest(Node* root, int k) {
        int cnt = 0;
        Node *ans = nullptr;
        kSmallestUntil(root, k, cnt, ans);
        return ans;
    }   

    Node *lowestCommonAncestor(Node *root, int n1, int n2) {
        if (!root) return nullptr;

        if (n1 < root->data and n2 < root->data)
            return lowestCommonAncestor(root->left, n1, n2);

        if (n1 > root->data and n2 > root->data)
            return lowestCommonAncestor(root->right, n1, n2);

        return root;
    }


};

int main() {
    vector<int> tree = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    BST bst;

    Node *root = nullptr;
    for (int x : tree) 
        root = bst.insert(root, x);

    //       8
    //     /   \
    //    3     10
    //   / \      \
    //  1   6      14
    //     / \     /
    //    4   7   13


    bst.printInorder(root);
    cout << endl;

    Node *max = bst.findMax(root);
    Node *min = bst.findMin(root);

    cout << "Max: " << max->data << endl;
    cout << "Min: " << min->data << endl;

    Node *predec = bst.predecessor(max);
    Node *success = bst.successor(root, predec);

    cout << "predecessor: " << predec->data << endl;
    cout << "successor: " << success->data << endl;

    int a[7] = {3, 6, 2, 1, 9, 7, 8};
    bst.bstSort(a, 7);
    for (int x : a) 
        cout << x << " ";
    cout << endl;

    Node *ans = bst.findKthSmallest(root, 3);
    cout << 3 << " smallest: " << ans->data << endl;

    cout << bst.lowestCommonAncestor(root, 4, 13)->data << endl;
}