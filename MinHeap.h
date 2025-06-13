#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <string>
#include <stdexcept>

// Κλάση για ελάχιστη σωρό (Min Heap)
class MinHeap {
private:
    std::vector<int> heap; // Δομή δεδομένων για τη σωρό

    void heapifyUp(int index);   // Επαναφορά σωρού προς τα πάνω
    void heapifyDown(int index); // Επαναφορά σωρού προς τα κάτω
    void buildHeap();            // Δημιουργία σωρού από πίνακα

public:
    MinHeap(); // Κατασκευαστής

    bool buildFromFile(const std::string& filename); // Φόρτωση από αρχείο
    int getSize() const;     // Επιστρέφει το μέγεθος
    int findMin() const;     // Επιστρέφει το ελάχιστο
    void deleteMin();        // Διαγράφει το ελάχιστο
    void insert(int number); // Εισαγωγή στοιχείου
};

#endif 
