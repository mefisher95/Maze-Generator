#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cmath>

class Cell
{
    public:
    Cell()
    :x_(0), y_(0)
    {}
    Cell(int x, int y, Cell *prev=NULL, Cell *N=NULL, Cell *S=NULL,
    Cell *E=NULL, Cell *W=NULL, bool visited=false)
    :x_(x), y_(y), prev_(prev), visited_(visited),
    N_(N), S_(S), E_(E), W_(W)
    {}

    // positional methods
    int x() const { return x_; }
    int &x() { return x_; }

    int y() const { return y_; }
    int &y() { return y_; }

    bool visited() const { return visited_; }
    bool &visited() { return visited_; }
    
    Cell *prev_;
    Cell *N_;
    Cell *S_;
    Cell *E_;
    Cell *W_;
    

    private:
    int x_;
    int y_;
    bool visited_;
};

std::ostream &operator<<(std::ostream &cout, const Cell &cell);


class Maze
{
    public:
    Maze(int size=0)
    :size_(size), check_num_(1)
    {
        srand((unsigned int) time(NULL));
    }

    int size () const { return size_; }
    int &size () { return size_; }

    void init_maze(int size, int y_, int x_);
    
   

    std::vector < Cell > maze;

    private:

    bool _choose_room();
    void _build_maze();
    void _print_path();
    void _print();

    int size_;
    Cell *current_pos_;
    int check_num_;
    
};

std::ostream &operator<<(std::ostream &cout, const std::vector < Cell > &maze);

/*
void print_Llist(const Maze &maze)
{
    Cell *p = maze.current_pos_;
    while (1)
    {
        std::cout << *p << std::endl;
        p = p->prev_;
        if (p->prev_ == NULL)
        {
            std::cout << *p << std::endl;
            break;
        }
    }
    std::cout << std::endl;
}*/


#endif