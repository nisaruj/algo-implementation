#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

class Edge {
    public:
    int node1, node2;
    int distance;
    Edge(int node1, int node2, int distance) {
        this -> node1 = node1;
        this -> node2 = node2;
        this -> distance = distance;
    }
};

class CompareEdge {
    public:
    bool operator() (Edge a, Edge b) {
        return a.distance < b.distance;
    }
    CompareEdge () {};
};

int myFind(vector<int>& parent, int node) {
    if (parent[node] == 0) return node;
    return myFind(parent, parent[node]);
}

bool myUnion(vector<int>& parent, int node1, int node2) {
    int root1 = myFind(parent, node1);
    int root2 = myFind(parent, node2);
    if (root1 == root2) return false;
    parent[root2] = root1;
    return true;
}

vector<Edge> MST(vector<Edge> edges) {
    vector<int> parent(10000);
    vector<Edge> res;
    sort(edges.begin(), edges.end(), CompareEdge());
    for (auto e: edges) {
        if (res.size() == edges.size() - 1) break;
        if (myUnion(parent, e.node1, e.node2)) res.push_back(e);
    }
    return res;
}

int main() {
    /* Testcase 
    1 2 50
    1 3 80
    2 3 60
    2 4 20
    3 5 40
    2 5 30
    4 5 10
    4 6 10
    5 6 50
    MST should return 
    4 6 10
    4 5 10
    2 4 20
    3 5 40
    1 2 50
    Sum of distance is 130.
    */
    vector<Edge> edges = {Edge(1, 2, 50), Edge(1, 3, 80), Edge(2, 3, 60), Edge(2, 4, 20), Edge(3, 5, 40),
        Edge(2, 5, 30), Edge(4, 5, 10), Edge(4, 6, 10), Edge(5, 6, 50)};  
    for (auto e: MST(edges)) {
        cout << e.node1 << " " << e.node2 << " " << e.distance << endl;
    }
}
