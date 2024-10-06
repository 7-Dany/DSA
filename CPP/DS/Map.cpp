#include <iostream>
#include "AVL.cpp"

template <typename T>
class Map
{

private:
    AVL<T> tree;

public:
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Map<U> &map);

    Map() : tree()
    {
    }

    void print() const
    {
    }
};

template <typename U>
std::ostream &operator<<(std::ostream &os, const Map<U> &map)
{
    map.print();
    return os;
}