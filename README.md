
# Maze solver

C application that visually generates a maze (as a waged graph) and uses Dijkstra's algorithm to find and display the shortest path.

Full documentation in polish available under doc.pdf
## Installation & run

Compile my project with gcc

```bash
  # regular install
  $ gcc main.c maze.c matrix.c dijkstra.c <-o filename>
  # install with debugging prompts
  $ gcc main.c maze.c matrix.c dijkstra.c -DDEBUG <-o filename> 
```

To run, simply execute program giving the size of the wall, e.g. 
```bash
  $ ./maze 5
```
    