#include <iostream>
#include <optional>

template <typename T>
class Array
{
private:
    void resize(int new_capacity)
    {
        capacity_ = new_capacity;
        T *new_array = new T[capacity_];

        for (int i = 0; i < length_; i++)
        {
            new_array[i] = array_[i];
        }

        delete[] array_;
        array_ = new_array;
    }

public:
    T *array_;
    int capacity_{8};
    int length_{0};

    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Array<U> &arr);

    Array()
    {
        array_ = new T[capacity_];
    }

    Array(std::initializer_list<T> init_list)
    {
        length_ = init_list.size();
        capacity_ = length_ * 2;
        array_ = new T[capacity_];

        int i = 0;
        for (T element : init_list)
        {
            array_[i] = element;
            i++;
        }
    }

    Array(const Array &array) : length_(array.length_), capacity_(array.capacity_)
    {
        array_ = new T[capacity_];
        for (int i = 0; i < length_; i++)
        {
            array_[i] = array[i];
        }
    }

    Array &operator=(const Array &array)
    {
        if (this != &array)
        {
            length_ = array.length_;
            capacity_ = array.capacity_;

            delete[] array_;
            array_ = new T[capacity_];

            for (int i = 0; i < length_; i++)
            {
                array_[i] = array.array_[i];
            }
        }

        return *this;
    }

    Array(Array &&array) noexcept
    {
        array_ = array.array_;
        length_ = array.length_;
        capacity_ = array.capacity_;

        array.array_ = nullptr;
        array.length_ = 0;
        array.capacity_ = 0;
    }

    Array &operator=(Array &&array)
    {
        if (this != &array)
        {
            delete[] array_;

            array_ = array.array_;
            length_ = array.length_;
            capacity_ = array.capacity_;

            array.array_ = nullptr;
            array.length_ = 0;
            array.capacity_ = 0;
        }

        return *this;
    }

    T &operator[](int index)
    {
        return array_[index];
    }

    const T &operator[](int index) const
    {
        return array_[index];
    }

    int size()
    {
        return length_;
    }

    void swap(int x, int y)
    {
        if (x >= 0 && x < length_ && y >= 0 && y < length_)
        {
            T temp = array_[x];
            array_[x] = array_[y];
            array_[y] = temp;
        }
    }

    void print() const
    {
        for (int i = 0; i < length_; i++)
        {
            std::cout << array_[i] << " ";
        }
        std::cout << std::endl;
    }

    void push(T element)
    {
        if (length_ == capacity_)
        {
            resize(capacity_ * 2);
        }

        array_[length_] = element;
        length_++;
    }

    std::optional<T> pop()
    {
        if (length_ == 0)
        {
            return std::nullopt;
        }

        length_--;
        T element = array_[length_];

        if (length_ <= capacity_ / 4)
        {
            resize(capacity_ / 2);
        }

        return element;
    }

    ~Array()
    {
        delete[] array_;
    }
};

template <typename U>
std::ostream &operator<<(std::ostream &os, const Array<U> &arr)
{
    arr.print();
    return os;
}