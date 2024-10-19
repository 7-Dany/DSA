#include <iostream>
#include <optional>

template <typename T>
class Node
{
public:
    T data_;
    Node<T> *next_{nullptr};
    Node<T> *prev_{nullptr};

    Node(T data) : data_(data)
    {
    }
};

template <typename T>
class LinkedList
{
private:
    void delete_helper()
    {
        Node<T> *current = head_;
        while (current)
        {
            Node<T> *temp = current->next_;
            delete current;
            current = temp;
        }
    }

public:
    Node<T> *head_{nullptr};
    Node<T> *tail_{nullptr};

    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const LinkedList<U> &list);

    LinkedList()
    {
    }

    LinkedList(std::initializer_list<T> init_list)
    {
        for (T element : init_list)
        {
            insert(element);
        }
    }

    LinkedList(LinkedList<T> &list)
    {
        if (this != &list)
        {
            Node<T> *current = list.head_;
            while (current)
            {
                insert(current->data_);
                current = current->next_;
            }
        }
    }

    LinkedList(LinkedList<T> &&list)
    {
        if (this != &list)
        {
            head_ = list.head_;
            tail_ = list.tail_;

            list.head_ = nullptr;
            list.tail_ = nullptr;
        }
    }

    LinkedList &operator=(LinkedList<T> &list)
    {
        if (this != &list)
        {
            Node<T> *current = list.head_;
            while (current)
            {
                insert(current->data_);
                current = current->next_;
            }
        }

        return *this;
    }

    LinkedList &operator=(LinkedList<T> &&list)
    {
        if (this != &list)
        {
            delete_helper();

            head_ = list.head_;
            tail_ = list.tail_;

            list.head_ = nullptr;
            list.tail_ = nullptr;
        }

        return *this;
    }

    void print() const
    {
        Node<T> *current = head_;

        while (current)
        {
            std::cout << current->data_ << " ";
            current = current->next_;
        }

        std::cout << std::endl;
    }

    void insert(T element)
    {
        if (!head_)
        {
            Node<T> *node = new Node<T>(element);
            head_ = node;
            tail_ = node;
            return;
        }

        Node<T> *node = new Node<T>(element);
        node->prev_ = tail_;
        tail_->next_ = node;
        tail_ = tail_->next_;
    }

    std::optional<T> pop_head()
    {
        if (!head_)
        {
            return std::nullopt;
        }

        T element = head_->data_;
        Node<T> *node = head_;
        head_ = node->next_;

        delete node;

        if (!head_)
        {
            tail_ = nullptr;
        }

        return element;
    }

    std::optional<T> pop_tail()
    {
        if (!tail_)
        {
            return std::nullopt;
        }

        T element = tail_->data_;
        Node<T> *node = tail_;
        tail_ = tail_->prev_;

        delete node;

        if (!tail_)
        {
            head_ = nullptr;
        }
        else
        {
            tail_->next_ = nullptr;
        }

        return element;
    }

    bool search(T element)
    {
        Node<T> *current = head_;
        while (current)
        {
            if (current->data_ == element)
            {
                return true;
            }

            current = current->next_;
        }

        return false;
    }

    ~LinkedList()
    {
        delete_helper();
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const LinkedList<T> &list)
{
    list.print();
    return os;
}