#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <string>

class HashTable {
private:
    static const int TABLE_SIZE = 103; // A prime number for better distribution
    std::vector<std::list<int>> table;
    int numElements;

    int hashFunction(int key) const;

public:
    HashTable();

    bool buildFromFile(const std::string& filename);
    int getSize() const;
    bool search(int number) const;
    void insert(int number);
};

#endif
