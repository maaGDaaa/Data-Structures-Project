#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm> // For std::remove_if

struct EdgeInfo {
    int to;
    int weight;

    bool operator==(const EdgeInfo& other) const {
        return to == other.to;
    }
};


class Graph {
private:
    std::map<int, std::list<EdgeInfo>> adj;
    std::set<int> vertices;
    int num_edges;

    void DFS(int u, std::map<int, bool>& visited) const;

    struct DSU {
        std::map<int, int> parent;
        std::map<int, int> rank;

        DSU(const std::set<int>& nodes) {
            for (int node : nodes) {
                parent[node] = node;
                rank[node] = 0;
            }
        }

        int find(int i) {
            if (parent.find(i) == parent.end()) {
                parent[i] = i;
                rank[i] = 0;
            }
            if (parent[i] == i)
                return i;
            return parent[i] = find(parent[i]);
        }

        void unite(int i, int j) {
            int root_i = find(i);
            int root_j = find(j);
            if (root_i != root_j) {
                if (rank[root_i] < rank[root_j]) std::swap(root_i, root_j);
                parent[root_j] = root_i;
                if (rank[root_i] == rank[root_j]) rank[root_i]++;
            }
        }
    };


public:
    Graph();
    ~Graph();

    bool buildFromFile(const std::string& filename);
    void insertEdge(int u, int v, int weight);
    void removeEdge(int u, int v);

    int vertexCount() const;
    int edgeCount() const;

    int shortestPath(int startNode, int endNode) const;
    int spanningTreeCost() const;
    int connectedComponents() const;
};

#endif // GRAPH_H