#ifndef HEAP_TESTS_HPP
#define HEAP_TESTS_HPP

#include <iostream>
#include <cassert>
#include <vector>
#include "../include/heap/binary_heap.hpp"
#include "../include/heap/dary_heap.hpp"

/**
 * Simple test framework
 */
class TestFramework {
private:
    int tests_run = 0;
    int tests_passed = 0;
    
public:
    void run_test(const std::string& name, bool (*test_func)()) {
        tests_run++;
        std::cout << "Running: " << name << "... ";
        
        if (test_func()) {
            tests_passed++;
            std::cout << "[PASSED]" << std::endl;
        } else {
            std::cout << "[FAILED]" << std::endl;
        }
    }
    
    void display_summary() {
        std::cout << "\n=== Test Summary ===" << std::endl;
        std::cout << "Tests run: " << tests_run << std::endl;
        std::cout << "Tests passed: " << tests_passed << std::endl;
        std::cout << "Tests failed: " << (tests_run - tests_passed) << std::endl;
        
        if (tests_passed == tests_run) {
            std::cout << "[SUCCESS] All tests passed!" << std::endl;
        }
    }
};

/**
 * Test cases for Binary Heap
 */
bool test_max_heap_basic() {
    MaxHeap<int> heap;
    heap.push(10);
    heap.push(30);
    heap.push(20);
    
    return heap.top() == 30 && heap.size() == 3;
}

bool test_min_heap_basic() {
    MinHeap<int> heap;
    heap.push(10);
    heap.push(30);
    heap.push(20);
    
    return heap.top() == 10 && heap.size() == 3;
}

bool test_heap_pop() {
    MaxHeap<int> heap;
    heap.push(10);
    heap.push(30);
    heap.push(20);
    
    int max = heap.pop();
    return max == 30 && heap.top() == 20 && heap.size() == 2;
}

bool test_heap_empty() {
    MaxHeap<int> heap;
    return heap.empty() && heap.size() == 0;
}

bool test_heap_ordering() {
    MaxHeap<int> heap;
    std::vector<int> values = {5, 3, 8, 1, 9, 2, 7};
    
    for (int val : values) {
        heap.push(val);
    }
    
    std::vector<int> sorted;
    while (!heap.empty()) {
        sorted.push_back(heap.pop());
    }
    
    // Check descending order
    for (size_t i = 1; i < sorted.size(); i++) {
        if (sorted[i-1] < sorted[i]) {
            return false;
        }
    }
    
    return true;
}

bool test_heapify() {
    std::vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6};
    MaxHeap<int> heap(data);
    
    return heap.top() == 9 && heap.size() == 8;
}

bool test_heap_clear() {
    MaxHeap<int> heap;
    heap.push(10);
    heap.push(20);
    heap.clear();
    
    return heap.empty() && heap.size() == 0;
}

bool test_dary_heap_basic() {
    TernaryHeap<int> heap;
    heap.push(10);
    heap.push(30);
    heap.push(20);
    
    return heap.top() == 30 && heap.size() == 3;
}

bool test_heap_statistics() {
    MaxHeap<int> heap;
    heap.push(10);
    heap.push(20);
    heap.push(30);
    
    size_t comparisons = heap.get_comparisons();
    size_t swaps = heap.get_swaps();
    
    return comparisons > 0 && swaps >= 0;
}

bool test_large_heap() {
    MaxHeap<int> heap;
    const int SIZE = 10000;
    
    for (int i = 0; i < SIZE; i++) {
        heap.push(i);
    }
    
    return heap.size() == SIZE && heap.top() == SIZE - 1;
}

/**
 * Main test runner
 */
void run_all_tests() {
    std::cout << "========================================" << std::endl;
    std::cout << "     HEAP UNIT TESTS                    " << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    TestFramework framework;
    
    // Run tests
    framework.run_test("Max Heap Basic", test_max_heap_basic);
    framework.run_test("Min Heap Basic", test_min_heap_basic);
    framework.run_test("Heap Pop", test_heap_pop);
    framework.run_test("Heap Empty", test_heap_empty);
    framework.run_test("Heap Ordering", test_heap_ordering);
    framework.run_test("Heapify", test_heapify);
    framework.run_test("Heap Clear", test_heap_clear);
    framework.run_test("D-ary Heap Basic", test_dary_heap_basic);
    framework.run_test("Heap Statistics", test_heap_statistics);
    framework.run_test("Large Heap", test_large_heap);
    
    framework.display_summary();
}

#endif // HEAP_TESTS_HPP
