#include <fstream>
#include <sstream>
#include <chrono>
#include <string>
#include "AVLTree.h"

int main() {
    AVLTree avl;
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
            avl.buildFromFile(filename);
            auto end = std::chrono::high_resolution_clock::now();
            double ms = std::chrono::duration<double, std::milli>(end - start).count();
            outfile << "BUILD AVLTREE " << ms << "ms\n";
        }
        else if (cmd == "FINDMIN") {
            std::string what;
            iss >> what;
            try {
                int mn = avl.findMin();
                auto end = std::chrono::high_resolution_clock::now();
                double ms = std::chrono::duration<double, std::milli>(end - start).count();
                outfile << mn << " " << ms << "ms\n";
            } catch (...) {
                auto end = std::chrono::high_resolution_clock::now();
                double ms = std::chrono::duration<double, std::milli>(end - start).count();
                outfile << "FAILURE " << ms << "ms\n";
            }
        }
        else if (cmd == "SEARCH") {
            std::string what;
            int number;
            iss >> what >> number;
            bool found = avl.search(number);
            auto end = std::chrono::high_resolution_clock::now();
            double ms = std::chrono::duration<double, std::milli>(end - start).count();
            outfile << (found ? "SUCCESS" : "FAILURE") << " " << ms << "ms\n";
        }
        else if (cmd == "INSERT") {
            std::string what;
            int number;
            iss >> what >> number;
            avl.insert(number);
            auto end = std::chrono::high_resolution_clock::now();
            double ms = std::chrono::duration<double, std::milli>(end - start).count();
            outfile << "INSERTED " << ms << "ms\n";
        }
        else if (cmd == "DELETE") {
            std::string what;
            int number;
            iss >> what >> number;
            avl.remove(number);
            auto end = std::chrono::high_resolution_clock::now();
            double ms = std::chrono::duration<double, std::milli>(end - start).count();
            outfile << "DELETED " << ms << "ms\n";
        }
        else if (cmd == "GETSIZE") {
            std::string what;
            iss >> what;
            int n = avl.size();
            auto end = std::chrono::high_resolution_clock::now();
            double ms = std::chrono::duration<double, std::milli>(end - start).count();
            outfile << n << " " << ms << "ms\n";
        }
    }
    return 0;
}