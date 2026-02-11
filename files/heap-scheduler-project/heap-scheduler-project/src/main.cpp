#include <iostream>
#include <vector>
#include <random>
#include "heap/binary_heap.hpp"
#include "heap/dary_heap.hpp"
#include "scheduler/scheduler.hpp"
#include "scheduler/process.hpp"
#include "utils/benchmark.hpp"
#include "utils/visualizer.hpp"

void print_menu() {
    std::cout << "\n╔════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║     HEAP & SCHEDULER DEMONSTRATION             ║" << std::endl;
    std::cout << "╠════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║  1. Binary Heap Demo                           ║" << std::endl;
    std::cout << "║  2. D-ary Heap Demo                            ║" << std::endl;
    std::cout << "║  3. Heap Comparison Demo                       ║" << std::endl;
    std::cout << "║  4. OS Scheduler Simulation                    ║" << std::endl;
    std::cout << "║  5. Performance Benchmark                      ║" << std::endl;
    std::cout << "║  6. Interactive Heap Builder                   ║" << std::endl;
    std::cout << "║  0. Exit                                       ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════╝" << std::endl;
    std::cout << "Choose an option: ";
}

void binary_heap_demo() {
    std::cout << "\n=== Binary Heap Demonstration ===" << std::endl;
    
    // Create max heap
    MaxHeap<int> max_heap;
    
    std::vector<int> values = {15, 10, 20, 8, 12, 25, 6};
    
    std::cout << "\nInserting values: ";
    for (int val : values) {
        std::cout << val << " ";
        max_heap.push(val);
    }
    std::cout << std::endl;
    
    // Visualize
    std::vector<int> heap_data;
    MaxHeap<int> temp_heap = max_heap;
    while (!temp_heap.empty()) {
        heap_data.push_back(temp_heap.pop());
    }
    
    // Rebuild for visualization
    for (int val : values) {
        max_heap.push(val);
    }
    
    std::cout << "\nMax Heap Statistics:" << std::endl;
    std::cout << "Size: " << max_heap.size() << std::endl;
    std::cout << "Top element: " << max_heap.top() << std::endl;
    std::cout << "Comparisons: " << max_heap.get_comparisons() << std::endl;
    std::cout << "Swaps: " << max_heap.get_swaps() << std::endl;
    
    // Display structure
    HeapVisualizer::display_array(values);
    
    // Extract all elements
    std::cout << "\nExtracting in priority order: ";
    while (!max_heap.empty()) {
        std::cout << max_heap.pop() << " ";
    }
    std::cout << std::endl;
}

void dary_heap_demo() {
    std::cout << "\n=== D-ary Heap Demonstration ===" << std::endl;
    
    std::vector<int> values = {15, 10, 20, 8, 12, 25, 6, 30, 5, 18};
    
    // Ternary heap
    DaryHeap<int, 3> ternary_heap;
    std::cout << "\nTernary Heap (D=3):" << std::endl;
    for (int val : values) {
        ternary_heap.push(val);
    }
    std::cout << "Comparisons: " << ternary_heap.get_comparisons() << std::endl;
    std::cout << "Swaps: " << ternary_heap.get_swaps() << std::endl;
    
    // Quaternary heap
    DaryHeap<int, 4> quaternary_heap;
    std::cout << "\nQuaternary Heap (D=4):" << std::endl;
    for (int val : values) {
        quaternary_heap.push(val);
    }
    std::cout << "Comparisons: " << quaternary_heap.get_comparisons() << std::endl;
    std::cout << "Swaps: " << quaternary_heap.get_swaps() << std::endl;
    
    // Comparison
    std::vector<std::pair<std::string, double>> comparison = {
        {"Binary (D=2)", 0},
        {"Ternary (D=3)", static_cast<double>(ternary_heap.get_comparisons())},
        {"Quaternary (D=4)", static_cast<double>(quaternary_heap.get_comparisons())}
    };
    
    BinaryHeap<int> binary_heap;
    for (int val : values) {
        binary_heap.push(val);
    }
    comparison[0].second = binary_heap.get_comparisons();
    
    HeapVisualizer::display_comparison_chart(comparison);
}

