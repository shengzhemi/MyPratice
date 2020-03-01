#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    int minMalwareSpread(vector<vector<int> >& graph, vector<int>& initial) {
        vector<int> v;
        v.resize(graph.size());
        for (int i = 0; i < v.size(); i++){
            v[i] = i;
        }

        for (int i = 0; i < graph.size(); i++) {
            for (int j = i; j < graph[i].size(); j++) {
                if (graph[i][j] == 1) {
                    adjust(v, i, j);
                }
            }
        }

        /*cout << "collections: " << endl;
        for (int i = 0; i < v.size(); i++){
            cout << "v[" << i << "]= " << v[i] << endl;
        }*/

        map<int, int> m;
        for (int i = 0; i < v.size(); i++) {
            int root = v[i];
            m[root] += 1;
        }

        int maxNum = 0;
        int index = 0;
        for (int i = 0; i < initial.size(); i++) {
            int root = v[initial[i]];
            //cout << "---" << initial[i] << " " << root << " " << m[root] << endl;
            if (m[root] > maxNum) {
                maxNum = m[root];
                index = initial[i];
            }
        }

        return index;
    }

    void adjust(vector<int> &v, int pos, int pre) {
        int root = find(v, pos);
        /*if (root == pos) {
            //v[pos] = pre;
            //return;
        }*/

        root = (pre > root) ? pre : root;
        int next = pos;
        int current = pos;
        while (v[current] != root) {
            next = v[current];
            v[current] = root;
            current = next;
        }
    }

    int find(vector<int> v, int pos) {
        int root = pos;
        //std::cout << "-cur:" << root << " pre:" << v[root] << std::endl;
        while (v[root] != root) {
            root = v[root];
        }
        return root;
    }
};

int main(int argc, char **argv) {
    return 0;
}
