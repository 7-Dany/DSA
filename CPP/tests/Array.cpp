#include <iostream>
#include <cassert>
#include <string>
#include "../DS/Array.cpp"

void test_default_constructor() {
    Array<int> arr;
    assert(arr.size() == 0);
    assert(arr.capacity_ == 8);
    std::cout << "Default constructor test passed.\n";
}

void test_initializer_list_constructor() {
    Array<int> arr = {1, 2, 3, 4, 5};
    assert(arr.size() == 5);
    assert(arr.capacity_ == 10);
    for (int i = 0; i < 5; ++i) {
        assert(arr[i] == i + 1);
    }
    std::cout << "Initializer list constructor test passed.\n";
}

void test_copy_constructor() {
    Array<int> arr1 = {1, 2, 3, 4, 5};
    Array<int> arr2(arr1);
    assert(arr2.size() == arr1.size());
    assert(arr2.capacity_ == arr1.capacity_);
    for (int i = 0; i < arr1.size(); ++i) {
        assert(arr2[i] == arr1[i]);
    }
    std::cout << "Copy constructor test passed.\n";
}

void test_move_constructor() {
    Array<int> arr1 = {1, 2, 3, 4, 5};
    Array<int> arr2(std::move(arr1));
    assert(arr2.size() == 5);
    assert(arr1.size() == 0);
    assert(arr1.array_ == nullptr);
    std::cout << "Move constructor test passed.\n";
}

void test_copy_assignment() {
    Array<int> arr1 = {1, 2, 3, 4, 5};
    Array<int> arr2;
    arr2 = arr1;
    assert(arr2.size() == arr1.size());
    for (int i = 0; i < arr1.size(); ++i) {
        assert(arr2[i] == arr1[i]);
    }
    std::cout << "Copy assignment test passed.\n";
}

void test_move_assignment() {
    Array<int> arr1 = {1, 2, 3, 4, 5};
    Array<int> arr2;
    arr2 = std::move(arr1);
    assert(arr2.size() == 5);
    assert(arr1.size() == 0);
    assert(arr1.array_ == nullptr);
    std::cout << "Move assignment test passed.\n";
}

void test_indexing_operator() {
    Array<int> arr = {1, 2, 3, 4, 5};
    assert(arr[0] == 1);
    assert(arr[4] == 5);
    arr[2] = 10;
    assert(arr[2] == 10);
    std::cout << "Indexing operator test passed.\n";
}

void test_size() {
    Array<int> arr = {1, 2, 3, 4, 5};
    assert(arr.size() == 5);
    std::cout << "Size method test passed.\n";
}

void test_swap() {
    Array<int> arr = {1, 2, 3, 4, 5};
    arr.swap(1, 3);
    assert(arr[1] == 4);
    assert(arr[3] == 2);
    std::cout << "Swap method test passed.\n";
}

void test_push() {
    Array<int> arr;
    for (int i = 0; i < 10; ++i) {
        arr.push(i);
    }
    assert(arr.size() == 10);
    assert(arr.capacity_ == 16);
    for (int i = 0; i < 10; ++i) {
        assert(arr[i] == i);
    }
    std::cout << "Push method test passed.\n";
}

void test_pop() {
    Array<int> arr = {1, 2, 3, 4, 5};
    std::optional<int> popped = arr.pop();
    assert(popped == 5);
    assert(arr.size() == 4);
    std::cout << "Pop method test passed.\n";
}

void test_resize() {
    Array<int> arr;
    for (int i = 0; i < 20; ++i) {
        arr.push(i);
    }
    assert(arr.capacity_ == 32);
    for (int i = 0; i < 15; ++i) {
        arr.pop();
    }
    assert(arr.capacity_ == 16);
    std::cout << "Resize method test passed.\n";
}

int main() {
    test_default_constructor();
    test_initializer_list_constructor();
    test_copy_constructor();
    test_move_constructor();
    test_copy_assignment();
    test_move_assignment();
    test_indexing_operator();
    test_size();
    test_swap();
    test_push();
    test_pop();
    test_resize();

    std::cout << "All tests passed successfully!\n";
    return 0;
}