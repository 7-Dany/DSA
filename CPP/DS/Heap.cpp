#include <iostream>
#include "Array.cpp"

enum Type
{
    MIN = 0,
    MAX = 1
};

template <typename T>
class Heap
{
private:
    Array<T> array;
    Type type;

    int get_parent(int index)
    {
        return (index - 1) / 2;
    }

    int get_min(int parent)
    {
        int min = parent;
        int left = parent * 2 + 1;
        int right = parent * 2 + 2;

        if (left < array.size() && array[left] < array[min])
        {
            min = left;
        }

        if (right < array.size() && array[right] < array[min])
        {
            min = right;
        }

        return min;
    }

    int get_max(int parent)
    {
        int max = parent;
        int left = parent * 2 + 1;
        int right = parent * 2 + 2;

        if (left < array.size() && array[left] > array[max])
        {
            max = left;
        }

        if (right < array.size() && array[right] > array[max])
        {
            max = right;
        }

        return max;
    }

    void heapify(int index)
    {
        int parent = index;
        while (parent < array.size())
        {
            int child;
            switch (type)
            {
            case MIN:
                child = get_min(parent);
                break;
            case MAX:
                child = get_max(parent);
                break;
            }

            if (child == parent)
                return;

            array.swap(parent, child);
            parent = child;
        }
    }

    void build()
    {
        int middle = (array.size() - 1) / 2;
        for (int i = middle; i >= 0; i--)
        {
            heapify(i);
        }
    }

public:
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Heap<U> &heap);

    Heap(Type heap_type = MIN) : array(), type(heap_type)
    {
    }

    Heap(std::initializer_list<T> init_list, Type heap_type = MIN) : array(init_list), type(heap_type)
    {
        build();
    }

    void switch_type(Type heap_type)
    {
        if (heap_type != type)
        {
            type = heap_type;
            build();
        }
    }

    void insert(T element)
    {
        array.push(element);

        int child = array.size() - 1;
        while (child >= 0)
        {
            int parent = get_parent(child);
            bool swap;

            switch (type)
            {
            case MIN:
                swap = parent >= 0 && array[child] < array[parent];
                break;

            case MAX:
                swap = parent >= 0 && array[child] > array[parent];
                break;
            }

            if (!swap)
                return;

            array.swap(child, parent);
            child = parent;
        }
    }

    T *pop()
    {
        if (array.size() == 0)
        {
            return nullptr;
        }

        array.swap(0, array.size() - 1);
        T *element = array.pop();

        heapify(0);

        return element;
    }

    void print() const
    {
        array.print();
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Heap<T> &heap)
{
    heap.print();
    return os;
}