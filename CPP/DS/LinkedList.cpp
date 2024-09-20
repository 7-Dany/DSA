#include <iostream>

template <typename T>
class Node
{
public:
    T data;
    Node<T> *next;
    Node<T> *prev;

    Node(T element)
    {
        data = element;
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class LinkedList
{
private:
    Node<T> *head;
    Node<T> *tail;

    void remove_helper(Node<T> *node)
    {
        if (node->prev)
        {
            node->prev->next = node->next;
        }
        else
        {
            head = node->next;
        }

        if (node->next)
        {
            node->next->prev = node->prev;
        }
        else
        {
            tail = node->prev;
        }

        delete node;
    }

public:
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const LinkedList<U> &list);

    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    LinkedList(std::initializer_list<T> init_list)
    {
        head = nullptr;
        tail = nullptr;

        for (T element : init_list)
        {
            insert(element);
        }
    }

    void insert(T element)
    {
        if (!head)
        {
            head = new Node<T>(element);
            tail = head;
        }
        else
        {
            Node<T> *temp = new Node<T>(element);
            temp->prev = tail;
            tail->next = temp;
            tail = temp;
        }
    }

    T *pop_head()
    {
        // Return nullptr if the list is empty
        if (!head)
        {
            return nullptr; 
        }

        Node<T> *node = head;
        head = head->next;

        if (head)
        {
            head->prev = nullptr;
        }
        // If the list becomes empty, update tail
        else
        {
            tail = nullptr; 
        }

        // Create a copy of the data
        T *data = new T(node->data); 
        delete node;

        // Return pointer to the data for checking
        return data; 
    }

    T *pop_tail()
    {
        // Return nullptr if the list is empty
        if (!tail)
        {
            return nullptr; 
        }

        Node<T> *temp = tail;
        tail = tail->prev;

        if (tail)
        {
            tail->next = nullptr;
        }
        // If the list becomes empty, update head
        else
        {
            head = nullptr; 
        }

        // Create a copy of the data
        T *data = new T(temp->data); 
        delete temp;

        // Return pointer to the data for checking
        return data; 
    }

    void remove(T element)
    {
        Node<T> *current = head;
        while (current)
        {
            if (current->data == element)
            {
                remove_helper(current);
                return;
            }
            current = current->next;
        }
    }

    bool search(T element)
    {
        Node<T> *current = head;
        while (current)
        {
            if (current->data == element)
            {
                return true;
            }
            current = current->next;
        }

        return false;
    }

    void print() const
    {
        Node<T> *current = head;
        while (current)
        {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    ~LinkedList()
    {
        Node<T> *current = head;
        while (current)
        {
            Node<T> *temp = current->next;
            delete current;
            current = temp;
        }
    }
};

template <typename U>
std::ostream &operator<<(std::ostream &os, const LinkedList<U> &list)
{
    list.print();
    return os;
}