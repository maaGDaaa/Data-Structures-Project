#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm> // Για std::remove_if

// Πληροφορίες ακμής
struct EdgeInfo {
    int to;
    int weight;

    bool operator==(const EdgeInfo& other) const {
        return to == other.to;
    }
};

// Κλάση γράφου
class Graph {
private:
    std::map<int, std::list<EdgeInfo>> adj; // Λίστα γειτνίασης
    std::set<int> vertices; // Κορυφές
    int num_edges; // Πλήθος ακμών

    void DFS(int u, std::map<int, bool>& visited) const; // Βαθιά αναζήτηση

    // Δομή για Disjoint Set Union (DSU)
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
    Graph(); // Κατασκευαστής
    ~Graph(); // Καταστροφέας

    bool buildFromFile(const std::string& filename); // Δημιουργία από αρχείο
    void insertEdge(int u, int v, int weight); // Εισαγωγή ακμής
    void removeEdge(int u, int v); // Αφαίρεση ακμής

    int vertexCount() const; // Πλήθος κορυφών
    int edgeCount() const; // Πλήθος ακμών

    int shortestPath(int startNode, int endNode) const; // Συντομότερο μονοπάτι
    int spanningTreeCost() const; // Κόστος ελάχιστου δέντρου κάλυψης
    int connectedComponents() const; // Συνδεδεμένα συστατικά
};

#endif // GRAPH_H