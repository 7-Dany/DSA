#include <iostream>
#include "Array.cpp"

template <typename T>
class Stack
{
private:
    Array<T> array;

public:
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Stack<U> &stack);

    Stack() : array()
    {
    }

    Stack(std::initializer_list<T> init_list) : array(init_list)
    {
    }

    void push(T element)
    {
        array.push(element);
    }

    T *pop()
    {
        return array.pop();
    }

    void print() const
    {
        array.print();
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Stack<T> &stack)
{
    stack.print();
    return os;
}
