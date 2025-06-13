#include "Graph.h"
#include <fstream>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>

Graph::Graph() : num_edges(0) {}

Graph::~Graph() {
    adj.clear(); // καθαρισμα λιστας γειτονων
    vertices.clear(); // καθαρισμα κορυφων
    num_edges = 0; // μηδενισμος ακμων
}

bool Graph::buildFromFile(const std::string& filename) {
    adj.clear();
    vertices.clear();
    num_edges = 0;

    std::ifstream file(filename);
    int u, v, w;
    while (file >> u >> v >> w) {
        insertEdge(u, v, w); // προσθηκη ακμης απο αρχειο
    }
    return true;
}

void Graph::insertEdge(int u, int v, int weight) {
    vertices.insert(u); // προσθηκη κορυφης
    vertices.insert(v);

    bool found = false;
    for (const auto& edge : adj[u]) {
        if (edge.to == v) {
            found = true;
            return; // αν υπαρχει ηδη η ακμη, επιστροφη
        }
    }

    adj[u].push_back({v, weight}); // προσθηκη ακμης
    adj[v].push_back({u, weight}); // αμφιδρομη
    num_edges++;
}

void Graph::removeEdge(int u, int v) {
    bool removed = false;
    if (adj.count(u)) {
        auto& u_neighbors = adj[u];
        auto initial_size = u_neighbors.size();
        u_neighbors.remove_if([v](const EdgeInfo& edge){ return edge.to == v; });
        if (u_neighbors.size() < initial_size) removed = true;
    }

    if (adj.count(v)) {
         auto& v_neighbors = adj[v];
         v_neighbors.remove_if([u](const EdgeInfo& edge){ return edge.to == u; });
    }
    
    if (removed) {
        num_edges--; // μειωση αριθμου ακμων
    }
}

int Graph::vertexCount() const {
    return vertices.size(); // επιστροφη αριθμου κορυφων
}

int Graph::edgeCount() const {
    return num_edges; // επιστροφη αριθμου ακμων
}

void Graph::DFS(int u, std::map<int, bool>& visited) const {
    visited[u] = true; // σημειωσε ως επισκεπτομενο
    if (adj.count(u)) {
        for (const auto& edge : adj.at(u)) {
            if (!visited[edge.to]) {
                DFS(edge.to, visited); // αναδρομικη επισκεψη
            }
        }
    }
}

int Graph::connectedComponents() const {
    if (vertices.empty()) return 0;

    std::map<int, bool> visited;
    for (int v_node : vertices) {
        visited[v_node] = false;
    }

    int components = 0;
    for (int v_node : vertices) {
        if (!visited[v_node]) {
            DFS(v_node, visited); // βρες συνεκτικο συστατικο
            components++;
        }
    }
    return components;
}

int Graph::shortestPath(int startNode, int endNode) const {
    if (vertices.find(startNode) == vertices.end() || vertices.find(endNode) == vertices.end()) {
        return -1; // αν δεν υπαρχει κορυφη
    }
    if (startNode == endNode) return 0;

    std::map<int, int> dist;
    for (int v_node : vertices) {
        dist[v_node] = std::numeric_limits<int>::max();
    }
    dist[startNode] = 0;

    // ουρα προτεραιοτητας για dijkstra
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, startNode});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u] && dist[u] != std::numeric_limits<int>::max()) {
            if (u != startNode) continue;
            else if (d > 0) continue;
        }
        if (u == endNode) break;

        if (adj.count(u)) {
            for (const auto& edge : adj.at(u)) {
                int v_neighbor = edge.to;
                int weight = edge.weight;
                if (dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v_neighbor]) {
                    dist[v_neighbor] = dist[u] + weight;
                    pq.push({dist[v_neighbor], v_neighbor});
                }
            }
        }
    }

    return (dist[endNode] == std::numeric_limits<int>::max()) ? -1 : dist[endNode];
}

int Graph::spanningTreeCost() const {
    if (vertices.empty()) return 0;

    std::vector<std::tuple<int, int, int>> all_edges;
    std::set<std::pair<int,int>> added_edges_check;

    // συλλογη ολων των ακμων
    for (int u : vertices) {
        if (adj.count(u)) {
            for (const auto& edge : adj.at(u)) {
                int v = edge.to;
                int weight = edge.weight;
                if (u < v) {
                     if(added_edges_check.find({u,v}) == added_edges_check.end()){
                        all_edges.emplace_back(weight, u, v);
                        added_edges_check.insert({u,v});
                     }
                } else {
                     if(added_edges_check.find({v,u}) == added_edges_check.end()){
                        all_edges.emplace_back(weight, v, u);
                        added_edges_check.insert({v,u});
                     }
                }
            }
        }
    }
    
    if (all_edges.empty() && vertices.size() > 1 && connectedComponents() > 1) return -1;
    if (all_edges.empty() && vertices.size() <=1) return 0;

    std::sort(all_edges.begin(), all_edges.end()); // ταξινομηση ακμων

    DSU dsu(vertices);
    int mst_cost = 0;
    int edges_in_mst = 0;

    // Kruskal αλγοριθμος
    for (const auto& edge_tuple : all_edges) {
        int weight = std::get<0>(edge_tuple);
        int u = std::get<1>(edge_tuple);
        int v = std::get<2>(edge_tuple);

        if (dsu.find(u) != dsu.find(v)) {
            dsu.unite(u, v);
            mst_cost += weight;
            edges_in_mst++;
        }
    }

    if (vertexCount() > 0 && edges_in_mst < vertexCount() - connectedComponents() ) {
        if (connectedComponents() > 1 && vertexCount() > 1) return -1;
    }
    return mst_cost;
}