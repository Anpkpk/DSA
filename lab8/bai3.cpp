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

    void bfsTraversal(int startNode) {
        vector<bool> visited(V + 1, false);
        queue<int> q;

        visited[startNode] = true;
        q.push(startNode);
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            cout << u << " ";

            for (int v : adjList[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << endl;
    }

    vector<int> findPathBFS(int u, int v) {
        vector<bool> visited(V + 1, false);
        vector<int> parent(V + 1, -1);
        queue<int> q;

        visited[u] = true;
        q.push(u);

        while (!q.empty()) {
            int s = q.front();
            q.pop();
            
            for (int t : adjList[s]) {
                if (!visited[t]) {
                    visited[t] = true;
                    parent[t] = s;
                    q.push(t);

                    if (t == v) break;
                }
            }
        }
        
        if (!visited[v]) return {};

        vector<int> path;
        for (int t = v; t != -1; t = parent[t])
            path.push_back(t);
    
        reverse(path.begin(), path.end());
        return path;
    }

    vector<int> distToAll(int startNode) {
        vector<int> dist(V + 1, -1);
        queue<int> q;

        dist[startNode] = 0;
        q.push(startNode);

        while (!q.empty()) {
            int u = q.front(); q.pop();

            for (int v : adjList[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[v] + 1;
                    q.push(v);
                }
            }
        }
        return dist;  
    }

    bool isConnected() {
        vector<int> dist = distToAll(1);

        for (int i = 1; i <= adjList.size(); i++) {
            if (dist[i] == -1)
                return false; 
        }
        return true;
    }

};

int main() {
    Graph g;
    g.loadGraph("graph.txt");

    g.bfsTraversal(1);
    vector<int> path_bfs = g.findPathBFS(1, 7);
    for (int x : path_bfs)
        cout << x << " ";
    cout << endl;
}
