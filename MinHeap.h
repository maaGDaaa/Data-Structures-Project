#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <string>
#include <stdexcept>

class MinHeap {
private:
    std::vector<int> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);
    void buildHeap();

public:
    MinHeap();

    bool buildFromFile(const std::string& filename);
    int getSize() const;
    int findMin() const;
    void deleteMin();
    void insert(int number);
};

#endif // MINHEAP_H
