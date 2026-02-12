#ifndef HEAP_BASE_HPP
#define HEAP_BASE_HPP

#include <vector>
#include <functional>
#include <stdexcept>

/**
 * @brief Abstract base class for heap data structures
 * @tparam T Type of elements stored in the heap
 * @tparam Compare Comparison function (default: std::less for max-heap)
 */
template<typename T, typename Compare = std::less<T>>
class HeapBase {
protected:
    std::vector<T> data;
    Compare comp;
    
    // Statistics
    size_t comparison_count = 0;
    size_t swap_count = 0;

public:
    HeapBase() = default;
    explicit HeapBase(const Compare& compare) : comp(compare) {}
    virtual ~HeapBase() = default;

    /**
     * @brief Insert an element into the heap
     * @param value Element to insert
     */
    virtual void push(const T& value) = 0;
    
    /**
     * @brief Remove and return the top element
     * @return Top element (max for max-heap, min for min-heap)
     */
    virtual T pop() = 0;
    
    /**
     * @brief Get the top element without removing it
     * @return Reference to top element
     */
    virtual const T& top() const {
        if (empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return data[0];
    }
    
    /**
     * @brief Check if heap is empty
     */
    bool empty() const { return data.empty(); }
    
    /**
     * @brief Get number of elements
     */
    size_t size() const { return data.size(); }
    
    /**
     * @brief Clear all elements
     */
    void clear() {
        data.clear();
        comparison_count = 0;
        swap_count = 0;
    }
    
    /**
     * @brief Get statistics
     */
    size_t get_comparisons() const { return comparison_count; }
    size_t get_swaps() const { return swap_count; }
    
    /**
     * @brief Reset statistics
     */
    void reset_stats() {
        comparison_count = 0;
        swap_count = 0;
    }

protected:
    /**
     * @brief Compare two elements and increment counter
     */
    bool compare(const T& a, const T& b) {
        comparison_count++;
        return comp(a, b);
    }
    
    /**
     * @brief Swap two elements and increment counter
     */
    void swap_elements(size_t i, size_t j) {
        swap_count++;
        std::swap(data[i], data[j]);
    }
};

#endif // HEAP_BASE_HPP
