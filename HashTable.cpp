#include "HashTable.h"
#include <fstream>
#include <iostream>
#include <sstream>

HashTable::HashTable() : table(TABLE_SIZE), numElements(0) {}

int HashTable::hashFunction(int key) const {
    return key % TABLE_SIZE;
}

bool HashTable::buildFromFile(const std::string& filename) {
    table.clear();
    table.resize(TABLE_SIZE);
    numElements = 0;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << "\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        try {
            int value = std::stoi(line);
            insert(value);
        } catch (const std::exception& e) {
            std::cerr << "Invalid line in file: " << line << "\n";
        }
    }

    file.close();
    return true;
}

int HashTable::getSize() const {
    return numElements;
}

bool HashTable::search(int number) const {
    int index = hashFunction(number);
    for (int val : table[index]) {
        if (val == number) {
            return true;  // Βρέθηκε
        }
    }
    return false; // Δεν βρέθηκε
}


void HashTable::insert(int number) {
    int index = hashFunction(number);
    for (int val : table[index]) {
        if (val == number) return; // Avoid duplicates
    }
    table[index].push_back(number);
    ++numElements;
}
