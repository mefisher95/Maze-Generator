#include "Maze.h"



int main()
{
    int n, r, c;
    std::cin >> n >> r >> c;

    Maze maze(n);
    
    maze.init_maze(n, r, c);  
}

