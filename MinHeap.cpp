#include "MinHeap.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Προεπιλεγμένος κατασκευαστής
MinHeap::MinHeap() {}

// Μετακινεί το στοιχείο προς τα πάνω για διατήρηση της ιδιότητας του σωρού
void MinHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent] > heap[index]) {
            std::swap(heap[parent], heap[index]);
            index = parent;
        } else {
            break;
        }
    }
}

// Μετακινεί το στοιχείο προς τα κάτω για διατήρηση της ιδιότητας του σωρού
void MinHeap::heapifyDown(int index) {
    int size = heap.size();
    while (index < size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && heap[left] < heap[smallest])
            smallest = left;
        if (right < size && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

// Δημιουργεί σωρό από το τρέχον vector
void MinHeap::buildHeap() {
    for (int i = heap.size() / 2 - 1; i >= 0; --i) {
        heapifyDown(i);
    }
}

// Δημιουργεί σωρό από αρχείο, επιστρέφει true αν πετύχει
bool MinHeap::buildFromFile(const std::string& filename) {
    heap.clear();
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        try {
            int value = std::stoi(line);
            heap.push_back(value);
        } catch (...) {
            std::cerr << "Μη έγκυρη τιμή στο αρχείο: '" << line << "'\n";
            return false;
        }
    }

    file.close();
    buildHeap();
    return true;
}

// Επιστρέφει το μέγεθος του σωρού
int MinHeap::getSize() const {
    return heap.size();
}

// Επιστρέφει το ελάχιστο στοιχείο
int MinHeap::findMin() const {
    if (heap.empty()) {
        throw std::runtime_error("Ο σωρός είναι άδειος");
    }
    return heap[0];
}

// Διαγράφει το ελάχιστο στοιχείο
void MinHeap::deleteMin() {
    if (heap.empty()) {
        throw std::runtime_error("Ο σωρός είναι άδειος");
    }
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
}

// Εισάγει νέο στοιχείο
void MinHeap::insert(int number) {
    heap.push_back(number);
    heapifyUp(heap.size() - 1);
}
