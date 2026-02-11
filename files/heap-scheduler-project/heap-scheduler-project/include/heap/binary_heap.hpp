#ifndef BINARY_HEAP_HPP
#define BINARY_HEAP_HPP

#include "heap_base.hpp"
#include <algorithm>

/**
 * @brief Standard binary heap implementation
 * @tparam T Type of elements
 * @tparam Compare Comparison function (std::less = max-heap, std::greater = min-heap)
 * 
 * Time Complexity:
 * - push: O(log n)
 * - pop: O(log n)
 * - top: O(1)
 * 
 * Space Complexity: O(n)
 */
template<typename T, typename Compare = std::less<T>>
class BinaryHeap : public HeapBase<T, Compare> {
    using Base = HeapBase<T, Compare>;
    
public:
    BinaryHeap() = default;
    explicit BinaryHeap(const Compare& compare) : Base(compare) {}
    
    /**
     * @brief Construct heap from vector (heapify)
     * Time complexity: O(n)
     */
    explicit BinaryHeap(const std::vector<T>& elements, const Compare& compare = Compare()) 
        : Base(compare) {
        Base::data = elements;
        build_heap();
    }
    
    void push(const T& value) override {
        Base::data.push_back(value);
        heapify_up(Base::data.size() - 1);
    }
    
    T pop() override {
        if (Base::empty()) {
            throw std::out_of_range("Cannot pop from empty heap");
        }
        
        T result = Base::data[0];
        Base::data[0] = Base::data.back();
        Base::data.pop_back();
        
        if (!Base::empty()) {
            heapify_down(0);
        }
        
        return result;
    }
    
    /**
     * @brief Update priority of element at index
     * Useful for priority queues with changing priorities
     */
    void update(size_t index, const T& new_value) {
        if (index >= Base::data.size()) {
            throw std::out_of_range("Index out of range");
        }
        
        T old_value = Base::data[index];
        Base::data[index] = new_value;
        
        // Determine direction to heapify
        if (Base::compare(new_value, old_value)) {
            heapify_up(index);
        } else {
            heapify_down(index);
        }
    }
    
    /**
     * @brief Build heap from existing data
     * Time: O(n) - better than n insertions O(n log n)
     */
    void build_heap() {
        // Start from last non-leaf node
        for (int i = (Base::data.size() / 2) - 1; i >= 0; i--) {
            heapify_down(i);
        }
    }

private:
    /**
     * @brief Get parent index
     */
    static size_t parent(size_t i) { return (i - 1) / 2; }
    
    /**
     * @brief Get left child index
     */
    static size_t left_child(size_t i) { return 2 * i + 1; }
    
    /**
     * @brief Get right child index
     */
    static size_t right_child(size_t i) { return 2 * i + 2; }
    
    /**
     * @brief Restore heap property upward (for insertion)
     */
    void heapify_up(size_t index) {
        while (index > 0) {
            size_t parent_idx = parent(index);
            
            if (Base::compare(Base::data[index], Base::data[parent_idx])) {
                Base::swap_elements(index, parent_idx);
                index = parent_idx;
            } else {
                break;
            }
        }
    }
    
    /**
     * @brief Restore heap property downward (for deletion)
     */
    void heapify_down(size_t index) {
        size_t size = Base::data.size();
        
        while (true) {
            size_t largest = index;
            size_t left = left_child(index);
            size_t right = right_child(index);
            
            // Find largest among node and children
            if (left < size && Base::compare(Base::data[left], Base::data[largest])) {
                largest = left;
            }
            
            if (right < size && Base::compare(Base::data[right], Base::data[largest])) {
                largest = right;
            }
            
            // If largest is not current node, swap and continue
            if (largest != index) {
                Base::swap_elements(index, largest);
                index = largest;
            } else {
                break;
            }
        }
    }
};

// Type aliases for convenience
template<typename T>
using MaxHeap = BinaryHeap<T, std::less<T>>;

template<typename T>
using MinHeap = BinaryHeap<T, std::greater<T>>;

#endif // BINARY_HEAP_HPP
