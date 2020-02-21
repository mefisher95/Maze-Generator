#include "Maze.h"

bool Maze::_choose_room()
{
    int x = current_pos_->x();
    int y = current_pos_->y();

    bool zero = 0;
    bool one  = 0;
    bool two = 0;
    bool three = 0;

    while(1)
    {
        int direction = rand() % 4;
        int pos = -1;

        switch (direction)
        {
            case 0: // north direction
            if (y - 1 >= 0 && !maze[((y - 1) * size_ + x)].visited())
            {
                pos = (y - 1) * size_ + x; // North
                maze[pos].S_ = current_pos_;
                current_pos_->N_ = &maze[pos];
            }
            else zero = true;
            break;

            case 1: // south
            if (y + 1 < size_ && !maze[((y + 1) * size_ + x)].visited())
            {
                pos = (y + 1) * size_ + x;
                maze[pos].N_ = current_pos_;
                current_pos_->S_ = &maze[pos];
            }
            else one = true;
            break;

            case 2: // east
            if (x + 1 < size_&& !maze[((y) * size_ + x + 1)].visited())
            {
                pos = (y) * size_ + x + 1;
                maze[pos].W_ = current_pos_;
                current_pos_->E_ = &maze[pos];
            }
            else two = true;
            break;

            case 3: // west
            if (x - 1 >= 0 && !maze[((y) * size_ + x - 1)].visited())
            {
                pos = (y) * size_ + x - 1;
                maze[pos].E_ = current_pos_;
                current_pos_->W_ = &maze[pos];
            }
            else three = true;
            break;
        }

        if (zero && one && two && three) return false;

        if (maze[pos].visited()) continue;
        else
        {
            maze[pos].prev_ = current_pos_;
            current_pos_ = &maze[pos];
            current_pos_->visited() = true;
            ++check_num_;
            return true;                
        }
    }
    
}

void Maze::_build_maze()
{
    bool blocked = 0;

    while(1)
    {
        if(!_choose_room()) current_pos_ = current_pos_->prev_;
        if (check_num_ == maze.size()) return;
    }
}

void Maze::_print()
{
    for (int y = 0; y < size(); ++y)
    {
        ///////////////////////////
        if (!y)
        {
            for (int i = 0; i < size(); ++i)
            {
                std::cout << "+-";
            }
            std::cout << "+\n";
        }
        /////////////////////////////////////////

        for (int x = 0; x < size(); ++x)
        {
            int pos = y * size() + x;
            if (!x) std::cout << '|';
            if (maze[pos].E_ == NULL)
            {
                std::cout << " |";
            }
            else if (x == size() - 1) std::cout << " |";
            else std::cout << "  ";
        }
        std::cout << std::endl;
        /////////////////////////////////

        for (int x = 0; x < size(); ++x)
        {
            int pos = y * size() + x;
            if (maze[pos].S_ == NULL) std::cout << "+-";
            else std::cout << "+ ";
        }
        std::cout << '+' << std::endl;
    }
}

void Maze::_print_path()
{
    Cell *p = current_pos_;
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
}

void Maze::init_maze(int size = 0, int y_ = 0, int x_ = 0)
{
    if (!size_) size_ = size;
    
    for (int y = 0; y < size_; ++y)
    {
        for ( int x = 0; x < size_; ++x)
        {
            Cell cell(x, y);

            maze.push_back(cell);
        }
    }

    int starting_pos = y_ * maze.size() + x_;
    current_pos_ = &maze[starting_pos];
    current_pos_->visited() = true;

    _build_maze();
    _print();
}

std::ostream &operator<<(std::ostream &cout, const Cell &cell)
{
    cout << "<Cell(" << cell.x() << ", " << cell.y()
         << ") prev: "<< std::setw(8) << cell.prev_ 
         << " current: "<< std::setw(8) << &cell
         << " next_N: " << std::setw(8) << cell.N_
         << " next_S: " << std::setw(8) << cell.S_
         << " next_E: " << std::setw(8) << cell.E_
         << " next_W: " << std::setw(8) << cell.W_
         << '>';
    return cout;
}

std::ostream &operator<<(std::ostream &cout, const std::vector < Cell > &maze)
{
    for (int i = 0; i < maze.size(); ++i)
    {
        cout << maze[i] << std::endl;
    }
    return cout;
}

