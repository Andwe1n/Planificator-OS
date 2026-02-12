#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <chrono>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "../heap/binary_heap.hpp"
#include "../heap/dary_heap.hpp"

/**
 * @brief Simple timer class for benchmarking
 */
class Timer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    
public:
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }
    
    double elapsed_ms() const {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        return duration.count() / 1000.0;
    }
    
    double elapsed_us() const {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        return duration.count();
    }
};

/**
 * @brief Benchmark results structure
 */
struct BenchmarkResult {
    std::string heap_type;
    size_t num_elements;
    double push_time_ms;
    double pop_time_ms;
    double total_time_ms;
    size_t comparisons;
    size_t swaps;
    
    void display() const {
        std::cout << std::left << std::setw(20) << heap_type
                  << std::setw(12) << num_elements
                  << std::setw(12) << std::fixed << std::setprecision(3) << push_time_ms
                  << std::setw(12) << pop_time_ms
                  << std::setw(12) << total_time_ms
                  << std::setw(12) << comparisons
                  << std::setw(12) << swaps
                  << std::endl;
    }
};

/**
 * @brief Heap benchmark suite
 */
class HeapBenchmark {
private:
    std::vector<BenchmarkResult> results;

public:
    /**
     * @brief Benchmark a heap implementation
     */
    template<typename HeapType>
    BenchmarkResult benchmark_heap(const std::string& name, const std::vector<int>& data) {
        BenchmarkResult result;
        result.heap_type = name;
        result.num_elements = data.size();
        
        HeapType heap;
        Timer timer;
        
        // Benchmark push operations
        timer.start();
        for (int val : data) {
            heap.push(val);
        }
        result.push_time_ms = timer.elapsed_ms();
        
        // Get statistics after pushes
        result.comparisons = heap.get_comparisons();
        result.swaps = heap.get_swaps();
        
        // Benchmark pop operations
        heap.reset_stats();
        timer.start();
        while (!heap.empty()) {
            heap.pop();
        }
        result.pop_time_ms = timer.elapsed_ms();
        
        result.total_time_ms = result.push_time_ms + result.pop_time_ms;
        
        return result;
    }
    
    /**
     * @brief Run comprehensive benchmark suite
     */
    void run_comprehensive_benchmark() {
        std::cout << "\n================================================================================" << std::endl;
        std::cout << "                    HEAP PERFORMANCE BENCHMARK                                  " << std::endl;
        std::cout << "================================================================================\n" << std::endl;
        
        std::vector<size_t> sizes = {100, 1000, 10000, 100000};
        
        for (size_t size : sizes) {
            std::cout << "\n--- Testing with " << size << " elements ---\n" << std::endl;
            
            // Generate random data
            std::vector<int> data = generate_random_data(size);
            
            // Display header
            std::cout << std::left 
                      << std::setw(20) << "Heap Type"
                      << std::setw(12) << "Elements"
                      << std::setw(12) << "Push (ms)"
                      << std::setw(12) << "Pop (ms)"
                      << std::setw(12) << "Total (ms)"
                      << std::setw(12) << "Compares"
                      << std::setw(12) << "Swaps"
                      << std::endl;
            std::cout << std::string(92, '-') << std::endl;
            
            // Benchmark different heap types
            auto binary_result = benchmark_heap<BinaryHeap<int>>("Binary Heap", data);
            binary_result.display();
            results.push_back(binary_result);
            
            auto ternary_result = benchmark_heap<DaryHeap<int, 3>>("Ternary Heap", data);
            ternary_result.display();
            results.push_back(ternary_result);
            
            auto quaternary_result = benchmark_heap<DaryHeap<int, 4>>("Quaternary Heap", data);
            quaternary_result.display();
            results.push_back(quaternary_result);
        }
    }
    
    /**
     * @brief Export results to CSV
     */
    void export_to_csv(const std::string& filename) const {
        std::ofstream file(filename);
        
        file << "HeapType,Elements,PushTime,PopTime,TotalTime,Comparisons,Swaps\n";
        
        for (const auto& result : results) {
            file << result.heap_type << ","
                 << result.num_elements << ","
                 << result.push_time_ms << ","
                 << result.pop_time_ms << ","
                 << result.total_time_ms << ","
                 << result.comparisons << ","
                 << result.swaps << "\n";
        }
        
        std::cout << "\nResults exported to " << filename << std::endl;
    }

private:
    /**
     * @brief Generate random test data
     */
    std::vector<int> generate_random_data(size_t size) const {
        std::vector<int> data;
        data.reserve(size);
        
        for (size_t i = 0; i < size; i++) {
            data.push_back(rand() % 10000);
        }
        
        return data;
    }
};

#endif // BENCHMARK_HPP
