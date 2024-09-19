#include <iostream>

template <typename T>
class Node
{
public:
    T data;
    int height;
    Node<T> *left;
    Node<T> *right;

    Node(T element)
    {
        data = element;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

template <typename T>
class AVL
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

    int get_height(Node<T> *root)
    {
        return root ? root->height : 0;
    }

    int get_balance_factor(Node<T> *root)
    {
        return root ? (get_height(root->left) - get_height(root->right)) : 0;
    }

    Node<T> *rotate_right(Node<T> *root)
    {
        Node<T> *left_node = root->left;
        Node<T> *right_left_node = left_node->right;

        root->left = right_left_node;
        left_node->right = root;

        root->height = 1 + std::max(get_height(root->left), get_height(root->right));
        left_node->height = 1 + std::max(get_height(left_node->left), get_height(left_node->right));

        return left_node;
    }

    Node<T> *rotate_left(Node<T> *root)
    {
        Node<T> *right_node = root->right;
        Node<T> *left_right_node = right_node->left;

        root->right = left_right_node;
        right_node->left = root;

        root->height = 1 + std::max(get_height(root->left), get_height(root->right));
        right_node->height = 1 + std::max(get_height(right_node->left), get_height(right_node->right));

        return right_node;
    }

    Node<T> *balance(Node<T> *root)
    {
        root->height = 1 + std::max(get_height(root->left), get_height(root->right));

        int factor = get_balance_factor(root);

        //* Left Node Left Node Case
        if (factor < -1 && get_balance_factor(root->right) < 0)
        {
            return rotate_left(root);
        }

        //* Left Node Right Node Case
        if (factor < -1 && get_balance_factor(root->right) > 0)
        {
            root->right = rotate_right(root->right);
            return rotate_left(root);
        }

        //* Right Node Right Node Case
        if (factor > 1 && get_balance_factor(root->left) > 0)
        {
            return rotate_right(root);
        }

        //* Right Node Left Node Case
        if (factor > 1 && get_balance_factor(root->left) < 0)
        {
            root->left = rotate_left(root->left);
            return rotate_right(root);
        }

        return root;
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

        return balance(root);
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

        return balance(root);
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

    AVL()
    {
        root = nullptr;
    }

    AVL(std::initializer_list<T> init_list)
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
std::ostream &operator<<(std::ostream &os, const AVL<T> &tree)
{
    tree.print();
    return os;
}

int main()
{
    AVL<int> tree = {5, 9, 7, 2, 0};
    std::cout << tree;
    tree.insert(4);
    tree.insert(3);
    std::cout << tree;
    tree.remove(2);
    std::cout << tree;
    return 0;
}