#include <iostream>

template <typename T>
class Node
{
public:
    T data;
    Node<T> *left;
    Node<T> *right;

    Node(T element)
    {
        data = element;
        left = nullptr;
        right = nullptr;
    }
};

template <typename T>
class BST
{
private:
    Node<T> *root;

    void pre_order(Node<T> *root) const
    {
        if (!root)
            return;
        std::cout << root->data << " ";
        in_order_helper(root->left);
        in_order_helper(root->right);
    }

    void in_order(Node<T> *root) const
    {
        if (!root)
            return;
        in_order_helper(root->left);
        std::cout << root->data << " ";
        in_order_helper(root->right);
    }

    void post_order(Node<T> *root) const
    {
        if (!root)
            return;
        in_order_helper(root->left);
        in_order_helper(root->right);
        std::cout << root->data << " ";
    }

    T successor(Node<T> *root)
    {
        Node<T> *node = root->right;
        while (node && node->left)
        {
            node = node->left;
        }
        return node->data;
    }

    T predecessor(Node<T> *root)
    {
        Node<T> *node = root->left;
        while (node && node->right)
        {
            node = node->right;
        }
        return node->data;
    }

    Node<T> *insert_helper(Node<T> *root, T data)
    {
        if (!root)
        {
            return new Node<T>(data);
        }

        if (data > root->data)
        {
            root->right = insert_helper(root->right, data);
        }
        else if (data < root->data)
        {
            root->left = insert_helper(root->left, data);
        }
        else
        {
            return root;
        }
    }

    Node<T> *remove_helper(Node<T> *root, T data)
    {
        if (!root)
        {
            return root;
        }
        else if (data > root->data)
        {
            root->right = remove_helper(root->right, data);
        }
        else if (data < root->data)
        {
            root->left = remove_helper(root->left, data);
        }
        else
        {
            //* Node is leaf
            if (!root->right && !root->left)
            {
                delete root;
                return nullptr;
            }
            //* Node doesnt have left.
            else if (!root->left)
            {
                Node<T> *temp = root->right;
                delete root;
                return temp;
            }
            //* Node doesnt have right.
            else if (!root->right)
            {
                Node<T> *temp = root->left;
                delete root;
                return temp;
            }
            //* Node have both right and left.
            else
            {
                root->data = successor(root);
                root->right = remove_helper(root->right, root->data);
            }
        }

        return root;
    }

    void destroy_helper(Node<T> *root)
    {
        if (!root)
            return;

        destroy_helper(root->left);
        destroy_helper(root->right);

        delete root;
    }

public:
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const AVL<U> &tree);

    BST()
    {
        root = nullptr;
    }

    BST(std::initializer_list<T> init_list)
    {
        root = nullptr;
        for (T element : init_list)
        {
            insert(element);
        }
    }

    void insert(T element)
    {
        root = insert_helper(root, element);
    }

    void remove(T element)
    {
        root = remove_helper(root, element);
    }

    void print() const
    {
        in_order(root);
        std::cout << std::endl;
    }

    ~AVL()
    {
        destroy_helper(root);
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const BST<T> &tree)
{
    tree.print();
    return os;
}