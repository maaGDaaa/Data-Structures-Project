#include <fstream>
#include <sstream>
#include <chrono>
#include <string>
#include <iostream>
#include "AVLTree.h"
#include "MaxHeap.h"
#include "MinHeap.h"
#include "HashTable.h"

int main() {
    AVLTree avl;
    MinHeap minheap;
    MaxHeap maxheap;
    HashTable hashtable;

    bool avlBuilt = false;
    bool minheapBuilt = false;
    bool maxheapBuilt = false;
    bool hashtableBuilt = false;

    std::ifstream cmdfile("commands.txt");
    std::ofstream outfile("output.txt");
    std::string line;

    while (std::getline(cmdfile, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        auto start = std::chrono::high_resolution_clock::now();

        if (cmd == "BUILD") {
            std::string what, filename;
            iss >> what >> filename;
            try {
                if (what == "MINHEAP") {
                    if (minheap.buildFromFile(filename)) {
                        minheapBuilt = true;
                        auto end = std::chrono::high_resolution_clock::now();
                        double ms = std::chrono::duration<double, std::milli>(end - start).count();
                        outfile << "BUILD MINHEAP " << ms << "ms\n";
                    } else {
                        outfile << "FAILURE BUILD MINHEAP\n";
                    }
                }
                else if (what == "MAXHEAP") {
                    if (maxheap.buildFromFile(filename)) {
                        maxheapBuilt = true;
                        auto end = std::chrono::high_resolution_clock::now();
                        double ms = std::chrono::duration<double, std::milli>(end - start).count();
                        outfile << "BUILD MAXHEAP " << ms << "ms\n";
                    } else {
                        outfile << "FAILURE BUILD MAXHEAP\n";
                    }
                }
                else if (what == "AVLTREE") {
                    if (avl.buildFromFile(filename)) {
                        avlBuilt = true;
                        auto end = std::chrono::high_resolution_clock::now();
                        double ms = std::chrono::duration<double, std::milli>(end - start).count();
                        outfile << "BUILD AVLTREE " << ms << "ms\n";
                    } else {
                        outfile << "FAILURE BUILD AVLTREE\n";
                    }
                }
                else if (what == "HASHTABLE") {
                    if (hashtable.buildFromFile(filename)) {
                        hashtableBuilt = true;
                        auto end = std::chrono::high_resolution_clock::now();
                        double ms = std::chrono::duration<double, std::milli>(end - start).count();
                        outfile << "BUILD HASHTABLE " << ms << "ms\n";
                    } else {
                        outfile << "FAILURE BUILD HASHTABLE\n";
                    }
                }
            } catch (...) {
                outfile << "FAILURE BUILD\n";
            }
        }
        else if (cmd == "FINDMIN") {
            std::string what; 
            iss >> what;
            try {
                if (what == "MINHEAP") {
                    if (!minheapBuilt) {
                        outfile << "FAILURE MINHEAP NOT BUILT\n";
                    } else {
                        int mn = minheap.findMin();
                        auto end = std::chrono::high_resolution_clock::now();
                        double ms = std::chrono::duration<double, std::milli>(end - start).count();
                        outfile << mn << " " << ms << "ms\n";
                    }
                }
                else if (what == "AVLTREE") {
                    if (!avlBuilt) {
                        outfile << "FAILURE AVLTREE NOT BUILT\n";
                    } else {
                        int mn = avl.findMin();
                        auto end = std::chrono::high_resolution_clock::now();
                        double ms = std::chrono::duration<double, std::milli>(end - start).count();
                        outfile << mn << " " << ms << "ms\n";
                    }
                }
                else {
                    outfile << "FAILURE INVALID STRUCTURE\n";
                }
            } catch (...) {
                outfile << "FAILURE EMPTY STRUCTURE\n";
            }
        }
        else if (cmd == "FINDMAX") {
            std::string what; 
            iss >> what;
            try {
                if (what == "MAXHEAP") {
                    if (!maxheapBuilt) {
                        outfile << "FAILURE MAXHEAP NOT BUILT\n";
                    } else {
                        int mx = maxheap.findMax();
                        auto end = std::chrono::high_resolution_clock::now();
                        double ms = std::chrono::duration<double, std::milli>(end - start).count();
                        outfile << mx << " " << ms << "ms\n";
                    }
                } else {
                    outfile << "FAILURE INVALID STRUCTURE\n";
                }
            } catch (...) {
                outfile << "FAILURE EMPTY STRUCTURE\n";
            }
        }
            else if (cmd == "INSERT") {
                std::string what; int number;
                iss >> what >> number;
                try {
                    if (what == "MINHEAP") {
                        if (!minheapBuilt) {
                            outfile << "FAILURE MINHEAP NOT BUILT\n";
                        } else {
                            minheap.insert(number);
                            auto end = std::chrono::high_resolution_clock::now();
                            double ms = std::chrono::duration<double, std::milli>(end - start).count();
                            outfile << "INSERTED " << ms << "ms\n";
                        }
                    }
                    else if (what == "MAXHEAP") {
                        if (!maxheapBuilt) {
                            outfile << "FAILURE MAXHEAP NOT BUILT\n";
                        } else {
                            maxheap.insert(number);
                            auto end = std::chrono::high_resolution_clock::now();
                            double ms = std::chrono::duration<double, std::milli>(end - start).count();
                            outfile << "INSERTED " << ms << "ms\n";
                        }
                    }
                    else if (what == "AVLTREE") {
                        if (!avlBuilt) {
                            outfile << "FAILURE AVLTREE NOT BUILT\n";
                        } else {
                            avl.insert(number);
                            auto end = std::chrono::high_resolution_clock::now();
                            double ms = std::chrono::duration<double, std::milli>(end - start).count();
                            outfile << "INSERTED " << ms << "ms\n";
                        }
                    }
                    else if (what == "HASHTABLE") {
                        if (!hashtableBuilt) {
                            outfile << "FAILURE HASHTABLE NOT BUILT\n";
                        } else {
                            hashtable.insert(number);
                            auto end = std::chrono::high_resolution_clock::now();
                            double ms = std::chrono::duration<double, std::milli>(end - start).count();
                            outfile << "INSERTED " << ms << "ms\n";
                        }
                    }
                    else {
                        outfile << "FAILURE INVALID STRUCTURE\n";
                    }
                } catch (...) {
                    outfile << "FAILURE INSERT\n";
                }
            }

        else if (cmd == "DELETE") {
            std::string what; int number;
            iss >> what >> number;
            try {
                if (what == "MINHEAP") {
                    if (!minheapBuilt) {
                        outfile << "FAILURE MINHEAP NOT BUILT\n";
                    } else {
                        minheap.deleteMin();
                        auto end = std::chrono::high_resolution_clock::now();
                        double ms = std::chrono::duration<double, std::milli>(end - start).count();
                        outfile << "DELETED " << ms << "ms\n";
                    }
                }
                else if (what == "MAXHEAP") {
                    if (!maxheapBuilt) {
                        outfile << "FAILURE MAXHEAP NOT BUILT\n";
                    } else {
                        maxheap.deleteMax();
                        auto end = std::chrono::high_resolution_clock::now();
                        double ms = std::chrono::duration<double, std::milli>(end - start).count();
                        outfile << "DELETED " << ms << "ms\n";
                    }
                }
                else if (what == "AVLTREE") {
                    if (!avlBuilt) {
                        outfile << "FAILURE AVLTREE NOT BUILT\n";
                    } else {
                        avl.remove(number);
                        auto end = std::chrono::high_resolution_clock::now();
                        double ms = std::chrono::duration<double, std::milli>(end - start).count();
                        outfile << "DELETED " << ms << "ms\n";
                    }
                }
                else {
                    outfile << "FAILURE INVALID STRUCTURE\n";
                }
            } catch (...) {
                outfile << "FAILURE DELETE\n";
            }
        }
        else if (cmd == "SEARCH") {
            std::string what; int number;
            iss >> what >> number;
            try {
                if (what == "AVLTREE") {
                    if (!avlBuilt) {
                        outfile << "FAILURE AVLTREE NOT BUILT\n";
                    } else {
                        bool found = avl.search(number);
                        auto end = std::chrono::high_resolution_clock::now();
                        double ms = std::chrono::duration<double, std::milli>(end - start).count();
                        outfile << (found ? "SUCCESS" : "FAILURE") << " " << ms << "ms\n";
                    }
                } 
                else if (what == "HASHTABLE") {
                    if (!hashtableBuilt) {
                        outfile << "FAILURE HASHTABLE NOT BUILT\n";
                    } else {
                        bool found = hashtable.search(number);
                        auto end = std::chrono::high_resolution_clock::now();
                        double ms = std::chrono::duration<double, std::milli>(end - start).count();
                        outfile << (found ? "SUCCESS" : "FAILURE") << " " << ms << "ms\n";
                    }
                }
                else {
                    outfile << "FAILURE INVALID STRUCTURE\n";
                }
            } catch (...) {
                outfile << "FAILURE SEARCH\n";
            }
        }
        else if (cmd == "GETSIZE") {
            std::string what;
            iss >> what;
            try {
                int size = -1;
                if (what == "MINHEAP") {
                    if (!minheapBuilt) {
                        outfile << "FAILURE MINHEAP NOT BUILT\n";
                        continue;
                    }
                    size = minheap.getSize();
                }
                else if (what == "MAXHEAP") {
                    if (!maxheapBuilt) {
                        outfile << "FAILURE MAXHEAP NOT BUILT\n";
                        continue;
                    }
                    size = maxheap.getSize();
                }
                else if (what == "AVLTREE") {
                    if (!avlBuilt) {
                        outfile << "FAILURE AVLTREE NOT BUILT\n";
                        continue;
                    }
                    size = avl.size();
                }
                else if (what == "HASHTABLE") {
                    if (!hashtableBuilt) {
                        outfile << "FAILURE HASHTABLE NOT BUILT\n";
                        continue;
                    }
                    size = hashtable.getSize();
                }
                else {
                    outfile << "FAILURE INVALID STRUCTURE\n";
                    continue;
                }
                auto end = std::chrono::high_resolution_clock::now();
                double ms = std::chrono::duration<double, std::milli>(end - start).count();
                outfile << size << " " << ms << "ms\n";
            } catch (...) {
                outfile << "FAILURE GETSIZE\n";
            }
        }
        else {
            outfile << "FAILURE UNKNOWN COMMAND\n";
        }
    }

    cmdfile.close();
    outfile.close();
    return 0;
}
