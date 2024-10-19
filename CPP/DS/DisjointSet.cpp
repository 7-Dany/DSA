#include <iostream>
#include <map>

template <typename T>
class DSet
{
private:
    std::map<T, T> parent_;
    std::map<T, int> rank_;

public:
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const DSet<U> &set);

    DSet() : parent_(), rank_() {};

    DSet(std::initializer_list<T> init_list) : parent_(), rank_()
    {
        for (const T &element : init_list)
        {
            create(element);
        }
    }

    void create(const T &x)
    {
        parent_[x] = x;
        rank_[x] = 0;
    }

    T find(const T &element)
    {
        if (parent_[element] != element)
        {
            parent_[element] = find(parent_[element]);
        }

        return parent_[element];
    }

    void unite(const T &x, const T &y)
    {
        T root_x = find(x);
        T root_y = find(y);

        if (root_x != root_y)
        {
            if (rank_[root_x] < rank_[root_y])
            {
                std::swap(root_x, root_y);
            }

            parent_[root_y] = root_x;

            if (rank_[root_x] == rank_[root_y])
            {
                rank_[root_x]++;
            }
        }
    }

    bool connected(const T &x, const T &y)
    {
        return find(x) == find(y);
    }

    void print() const
    {
        std::cout << "Parent: " << std::endl;
        std::cout << "{";
        bool first = true;
        for (const auto &[key, value] : parent_)
        {
            if (!first)
                std::cout << ", ";
            std::cout << key << ": " << value;
            first = false;
        }
        std::cout << "}" << std::endl;

        std::cout << "Rank: " << std::endl;
        std::cout << "{";
        first = true;
        for (const auto &[key, value] : rank_)
        {
            if (!first)
                std::cout << ", ";
            std::cout << key << ": " << value;
            first = false;
        }
        std::cout << "}" << std::endl;
    }
};

template <typename U>
std::ostream &operator<<(std::ostream &os, const DSet<U> &set)
{
    set.print();
    return os;
}
