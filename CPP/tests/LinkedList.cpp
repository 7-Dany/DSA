#include <cassert>
#include <iostream>
#include <vector>
#include <optional>
#include "../DS/LinkedList.cpp"

#define RUN_TEST(test) \
    do { \
        std::cout << #test << "... "; \
        test(); \
        std::cout << "PASSED" << std::endl; \
    } while (0)

void test_default_constructor() {
    LinkedList<int> list;
    assert(list.head_ == nullptr);
    assert(list.tail_ == nullptr);
}

void test_initializer_list_constructor() {
    LinkedList<int> list = {1, 2, 3};
    assert(list.head_->data_ == 1);
    assert(list.tail_->data_ == 3);
    assert(list.head_->next_->data_ == 2);
}

void test_copy_constructor() {
    LinkedList<int> list1 = {1, 2, 3};
    LinkedList<int> list2(list1);
    assert(list2.head_->data_ == 1);
    assert(list2.tail_->data_ == 3);
    assert(list2.head_ != list1.head_); // Ensure deep copy
}

void test_move_constructor() {
    LinkedList<int> list1 = {1, 2, 3};
    LinkedList<int> list2(std::move(list1));
    assert(list2.head_->data_ == 1);
    assert(list2.tail_->data_ == 3);
    assert(list1.head_ == nullptr); // list1 should be empty after move
}

void test_copy_assignment() {
    LinkedList<int> list1 = {1, 2, 3};
    LinkedList<int> list2;
    list2 = list1;
    assert(list2.head_->data_ == 1);
    assert(list2.tail_->data_ == 3);
    assert(list2.head_ != list1.head_); // Ensure deep copy
}

void test_move_assignment() {
    LinkedList<int> list1 = {1, 2, 3};
    LinkedList<int> list2;
    list2 = std::move(list1);
    assert(list2.head_->data_ == 1);
    assert(list2.tail_->data_ == 3);
    assert(list1.head_ == nullptr); // list1 should be empty after move
}

void test_insert() {
    LinkedList<int> list;
    list.insert(1);
    assert(list.head_->data_ == 1);
    assert(list.tail_->data_ == 1);
    list.insert(2);
    assert(list.head_->data_ == 1);
    assert(list.tail_->data_ == 2);
}

void test_pop_head() {
    LinkedList<int> list = {1, 2, 3};
    std::optional<int> popped = list.pop_head();
    assert(popped == 1);
    assert(list.head_->data_ == 2);
}

void test_pop_tail() {
    LinkedList<int> list = {1, 2, 3};
    std::optional<int> popped = list.pop_tail();
    assert(popped == 3);
    assert(list.tail_->data_ == 2);
}

void test_search() {
    LinkedList<int> list = {1, 2, 3};
    assert(list.search(2) == true);
    assert(list.search(4) == false);
}

void test_empty_operations() {
    LinkedList<int> list;
    assert(list.pop_head() == std::nullopt);
    assert(list.pop_tail() == std::nullopt);
    assert(list.search(1) == false);
}

int main() {
    RUN_TEST(test_default_constructor);
    RUN_TEST(test_initializer_list_constructor);
    RUN_TEST(test_copy_constructor);
    RUN_TEST(test_move_constructor);
    RUN_TEST(test_copy_assignment);
    RUN_TEST(test_move_assignment);
    RUN_TEST(test_insert);
    RUN_TEST(test_pop_head);
    RUN_TEST(test_pop_tail);
    RUN_TEST(test_search);
    RUN_TEST(test_empty_operations);
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}