[README.md](https://github.com/user-attachments/files/34964413/README.md)
# Data Structures Project (C++)

An academic C++ project exploring the implementation and use of fundamental data structures and graph algorithms. The code is organized into separate classes with header (`.h`) and implementation (`.cpp`) files.

## Implemented data structures

- **AVL tree:** a self-balancing binary search tree with insertion, searching, deletion, and rotations.
- **Min-heap and max-heap:** heap-based data structures with their own implementations.
- **Hash table:** a dedicated implementation for storing and looking up entries.
- **Graph:** a graph representation supporting traversal and graph-related operations, including depth-first search (DFS), connected-component counting, and shortest-path calculation using Dijkstra's algorithm.

## Project structure

```text
Data-Structures-Project/
├── AVLTree.h / AVLTree.cpp
├── MinHeap.h / MinHeap.cpp
├── MaxHeap.h / MaxHeap.cpp
├── HashTable.h / HashTable.cpp
├── Graph.h / Graph.cpp
└── main.cpp
```

`main.cpp` connects the individual structures and processes commands from a text file. It also measures execution time for certain operations and writes results to a separate output file.

## Building and running

You will need a C++ compiler, such as `g++`.

1. Clone the repository:

   ```bash
   git clone https://github.com/maaGDaaa/Data-Structures-Project.git
   cd Data-Structures-Project
   ```

2. Compile the source files:

   ```bash
   g++ -std=c++17 main.cpp AVLTree.cpp MinHeap.cpp MaxHeap.cpp HashTable.cpp Graph.cpp -o data_structures
   ```

3. **Prepare a `commands.txt` file in the directory where you will run the program.** The program reads its instructions from this file. A sample command file is not currently included in the repository; see the command handling in `main.cpp` for supported syntax and input-file requirements.

4. Run the program:

   ```bash
   ./data_structures
   ```

   On Windows, run `data_structures.exe` instead. The program writes operation results to `output.txt` in the working directory.

## What I practiced

This project helped me apply C++ programming, object-oriented organization, data structures, graph algorithms, file input/output, and algorithmic problem-solving in an academic setting.

## Notes

This repository documents an educational project, not a production-ready library. The build command above is provided for convenience; it has not been verified as a full automated build or test workflow.
