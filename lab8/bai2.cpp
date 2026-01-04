#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    Edge(int u, int v) : u(u), v(v) {}
};

class Graph {
private:
    int V, E;

public:
    vector<Edge> edgeList;
    vector<vector<int>> adjList;
    vector<vector<int>> adjMatrix;

    Graph() {}

    void loadGraph(string filename) {
        ifstream fin(filename);
        if (!fin.is_open()) {
            cout << "Khong mo duoc file\n";
            return;
        }

        fin >> V >> E;

        adjList.resize(V + 1);
        adjMatrix.assign(V + 1, vector<int>(V + 1, 0));

        for (int i = 0; i < E; i++) {
            int u, v;
            fin >> u >> v;

            edgeList.push_back(Edge(u, v));

            adjList[u].push_back(v);
            adjList[v].push_back(u);

            adjMatrix[u][v] = 1;
            adjMatrix[v][u] = 1;
        }

        fin.close();
    }

    void insertEdge(int u, int v) {
        edgeList.push_back(Edge(u, v));

        adjList[u].push_back(v);
        adjList[v].push_back(u);

        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    void eraseEdge(int u, int v) {
        for (vector<Edge>::iterator it = edgeList.begin(); it != edgeList.end(); it++) {
            if ((it->u == u and it->v == v) or (it->u == v) and it->v == u) {
                edgeList.erase(it);
                break;
            }
        }

        for (vector<int>::iterator it = adjList[u].begin(); it != adjList[u].end();) {
            if (*it == v)
                it = adjList[u].erase(it);
            else   
                it++;
        }

        for (vector<int>::iterator it = adjList[v].begin(); it != adjList[v].end();) {
            if (*it == u)
                it = adjList[v].erase(it);
            else   
                it++;
        }

        adjMatrix[u][v] = 0;
        adjMatrix[v][u] = 0;
    }

    bool hasEdge(int u, int v) {
        return (adjMatrix[u][v] == 1);
    }

    vector<int> neighbors(int u) {
        return adjList[u];
    }

    int degree(int u) {
        return adjList[u].size();
    }

    int covertRep() {}

    void dfsTraversal(int startNode) {
        vector<bool> visited(V + 1, false);
        stack<int> st;
        
        st.push(startNode);
        while (!st.empty()) {
            int u = st.top();
            st.pop();

            if (visited[u]) continue;

            visited[u] = true;
            cout << u << " ";

            for (auto it = adjList[u].rbegin(); it != adjList[u].rend(); it++) {
                int v = *it;
                if (!visited[v]) {
                    st.push(v);
                }
            }
        }
    }

    void dfsRec(int u, vector<bool> &visited) {
        visited[u] = true;
        cout << u << " ";
        for (int v : adjList[u]) {
            if (!visited[v])
                dfsRec(v, visited);
        }
    }

    void dfsTraversalRec(int startNode) {
        vector<bool> visited(V + 1, false);
        dfsRec(startNode, visited);
    }

    bool dfsfind(int u, int v, vector<bool> &visited, vector<int> &parent) {
        visited[u] = true;
        if (u == v) return true;

        for (int x : adjList[u]) {
            if (!visited[x]) {
                parent[x] = u;    
                if (dfsfind(x, v, visited, parent))
                    return true;
            }
        }
        return false;
    }

    void findPathDFS(int u, int v) {
        vector<bool> visited(V + 1, false);
        vector<int> parent(V + 1, -1);
        
        if (!dfsfind(u, v, visited, parent)) return;

        vector<int> path;
        for (int cur = v; cur != -1; cur = parent[cur]) 
            path.push_back(cur);

        reverse(path.begin(), path.end());

        for (int x : path) 
            cout << x << " ";
        cout << endl;
    }
};

int main() {
    Graph g;
    g.loadGraph("graph.txt");

    g.dfsTraversal(1);
    cout << endl;
    g.dfsTraversalRec(1);
    cout << endl;

    g.findPathDFS(1, 6);
}
