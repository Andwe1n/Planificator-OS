#ifndef DARY_HEAP_HPP
#define DARY_HEAP_HPP

#include "heap_base.hpp"

/**
 * @brief D-ary heap (generalization of binary heap with D children)
 * @tparam T Type of elements
 * @tparam D Number of children per node (default: 4)
 * @tparam Compare Comparison function
 * 
 * Advantages over binary heap:
 * - Better cache performance for large heaps
 * - Faster push operations (shallower tree)
 * - Trade-off: slower pop (more comparisons per level)
 * 
 * Optimal D value depends on:
 * - D=2: Traditional binary heap
 * - D=3-4: Good balance for most cases
 * - D=8-16: Better for push-heavy workloads
 */
template<typename T, size_t D = 4, typename Compare = std::less<T>>
class DaryHeap : public HeapBase<T, Compare> {
    using Base = HeapBase<T, Compare>;
    
    static_assert(D >= 2, "D must be at least 2");

public:
    DaryHeap() = default;
    explicit DaryHeap(const Compare& compare) : Base(compare) {}
    
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
     * @brief Get the branching factor
     */
    static constexpr size_t branching_factor() { return D; }

private:
    /**
     * @brief Get parent index in D-ary heap
     */
    static size_t parent(size_t i) {
        return (i - 1) / D;
    }
    
    /**
     * @brief Get k-th child index (k = 0 to D-1)
     */
    static size_t kth_child(size_t i, size_t k) {
        return D * i + k + 1;
    }
    
    /**
     * @brief Get first child index
     */
    static size_t first_child(size_t i) {
        return D * i + 1;
    }
    
    /**
     * @brief Heapify upward
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
     * @brief Heapify downward
     * More complex than binary heap - need to check D children
     */
    void heapify_down(size_t index) {
        size_t size = Base::data.size();
        
        while (true) {
            size_t best = index;
            size_t first = first_child(index);
            
            // Check all D children
            for (size_t i = 0; i < D && first + i < size; i++) {
                size_t child = first + i;
                if (Base::compare(Base::data[child], Base::data[best])) {
                    best = child;
                }
            }
            
            if (best != index) {
                Base::swap_elements(index, best);
                index = best;
            } else {
                break;
            }
        }
    }
};

// Common specializations
template<typename T>
using TernaryHeap = DaryHeap<T, 3>;

template<typename T>
using QuaternaryHeap = DaryHeap<T, 4>;

#endif // DARY_HEAP_HPP
