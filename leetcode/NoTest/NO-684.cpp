class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        /*vector<vector<int>> graph;
        vector<bool> visited;
        visited.resize(edges.size());
        initGraph(graph, edges.size());
        for (int i = 0; i < edges.size(); i++) {
            initVisited(visited);
            if (findPath(graph, edges[i][0] - 1, edges[i][1] - 1, visited)) {
                return edges[i];
            }
            addToGraph(graph, edges[i]);
        }

        return vector<int>();*/
        vector<int> dsu;
        for (int i = 0; i < edges.size(); i++) {
            dsu.push_back(i);
        }

        for (int i = 0; i < edges.size(); i++) {
            if (connected(dsu, edges[i][0] - 1, edges[i][1] - 1)) {
                return edges[i];
            }
            dsuUnion(dsu, edges[i][0] - 1, edges[i][1] - 1);
        }
        return vector<int>();
    }

    bool connected(vector<int> &dsu, int p, int q) {
        return dsuFind(dsu, p) == dsuFind(dsu, q);
    }

    int dsuFind(vector<int> &dsu, int p) {
        while (p != dsu[p]) {
            //dsu[p] = dsu[dsu[p]];
            //p = dsu[p];
            int root = dsuFind(dsu, dsu[dsu[p]]);
            p = dsu[p];
            dsu[p] = root;
        }
        return p;
    }

    void dsuUnion(vector<int> &dsu, int p, int q) {
        int pRoot = dsuFind(dsu, p);
        int qRoot = dsuFind(dsu, q);
        if (pRoot == qRoot) {
            return;
        }
        dsu[pRoot] = qRoot;
        /*if (pRoot < qRoot) {
            dsu[pRoot] = qRoot;
        } else {
            dsu[qRoot] = pRoot;
        }*/
    }

    void initVisited(vector<bool> &visited) {
        for (int i = 0; i < visited.size(); i++) {
            visited[i] = false;
        }
    }

    bool findPath(vector<vector<int>> &graph, int u, int v, vector<bool> &visited) {
        visited[u] = true;
        if (graph[u][v]) {
            return true;
        }

        for (int i = 0; i < graph.size(); i++) {
            if (!visited[i] && graph[u][i]) {
                if (findPath(graph, i, v, visited)) {
                    return true;
                }
            }
        }
        return false;
    }

    void addToGraph(vector<vector<int>> &graph, vector<int> &line) {
        graph[line[0] - 1][line[1] - 1] = graph[line[1] - 1][line[0] - 1] = 1;
    }

    void initGraph(vector<vector<int>> &graph, int num) {
        for (int i = 0; i < num; i++) {
            graph.push_back(vector<int>());
            for (int j = 0; j < num; j++) {
                graph[i].push_back(0);
            }
        }
    }

    /*void buildGraph(const vector<vector<int>>& edges, vector<vector<int>> &graph) {
        int v = edges.size();
        for (int i = 0; i < v; i++) {
            graph.push_back(vector<int>());
            for (int j = 0; j < v; j++) {
                graph[i].push_back(0);
            }
        }

        for (int i = 0; i < v; i++) {
            graph[edges[i][0] - 1][edges[i][1] - 1] = graph[edges[i][1] - 1][edges[i][0] - 1] = 1;
        }
    }

    void dfs(const vector<vector<int>> &graph, int n, vector<bool> &visited) {
        visited[n] = true;
        for (int i = n + 1; i < graph.size(); i++) {
            if (!visited[i] && graph[n][i]) {
                dfs(graph, i, visited);
            } else if (visited[i]) {
                cout << "Find " << n + 1 << "--> " << i + 1 << endl;
                return;
            }
        }
    }*/
};
