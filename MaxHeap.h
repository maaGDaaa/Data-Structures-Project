#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>
#include <string>

class MaxHeap {
private:
    std::vector<int> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);
    void buildHeap();

public:
    MaxHeap() = default;

    // Κατασκευή σωρού από vector
    MaxHeap(const std::vector<int>& elements);



    // Κατασκευή σωρού από αρχείο
    bool buildFromFile(const std::string& filename);

    int getSize() const;

    // Εύρεση μέγιστου στοιχείου (root)
    int findMax() const;

    // Διαγραφή μέγιστου στοιχείου
    bool deleteMax();

    // Εισαγωγή νέου στοιχείου
    void insert(int value);

    // Για έλεγχο αν είναι άδειος
    bool isEmpty() const;
};

#endif
