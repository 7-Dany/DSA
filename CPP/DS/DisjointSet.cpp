#include <iostream>
#include <map>

template <typename T>
class DSet
{
private:
    std::map<T, T> parent_{std::map<T, T>()};
    std::map<T, int> rank_{std::map<T, int>()};

public:
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const DSet<U> &set);

    DSet() = default;

    DSet(std::initializer_list<T> init_list)
    {
        for (T element : init_list)
        {
            create(element);
        }
    }

    void create(T &x)
    {
        parent_[x] = x;
        rank_[x] = 0;
    }

    T find(T &element)
    {
        if (parent[element] != element)
        {
            parent_[element] = find(element);
        }

        return parent_[element];
    }

    void unite(T &x, T &y)
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

    bool connected(T &x, T &y)
    {
        return find(x) == find(y);
    }

    void print() const
    {
        std::cout << "Parent: " << std::endl;
        std::cout << "{";
        for (const auto &[key, value] : parent_)
        {
            std::cout << key << ": " << value << ", ";
        }
        std::cout << "\b\b}";
        std::cout << std::endl;
        std::cout << "Rank: " << std::endl;
        std::cout << "{";
        for (const auto &[key, value] : rank_)
        {
            std::cout << key << ": " << value << ", ";
        }
        std::cout << "\b\b}";
        std::cout << std::endl;
    }
};

template <typename U>
std::ostream &operator<<(std::ostream &os, const DSet<U> &set)
{
    set.print();
    return os;
}

int main()
{
    DSet<int> set = {1, 2, 3, 4, 5};
    std::cout << set;
    return 0;
}