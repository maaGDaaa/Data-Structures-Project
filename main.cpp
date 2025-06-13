#include <fstream>
#include <sstream>
#include <chrono>
#include <string>
#include <iostream>
#include "AVLTree.h"
#include "MinHeap.h"
#include "MaxHeap.h"
#include "HashTable.h"
#include "Graph.h"

int main() {
    // Δημιουργία δομών δεδομένων
    AVLTree avl;
    MinHeap minheap;
    MaxHeap maxheap;
    HashTable hashtable;
    Graph graph;

    // Flags για το αν έχουν χτιστεί οι δομές
    bool avlBuilt = false;
    bool minheapBuilt = false;
    bool maxheapBuilt = false;
    bool hashtableBuilt = false;
    bool graphBuilt = false;

    std::ifstream cmdfile("commands.txt");
    std::ofstream outfile("output.txt");
    std::string line;

    if (!cmdfile.is_open()) {
        std::cerr << "Error: Could not open commands.txt" << std::endl;
        return 1;
    }
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not create/open output.txt" << std::endl;
        return 1;
    }

    // Επεξεργασία εντολών από το αρχείο
    while (std::getline(cmdfile, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        auto start = std::chrono::high_resolution_clock::now();
        double ms;

        if (cmd == "BUILD") {
            std::string what, filename;
            iss >> what >> filename;
            try {
                // Χτίσιμο δομής από αρχείο
                if (what == "MINHEAP") {
                    if (minheap.buildFromFile(filename)) {
                        minheapBuilt = true;
                        auto end = std::chrono::high_resolution_clock::now();
                        ms = std::chrono::duration<double, std::milli>(end - start).count();
                        outfile << "BUILD MINHEAP " << ms << "ms\n";
                    } else {
                        outfile << "FAILURE BUILD MINHEAP\n";
                    }
                } else if (what == "MAXHEAP") {
                    if (maxheap.buildFromFile(filename)) {
                        maxheapBuilt = true;
                        auto end = std::chrono::high_resolution_clock::now();
                        ms = std::chrono::duration<double, std::milli>(end - start).count();
                        outfile << "BUILD MAXHEAP " << ms << "ms\n";
                    } else {
                        outfile << "FAILURE BUILD MAXHEAP\n";
                    }
                } else if (what == "AVLTREE") {
                    if (avl.buildFromFile(filename)) {
                        avlBuilt = true;
                        auto end = std::chrono::high_resolution_clock::now();
                        ms = std::chrono::duration<double, std::milli>(end - start).count();
                        outfile << "BUILD AVLTREE " << ms << "ms\n";
                    } else {
                        outfile << "FAILURE BUILD AVLTREE\n";
                    }
                } else if (what == "HASHTABLE") {
                    if (hashtable.buildFromFile(filename)) {
                        hashtableBuilt = true;
                        auto end = std::chrono::high_resolution_clock::now();
                        ms = std::chrono::duration<double, std::milli>(end - start).count();
                        outfile << "BUILD HASHTABLE " << ms << "ms\n";
                    } else {
                        outfile << "FAILURE BUILD HASHTABLE\n";
                    }
                } else if (what == "GRAPH") {
                    if (graph.buildFromFile(filename)) {
                        graphBuilt = true;
                        auto end = std::chrono::high_resolution_clock::now();
                        ms = std::chrono::duration<double, std::milli>(end - start).count();
                        outfile << "BUILD GRAPH " << ms << "ms\n";
                    } else {
                        outfile << "FAILURE BUILD GRAPH\n";
                    }
                } else {
                    outfile << "FAILURE BUILD UNKNOWN_STRUCTURE\n";
                }
            } catch (...) {
                outfile << "FAILURE BUILD EXCEPTION\n";
            }
        }
        else if (cmd == "GETSIZE") {
            std::string what;
            iss >> what;
            try {
                int size1 = -1, size2 = -1;
                bool is_graph = false;

                // Επιστροφή μεγέθους δομής
                if (what == "MINHEAP") {
                    if (!minheapBuilt) { outfile << "FAILURE MINHEAP NOT BUILT\n"; continue; }
                    size1 = minheap.getSize();
                } else if (what == "MAXHEAP") {
                    if (!maxheapBuilt) { outfile << "FAILURE MAXHEAP NOT BUILT\n"; continue; }
                    size1 = maxheap.getSize();
                } else if (what == "AVLTREE") {
                    if (!avlBuilt) { outfile << "FAILURE AVLTREE NOT BUILT\n"; continue; }
                    size1 = avl.size();
                } else if (what == "HASHTABLE") {
                    if (!hashtableBuilt) { outfile << "FAILURE HASHTABLE NOT BUILT\n"; continue; }
                    size1 = hashtable.getSize();
                } else if (what == "GRAPH") {
                    if (!graphBuilt) { outfile << "FAILURE GRAPH NOT BUILT\n"; continue; }
                    size1 = graph.vertexCount();
                    size2 = graph.edgeCount();
                    is_graph = true;
                } else {
                    outfile << "FAILURE GETSIZE INVALID STRUCTURE\n";
                    continue;
                }
                auto end = std::chrono::high_resolution_clock::now();
                ms = std::chrono::duration<double, std::milli>(end - start).count();
                if (is_graph) {
                    outfile << size1 << " " << size2 << " " << ms << "ms\n";
                } else {
                    outfile << size1 << " " << ms << "ms\n";
                }
            } catch (...) {
                outfile << "FAILURE GETSIZE EXCEPTION\n";
            }
        }
        else if (cmd == "FINDMIN") {
            std::string what;
            iss >> what;
            try {
                // Εύρεση ελάχιστου στοιχείου
                if (what == "MINHEAP") {
                    if (!minheapBuilt) { outfile << "FAILURE MINHEAP NOT BUILT\n"; continue;}
                    int mn = minheap.findMin();
                    auto end = std::chrono::high_resolution_clock::now();
                    ms = std::chrono::duration<double, std::milli>(end - start).count();
                    outfile << mn << " " << ms << "ms\n";
                } else if (what == "AVLTREE") {
                    if (!avlBuilt) { outfile << "FAILURE AVLTREE NOT BUILT\n"; continue; }
                    int mn = avl.findMin();
                    auto end = std::chrono::high_resolution_clock::now();
                    ms = std::chrono::duration<double, std::milli>(end - start).count();
                    outfile << mn << " " << ms << "ms\n";
                } else {
                    outfile << "FAILURE FINDMIN INVALID STRUCTURE\n";
                }
            } catch (...) {
                outfile << "FAILURE FINDMIN EMPTY OR ERROR\n";
            }
        }
        else if (cmd == "FINDMAX") {
            std::string what;
            iss >> what;
            try {
                // Εύρεση μέγιστου στοιχείου
                 if (what == "MAXHEAP") {
                    if (!maxheapBuilt) { outfile << "FAILURE MAXHEAP NOT BUILT\n"; continue; }
                    int mx = maxheap.findMax();
                    auto end = std::chrono::high_resolution_clock::now();
                    ms = std::chrono::duration<double, std::milli>(end - start).count();
                    outfile << mx << " " << ms << "ms\n";
                } else {
                    outfile << "FAILURE FINDMAX INVALID STRUCTURE\n";
                }
            } catch (...) {
                outfile << "FAILURE FINDMAX EMPTY OR ERROR\n";
            }
        }
        else if (cmd == "INSERT") {
            std::string what;
            iss >> what;
            try {
                // Εισαγωγή στοιχείου
                if (what == "MINHEAP") {
                    if (!minheapBuilt) { outfile << "FAILURE MINHEAP NOT BUILT\n"; continue; }
                    int number; iss >> number; minheap.insert(number);
                } else if (what == "MAXHEAP") {
                    if (!maxheapBuilt) { outfile << "FAILURE MAXHEAP NOT BUILT\n"; continue; }
                    int number; iss >> number; maxheap.insert(number);
                } else if (what == "AVLTREE") {
                    if (!avlBuilt) { outfile << "FAILURE AVLTREE NOT BUILT\n"; continue; }
                    int number; iss >> number; avl.insert(number);
                } else if (what == "HASHTABLE") {
                    if (!hashtableBuilt) { outfile << "FAILURE HASHTABLE NOT BUILT\n"; continue; }
                    int number; iss >> number; hashtable.insert(number);
                } else if (what == "GRAPH") {
                    if (!graphBuilt) { outfile << "FAILURE GRAPH NOT BUILT\n"; continue; }
                    int n1, n2, weight; iss >> n1 >> n2 >> weight;
                    graph.insertEdge(n1, n2, weight);
                } else {
                    outfile << "FAILURE INSERT INVALID STRUCTURE\n";
                    continue;
                }
                auto end = std::chrono::high_resolution_clock::now();
                ms = std::chrono::duration<double, std::milli>(end - start).count();
                outfile << "INSERTED " << ms << "ms\n";

            } catch (...) {
                outfile << "FAILURE INSERT EXCEPTION\n";
            }
        }
        else if (cmd == "DELETE") {
            std::string what;
            iss >> what;
            try {
                // Διαγραφή στοιχείου
                if (what == "MINHEAP") {
                    if (!minheapBuilt) { outfile << "FAILURE MINHEAP NOT BUILT\n"; continue; }
                    minheap.deleteMin();
                } else if (what == "MAXHEAP") {
                    if (!maxheapBuilt) { outfile << "FAILURE MAXHEAP NOT BUILT\n"; continue; }
                    maxheap.deleteMax();
                } else if (what == "AVLTREE") {
                    if (!avlBuilt) { outfile << "FAILURE AVLTREE NOT BUILT\n"; continue; }
                    int number; iss >> number; avl.remove(number);
                } else if (what == "GRAPH") {
                    if (!graphBuilt) { outfile << "FAILURE GRAPH NOT BUILT\n"; continue; }
                    int n1, n2; iss >> n1 >> n2;
                    graph.removeEdge(n1, n2);
                } else {
                    outfile << "FAILURE DELETE INVALID STRUCTURE\n";
                    continue;
                }
                auto end = std::chrono::high_resolution_clock::now();
                ms = std::chrono::duration<double, std::milli>(end - start).count();
                outfile << "DELETED " << ms << "ms\n";

            } catch (...) {
                outfile << "FAILURE DELETE EXCEPTION\n";
            }
        }
        else if (cmd == "SEARCH") {
            std::string what; int number;
            iss >> what >> number;
            try {
                // Αναζήτηση στοιχείου
                bool found = false;
                if (what == "AVLTREE") {
                    if (!avlBuilt) { outfile << "FAILURE AVLTREE NOT BUILT\n"; continue; }
                    found = avl.search(number);
                } else if (what == "HASHTABLE") {
                    if (!hashtableBuilt) { outfile << "FAILURE HASHTABLE NOT BUILT\n"; continue; }
                    found = hashtable.search(number);
                } else {
                    outfile << "FAILURE SEARCH INVALID STRUCTURE\n";
                    continue;
                }
                auto end = std::chrono::high_resolution_clock::now();
                ms = std::chrono::duration<double, std::milli>(end - start).count();
                outfile << (found ? "SUCCESS" : "FAILURE") << " " << ms << "ms\n";
            } catch (...) {
                outfile << "FAILURE SEARCH EXCEPTION\n";
            }
        }
        else if (cmd == "COMPUTESHORTESTPATH") {
            std::string what; int n1, n2;
            iss >> what >> n1 >> n2;
            if (what == "GRAPH") {
                if (!graphBuilt) { outfile << "FAILURE GRAPH NOT BUILT\n"; continue; }
                try {
                    // Υπολογισμός συντομότερης διαδρομής
                    int cost = graph.shortestPath(n1, n2);
                    auto end = std::chrono::high_resolution_clock::now();
                    ms = std::chrono::duration<double, std::milli>(end - start).count();
                    outfile << cost << " " << ms << "ms\n";
                } catch (...) {
                    outfile << "FAILURE COMPUTESHORTESTPATH EXCEPTION\n";
                }
            } else {
                outfile << "FAILURE COMPUTESHORTESTPATH INVALID STRUCTURE\n";
            }
        }
        else if (cmd == "COMPUTESPANNINGTREE") {
            std::string what;
            iss >> what;
            if (what == "GRAPH") {
                if (!graphBuilt) { outfile << "FAILURE GRAPH NOT BUILT\n"; continue; }
                try {
                    // Υπολογισμός ελάχιστου δέντρου κάλυψης
                    int cost = graph.spanningTreeCost();
                    auto end = std::chrono::high_resolution_clock::now();
                    ms = std::chrono::duration<double, std::milli>(end - start).count();
                    outfile << cost << " " << ms << "ms\n";
                } catch (...) {
                    outfile << "FAILURE COMPUTESPANNINGTREE EXCEPTION\n";
                }
            } else {
                outfile << "FAILURE COMPUTESPANNINGTREE INVALID STRUCTURE\n";
            }
        }
        else if (cmd == "FINDCONNECTEDCOMPONENTS") {
            std::string what;
            iss >> what;
            if (what == "GRAPH") {
                if (!graphBuilt) { outfile << "FAILURE GRAPH NOT BUILT\n"; continue; }
                try {
                    // Εύρεση συνδεδεμένων συνιστωσών
                    int components = graph.connectedComponents();
                    auto end = std::chrono::high_resolution_clock::now();
                    ms = std::chrono::duration<double, std::milli>(end - start).count();
                    outfile << components << " " << ms << "ms\n";
                } catch (...) {
                    outfile << "FAILURE FINDCONNECTEDCOMPONENTS EXCEPTION\n";
                }
            } else {
                outfile << "FAILURE FINDCONNECTEDCOMPONENTS INVALID STRUCTURE\n";
            }
        }
        else {
            // Άγνωστη εντολή
            outfile << "FAILURE UNKNOWN COMMAND (" << cmd << ")\n";
        }
    }

    cmdfile.close();
    outfile.close();
    return 0;
}