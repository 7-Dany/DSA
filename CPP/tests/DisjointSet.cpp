#include <iostream>
#include <cassert>               // For assert
#include "../../DisjointSet.cpp" // Assuming DSet is in this file

void test_create_and_find()
{
    DSet<int> dset;
    dset.create(1);
    dset.create(2);

    assert(dset.find(1) == 1);
    assert(dset.find(2) == 2);

    std::cout << "test_create_and_find passed!" << std::endl;
}

void test_initializer_list()
{
    DSet<int> dset({1, 2, 3});

    assert(dset.find(1) == 1);
    assert(dset.find(2) == 2);
    assert(dset.find(3) == 3);

    std::cout << "test_initializer_list passed!" << std::endl;
}

void test_unite()
{
    DSet<int> dset({1, 2, 3, 4});

    dset.unite(1, 2);
    assert(dset.find(1) == dset.find(2));

    dset.unite(3, 4);
    assert(dset.find(3) == dset.find(4));

    dset.unite(2, 3);
    assert(dset.find(1) == dset.find(4)); // All should be connected now

    std::cout << "test_unite passed!" << std::endl;
}

void test_connected()
{
    DSet<int> dset({1, 2, 3, 4});

    dset.unite(1, 2);
    assert(dset.connected(1, 2) == true);
    assert(dset.connected(1, 3) == false);

    dset.unite(2, 3);
    assert(dset.connected(1, 3) == true);

    std::cout << "test_connected passed!" << std::endl;
}

void test_rank_compression()
{
    DSet<int> dset({1, 2, 3, 4});

    dset.unite(1, 2);
    dset.unite(3, 4);
    dset.unite(1, 3); // unite sets with equal rank, 1 becomes root

    assert(dset.find(1) == dset.find(4)); // All should be connected
    assert(dset.find(2) == dset.find(3));

    std::cout << "test_rank_compression passed!" << std::endl;
}

int main()
{
    test_create_and_find();
    test_initializer_list();
    test_unite();
    test_connected();
    test_rank_compression();

    std::cout << "All Tests Passed" << std::endl;
    return 0;
}