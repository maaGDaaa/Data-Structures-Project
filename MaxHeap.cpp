#include "MaxHeap.h"
#include <fstream>
#include <iostream>
#include <sstream>

void MaxHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent] >= heap[index]) break;
        std::swap(heap[parent], heap[index]);
        index = parent;
    }
}

void MaxHeap::heapifyDown(int index) {
    int size = (int)heap.size();
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size && heap[left] > heap[largest])
            largest = left;
        if (right < size && heap[right] > heap[largest])
            largest = right;

        if (largest == index) break;

        std::swap(heap[index], heap[largest]);
        index = largest;
    }
}

MaxHeap::MaxHeap(const std::vector<int>& elements) {
    heap = elements;
    // Δημιουργία σωρού (heapify) από το vector
    for (int i = (int)heap.size() / 2 - 1; i >= 0; --i) {
        heapifyDown(i);
    }
}

void MaxHeap::buildHeap() {
    for (int i = (int)heap.size() / 2 - 1; i >= 0; --i) {
        heapifyDown(i);
    }
}


bool MaxHeap::buildFromFile(const std::string& filename) {
    heap.clear();
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;  // Δεν άνοιξε το αρχείο
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        try {
            int value = std::stoi(line);
            heap.push_back(value);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid value in file: '" << line << "'\n";
            return false;  // Μη έγκυρη τιμή στο αρχείο
        }
    }

    file.close();
    buildHeap();  // Κατασκευή MaxHeap από το vector heap
    return true;  // Επιτυχής κατασκευή
}

int MaxHeap::getSize() const {
    return (int)heap.size();
}

int MaxHeap::findMax() const {
    if (heap.empty()) {
        std::cerr << "MaxHeap is empty\n";
        return -1; 
    }
    return heap[0];
}

bool MaxHeap::deleteMax() {
    if (heap.empty()) return false;

    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
    return true;
}

void MaxHeap::insert(int value) {
    heap.push_back(value);
    heapifyUp((int)heap.size() - 1);
}

bool MaxHeap::isEmpty() const {
    return heap.empty();
}
