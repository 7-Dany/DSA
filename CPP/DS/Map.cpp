#include <iostream>
#include "Array.cpp"

template <typename T>
class Map
{

public:
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Map<U> &map);

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