void heap_comparison_demo() {
    std::cout << "\n=== Heap Type Comparison ===" << std::endl;
    
    const int NUM_ELEMENTS = 1000;
    std::vector<int> data;
    
    // Generate random data
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);
    
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        data.push_back(dis(gen));
    }
    
    std::cout << "\nTesting with " << NUM_ELEMENTS << " random elements..." << std::endl;
    
    // Binary heap
    BinaryHeap<int> binary;
    for (int val : data) binary.push(val);
    
    // Ternary heap
    DaryHeap<int, 3> ternary;
    for (int val : data) ternary.push(val);
    
    // Quaternary heap
    DaryHeap<int, 4> quaternary;
    for (int val : data) quaternary.push(val);
    
    // Display results
    std::cout << "\nOperation Counts:\n" << std::endl;
    std::cout << std::left << std::setw(20) << "Heap Type" 
              << std::setw(15) << "Comparisons" 
              << std::setw(15) << "Swaps" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << std::setw(20) << "Binary" 
              << std::setw(15) << binary.get_comparisons() 
              << std::setw(15) << binary.get_swaps() << std::endl;
    std::cout << std::setw(20) << "Ternary" 
              << std::setw(15) << ternary.get_comparisons() 
              << std::setw(15) << ternary.get_swaps() << std::endl;
    std::cout << std::setw(20) << "Quaternary" 
              << std::setw(15) << quaternary.get_comparisons() 
              << std::setw(15) << quaternary.get_swaps() << std::endl;
}

void scheduler_demo() {
    std::cout << "\n=== OS Scheduler Simulation ===" << std::endl;
    
    // Create scheduler
    Scheduler scheduler(
        4,  // time quantum
        1,  // context switch time
        5,  // aging threshold
        2   // priority boost
    );
    
    // Create processes
    std::vector<Process> processes = {
        Process(1, "Browser", 5, 15, 0, 3),
        Process(2, "Editor", 8, 10, 1, 0),
        Process(3, "Compiler", 3, 20, 2, 5),
        Process(4, "Music", 6, 8, 3, 2),
        Process(5, "Download", 2, 12, 4, 4),
        Process(6, "Email", 7, 6, 5, 0),
        Process(7, "Chat", 4, 10, 6, 1)
    };
    
    std::cout << "\nAdding " << processes.size() << " processes..." << std::endl;
    scheduler.add_processes(processes);
    
    // Run simulation
    scheduler.run();
    
    // Display results
    scheduler.display_statistics();
}

void benchmark_demo() {
    std::cout << "\n=== Performance Benchmark Suite ===" << std::endl;
    std::cout << "This may take a few moments...\n" << std::endl;
    
    HeapBenchmark benchmark;
    benchmark.run_comprehensive_benchmark();
    
    // Export results
    benchmark.export_to_csv("benchmark_results.csv");
}

void interactive_heap_builder() {
    std::cout << "\n=== Interactive Heap Builder ===" << std::endl;
    
    MaxHeap<int> heap;
    
    while (true) {
        std::cout << "\n1. Insert element" << std::endl;
        std::cout << "2. Remove top" << std::endl;
        std::cout << "3. View heap" << std::endl;
        std::cout << "4. View statistics" << std::endl;
        std::cout << "5. Clear heap" << std::endl;
        std::cout << "0. Back to main menu" << std::endl;
        std::cout << "Choice: ";
        
        int choice;
        std::cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                std::cout << "Enter value to insert: ";
                int val;
                std::cin >> val;
                heap.push(val);
                std::cout << "Inserted " << val << std::endl;
                break;
            }
            case 2: {
                if (!heap.empty()) {
                    int val = heap.pop();
                    std::cout << "Removed " << val << std::endl;
                } else {
                    std::cout << "Heap is empty!" << std::endl;
                }
                break;
            }
            case 3: {
                if (!heap.empty()) {
                    std::cout << "Current heap (size " << heap.size() << "):" << std::endl;
                    std::cout << "Top element: " << heap.top() << std::endl;
                } else {
                    std::cout << "Heap is empty!" << std::endl;
                }
                break;
            }
            case 4: {
                std::cout << "\nHeap Statistics:" << std::endl;
                std::cout << "Size: " << heap.size() << std::endl;
                std::cout << "Comparisons: " << heap.get_comparisons() << std::endl;
                std::cout << "Swaps: " << heap.get_swaps() << std::endl;
                break;
            }
            case 5: {
                heap.clear();
                std::cout << "Heap cleared!" << std::endl;
                break;
            }
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    }
}

int main() {
    std::cout << "╔════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                                                ║" << std::endl;
    std::cout << "║     HEAP & OS SCHEDULER PROJECT               ║" << std::endl;
    std::cout << "║     Binary Heaps & Process Scheduling         ║" << std::endl;
    std::cout << "║                                                ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════╝" << std::endl;
    
    int choice;
    
    while (true) {
        print_menu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                binary_heap_demo();
                break;
            case 2:
                dary_heap_demo();
                break;
            case 3:
                heap_comparison_demo();
                break;
            case 4:
                scheduler_demo();
                break;
            case 5:
                benchmark_demo();
                break;
            case 6:
                interactive_heap_builder();
                break;
            case 0:
                std::cout << "\nThank you for using the Heap & Scheduler demonstration!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
        }
    }
    
    return 0;
}
