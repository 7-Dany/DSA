#include <iostream>
#include "LinkedList.cpp"

template <typename T>
class Queue
{
private:
    LinkedList<T> list;

public:
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Queue<U> &queue);

    Queue() : list()
    {
    }

    Queue(std::initializer_list<T> init_list) : list(init_list)
    {
    }

    void enqueue(T element)
    {
        list.insert(element);
    }

    T *dequeue()
    {
        T *element = list.pop_head();
        return element;
    }

    void print() const
    {
        list.print();
    }
};

template <typename U>
std::ostream &operator<<(std::ostream &os, const Queue<U> &queue)
{
    queue.print();
    return os;
}