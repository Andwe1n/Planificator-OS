#include <iostream>
#include "../include/heap/binary_heap.hpp"
#include "../include/heap/dary_heap.hpp"

/**
 * Simple examples demonstrating heap usage
 */

void example_max_heap() {
    std::cout << "=== Max Heap Example ===" << std::endl;
    
    MaxHeap<int> heap;
    
    // Insert elements
    heap.push(10);
    heap.push(30);
    heap.push(20);
    heap.push(5);
    heap.push(40);
    
    std::cout << "Heap size: " << heap.size() << std::endl;
    std::cout << "Max element: " << heap.top() << std::endl;
    
    // Extract elements in descending order
    std::cout << "Elements in priority order: ";
    while (!heap.empty()) {
        std::cout << heap.pop() << " ";
    }
    std::cout << std::endl;
}

void example_min_heap() {
    std::cout << "\n=== Min Heap Example ===" << std::endl;
    
    MinHeap<int> heap;
    
    // Insert elements
    heap.push(10);
    heap.push(30);
    heap.push(20);
    heap.push(5);
    heap.push(40);
    
    std::cout << "Heap size: " << heap.size() << std::endl;
    std::cout << "Min element: " << heap.top() << std::endl;
    
    // Extract elements in ascending order
    std::cout << "Elements in priority order: ";
    while (!heap.empty()) {
        std::cout << heap.pop() << " ";
    }
    std::cout << std::endl;
}

void example_custom_comparator() {
    std::cout << "\n=== Custom Comparator Example ===" << std::endl;
    
    struct Person {
        std::string name;
        int age;
        
        Person(const std::string& n, int a) : name(n), age(a) {}
    };
    
    // Comparator: older people have higher priority
    struct AgeComparator {
        bool operator()(const Person& a, const Person& b) const {
            return a.age > b.age;
        }
    };
    
    BinaryHeap<Person, AgeComparator> heap;
    
    heap.push(Person("Alice", 25));
    heap.push(Person("Bob", 30));
    heap.push(Person("Charlie", 20));
    heap.push(Person("Diana", 35));
    
    std::cout << "People by age (descending):" << std::endl;
    while (!heap.empty()) {
        Person p = heap.pop();
        std::cout << "  " << p.name << " (" << p.age << ")" << std::endl;
    }
}

void example_heapify() {
    std::cout << "\n=== Heapify Example ===" << std::endl;
    
    std::vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6};
    
    std::cout << "Original array: ";
    for (int val : data) std::cout << val << " ";
    std::cout << std::endl;
    
    // Build heap in O(n) time
    MaxHeap<int> heap(data);
    
    std::cout << "Heap built! Top element: " << heap.top() << std::endl;
    std::cout << "Sorted (descending): ";
    
    while (!heap.empty()) {
        std::cout << heap.pop() << " ";
    }
    std::cout << std::endl;
}

void example_dary_heap() {
    std::cout << "\n=== D-ary Heap Example ===" << std::endl;
    
    // Ternary heap (3 children per node)
    TernaryHeap<int> t_heap;
    
    for (int i = 1; i <= 10; i++) {
        t_heap.push(i * 10);
    }
    
    std::cout << "Ternary heap (D=3):" << std::endl;
    std::cout << "  Size: " << t_heap.size() << std::endl;
    std::cout << "  Top: " << t_heap.top() << std::endl;
    std::cout << "  Comparisons: " << t_heap.get_comparisons() << std::endl;
    
    // Quaternary heap (4 children per node)
    QuaternaryHeap<int> q_heap;
    
    for (int i = 1; i <= 10; i++) {
        q_heap.push(i * 10);
    }
    
    std::cout << "\nQuaternary heap (D=4):" << std::endl;
    std::cout << "  Size: " << q_heap.size() << std::endl;
    std::cout << "  Top: " << q_heap.top() << std::endl;
    std::cout << "  Comparisons: " << q_heap.get_comparisons() << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "     HEAP USAGE EXAMPLES                " << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    example_max_heap();
    example_min_heap();
    example_custom_comparator();
    example_heapify();
    example_dary_heap();
    
    std::cout << "\n=== All examples completed! ===" << std::endl;
    
    return 0;
}
