#include <iostream>
#include <cstdio>

template<typename T>
struct Node {
    Node<T> *left;
    Node<T> *right;
    T data;
    int height;

    Node(Node<T> *l, Node<T> *r, T item)
    : left(l), right(r), data(item)
    {
    }
};

template<typename T>
class AVL {
public:
    Node<T> *root = NULL;

    AVL()
    {
    }

    AVL(std::initializer_list<T> array) 
    {
        for (T item : array) {
            insert(item);
        }        
    }
    
//private:
    int get_height(Node<T> *root)
    {
        return root ? root->height: 0;
    }

    int get_balance_factor(Node<T> *root)
    {
        return root ? (get_height(root->left) - get_height(root->right)) : 0;
    }

    #define max(i, j) ((i) > (j) ? (i) : (j))
    #define min(i, j) ((i) < (j) ? (i) : (j))

    Node<T>* rotate_right(Node<T> *root)
    {
        // Left child
        Node<T> *left_child = root->left;
        Node<T> *right_left_child = left_child->right;

        root->left = right_left_child;
        left_child->right = root;
        
        root->height = 1 + max(get_height(root->left), get_height(root->right));
        left_child->height = 1 + max(get_height(left_child->left), get_height(left_child->right));

        return left_child;
    }

    Node<T>* rotate_left(Node<T> *root)
    {

    }
    
    #undef max
    #undef min
    
    void insert(T item)
    {
        
    }
};

int main(void)
{
    Node<int> *third = new Node<int>(NULL, NULL, 20);
    Node<int> *second = new Node<int>(NULL, third, 10);
    second->height = -1;
    Node<int> *first = new Node<int>(NULL, second, 0);
    first->height = -2;

    AVL<int> avl;

    Node<int> *root = avl.rotate_right(first);
    // Dude im still here 😁
    std::cout << root->data << " " << root->left->data << " " << root->right->data << std::endl;
    printf("hi\n");

    // tried microsoft compiler and it still doesn't work
    // I don't know what the fuck is wrong with this piece of molested shit
    // Fuck Bjarne stroustrup
    
    return 0;
}