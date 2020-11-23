
# Super Graph Coloring

**How to Run:**

The main program expects input from stdin

```sh
cat inputs/graph-1000-100000.txt | python3 src/main.py  
```

### **Random Graphs**

Nodes: 50, Edges: 500, New Colors: 10, Max Degree: 27

Nodes: 100, Edges: 500, New Colors: 6, Max Degree: 22

Nodes: 500, Edges: 1000, New Colors: 5, Max Degree: 5

Nodes: 1000, Edges: 50,000, New Colors: 29, Max Degree: 129

### **Sudoku**

Output from `sudoku.txt`

```
3
5 7 1 2 6 3 10 8 4 4 2 3 1 8 7 9 5 6 9 8 6 4 5 10 3 2 1 1 6 7 3 4 8 2
9 10 3 4 8 9 2 1 7 6 5 2 5 9 6 7 11 1 3 8 8 9 4 7 3 2 6 1 12 6 1 2 10 
9 5 8 4 3 7 3 10 8 1 4 5 11 2
```

3 new colors were added with the corresponding colors for each node underneath.