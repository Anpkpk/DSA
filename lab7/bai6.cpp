#include <bits/stdc++.h>

using namespace std;

struct Node {
    int value;
    int arrayIdx;
    int pos;
};

struct cmp {
    bool operator()(const Node &a, const Node &b) {
        return a.value > b.value;   // min-heap
    }
};

vector<int> mergeSortedArrays(vector<vector<int>> &arr) {
    priority_queue<Node, vector<Node>, cmp> pq;
    vector<int> result;

    int k = arr.size();

    for (int i = 0; i < k; i++) {
        if (!arr[i].empty()) {
            pq.push({arr[i][0], i, 0});
        }
    }

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        result.push_back(cur.value);

        int i = cur.arrayIdx;
        int j = cur.pos + 1;

        if (j < arr[i].size()) {
            pq.push({arr[i][j], i, j});
        }
    }
    return result;
}

int main() {
    vector<vector<int>> arr = {{1, 4, 7},
                               {2, 5, 8},
                               {3, 6, 9}};

    vector<int> res = mergeSortedArrays(arr);

    for (int x : res) 
        cout << x << " ";
    cout << endl;
}
