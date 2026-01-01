#include <bits/stdc++.h>

using namespace std;

class ArrayBinaryTree
{
private:
    int *arr;
    int capacity;
    int size;

public:
    ArrayBinaryTree(int cap) : capacity(cap), size(0)
    {
        arr = new int[capacity];
        for (int i = 0; i < capacity; i++)
            arr[i] = -1;
    }

    ~ArrayBinaryTree()
    {
        delete[] arr;
    }

    void insertRoot(int value)
    {
        arr[0] = value;
        size++;
    }

    void insertLeft(int parentIndex, int val)
    {
        arr[2 * parentIndex + 1] = val;
        size++;
    }

    void insertRight(int parentIndex, int val)
    {
        arr[2 * parentIndex + 2] = val;
        size++;
    }

    int getParent(int index)
    {
        return arr[(index - 1) / 2];
    }

    int getLeftChild(int index)
    {
        return arr[2 * index + 1];
    }

    int getRightChild(int index)
    {
        return arr[2 * index + 2];
    }

    int getSize()
    {
        return size;
    }

    void printArr()
    {
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }
    }

    void printTree() {
        int h = floor(log2(capacity)); 
        
        for (int i = 0; i <= h; i++) {
            int startNode = pow(2, i) - 1;      
            int nodesInLevel = pow(2, i);        
            int space = pow(2, h - i + 1);      
            
            for(int k=0; k < space/2; k++) cout << "   "; 

            for (int j = 0; j < nodesInLevel; j++) {
                int idx = startNode + j;
                if (idx < capacity && arr[idx] != -1) 
                    cout << setw(3) << arr[idx]; 
                else 
                    cout << "   ";               

                for(int k=0; k < space - 1; k++) cout << "   "; 
            }
            cout << endl << endl;
        }
    }

    void preorder(int index) {
        if (index >= capacity or arr[index] == -1) {
            return;
        }

        cout << arr[index] << " ";

        preorder(2 * index + 1);
        preorder(2 * index + 2);
    }

    void inorder(int index) {
        if (index >= capacity or arr[index] == -1)
            return;

        inorder(2 * index + 1);
        cout << arr[index] << " ";
        inorder(2 * index + 2);
    }

    void level_order() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
    }
};

int main() {

    ArrayBinaryTree tree(31); 

    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    tree.insertRoot(1);      
    tree.insertLeft(0, 2);   
    tree.insertRight(0, 3);  
    tree.insertLeft(1, 4);   
    tree.insertRight(1, 5);  
    
    // tree.preorder(0);

    tree.inorder(0);

    return 0;

}