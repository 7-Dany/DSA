#include <iostream>

#define NUM_CHARS 256

class Node
{
public:
    Node *children_[NUM_CHARS];
    bool terminate_{false};

    Node()
    {
        for (int i = 0; i < NUM_CHARS; i++)
        {
            children_[i] = nullptr;
        }
    }

    Node *&operator[](int index)
    {
        return children_[index];
    }
};

class Trie
{
public:
    Node *root_;
    Trie() : root_(new Node())
    {
    }

    bool insert(std::string key)
    {
        Node *current = root_;

        for (int index : key)
        {
            if (!(*current)[index])
            {
                (*current)[index] = new Node();
            }

            current = (*current)[index];
        }

        bool is_word_saved = current->terminate_;

        if (!is_word_saved)
        {
            current->terminate_ = true;
            return true;
        }

        return false;
    }

    bool search(std::string key, bool prefix = false)
    {
        Node *current = root_;

        for (int index : key)
        {
            if (!(*current)[index])
            {
                return false;
            }
            current = (*current)[index];
        }

        if (!current)
            return false;

        if (!prefix)
        {
            return current->terminate_;
        }

        return true;
    }

    bool prefix(std::string key)
    {
        return search(key, true);
    }
};