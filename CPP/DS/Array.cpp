#include <iostream>

template <typename T>
class Array
{
private:
    T *array;
    int capacity;
    int length;

    void resize(int new_capacity)
    {
        capacity = new_capacity;
        T *new_array = new T[capacity];

        for (int i = 0; i < length; i++)
        {
            new_array[i] = array[i];
        }

        delete[] array;

        array = new_array;
    }

public:
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Array<T> &arr);

    Array()
    {
        capacity = 8;
        length = 0;
        array = new T[capacity];
    }

    Array(std::initializer_list<T> init_list)
    {
        length = init_list.size();
        capacity = length * 2;
        array = new T[capacity];

        int i = 0;
        for (T element : init_list)
        {
            array[i] = element;
            i++;
        }
    }

    T &operator[](int index)
    {
        if (index >= 0 && index < length)
        {
            return array[index];
        }

        throw std::out_of_range("Index is out of bound.");
    }

    void print() const
    {
        for (int i = 0; i < length; i++)
        {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }

    int size()
    {
        return length;
    }

    void swap(int x, int y)
    {
        if (x >= 0 && x < length && y >= 0 && y < length && x != y)
        {
            T temp = array[x];
            array[x] = array[y];
            array[y] = temp;
        }
    }

    void push(T element)
    {
        if (length == capacity)
        {
            resize(capacity * 2);
        }

        array[length] = element;
        length++;
    }

    T *pop()
    {
        if (length == 0)
        {
            return nullptr;
        }

        length--;
        T *element = &array[length];

        if (length <= capacity / 4)
        {
            resize(capacity / 2);
        }

        return element;
    }

    ~Array()
    {
        if (array)
        {
            delete[] array;
        }
    }
};

template <typename U>
std::ostream &operator<<(std::ostream &os, const Array<U> &arr)
{
    arr.print();
    return os;
}