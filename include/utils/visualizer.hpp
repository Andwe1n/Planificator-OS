#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

/**
 * @brief Heap visualizer for console output
 */
class HeapVisualizer {
public:
    /**
     * @brief Display heap as ASCII tree
     */
    template<typename T>
    static void display_tree(const std::vector<T>& heap_data) {
        if (heap_data.empty()) {
            std::cout << "Empty heap" << std::endl;
            return;
        }
        
        int height = static_cast<int>(std::log2(heap_data.size())) + 1;
        int max_width = (1 << height) - 1;
        
        std::cout << "\n=== Heap Tree Visualization ===" << std::endl;
        
        size_t index = 0;
        for (int level = 0; level < height && index < heap_data.size(); level++) {
            int nodes_in_level = 1 << level;
            int spacing = max_width / (nodes_in_level + 1);
            
            // Print leading spaces
            for (int i = 0; i < spacing; i++) {
                std::cout << " ";
            }
            
            // Print nodes in this level
            for (int i = 0; i < nodes_in_level && index < heap_data.size(); i++) {
                std::cout << heap_data[index];
                index++;
                
                // Print spacing between nodes
                for (int j = 0; j < 2 * spacing - 1; j++) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
            
            // Print connection lines (simplified)
            if (level < height - 1 && index < heap_data.size()) {
                for (int i = 0; i < spacing / 2; i++) {
                    std::cout << " ";
                }
                for (int i = 0; i < nodes_in_level && 2 * i + 1 < heap_data.size(); i++) {
                    std::cout << "/";
                    for (int j = 0; j < spacing - 2; j++) {
                        std::cout << " ";
                    }
                    if (2 * i + 2 < heap_data.size()) {
                        std::cout << "\\";
                    }
                    for (int j = 0; j < spacing; j++) {
                        std::cout << " ";
                    }
                }
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
    
    /**
     * @brief Display heap as array with indices
     */
    template<typename T>
    static void display_array(const std::vector<T>& heap_data) {
        std::cout << "\n=== Heap Array Representation ===" << std::endl;
        std::cout << "Index: ";
        for (size_t i = 0; i < heap_data.size(); i++) {
            std::cout << std::setw(4) << i << " ";
        }
        std::cout << "\nValue: ";
        for (const auto& val : heap_data) {
            std::cout << std::setw(4) << val << " ";
        }
        std::cout << "\n" << std::endl;
    }
    
    /**
     * @brief Display heap properties verification
     */
    template<typename T>
    static void verify_heap_property(const std::vector<T>& heap_data, bool is_max_heap = true) {
        std::cout << "\n=== Heap Property Verification ===" << std::endl;
        
        bool is_valid = true;
        for (size_t i = 0; i < heap_data.size(); i++) {
            size_t left = 2 * i + 1;
            size_t right = 2 * i + 2;
            
            if (is_max_heap) {
                if (left < heap_data.size() && heap_data[i] < heap_data[left]) {
                    std::cout << "Violation at index " << i << ": " 
                              << heap_data[i] << " < " << heap_data[left] << std::endl;
                    is_valid = false;
                }
                if (right < heap_data.size() && heap_data[i] < heap_data[right]) {
                    std::cout << "Violation at index " << i << ": " 
                              << heap_data[i] << " < " << heap_data[right] << std::endl;
                    is_valid = false;
                }
            } else {
                if (left < heap_data.size() && heap_data[i] > heap_data[left]) {
                    std::cout << "Violation at index " << i << ": " 
                              << heap_data[i] << " > " << heap_data[left] << std::endl;
                    is_valid = false;
                }
                if (right < heap_data.size() && heap_data[i] > heap_data[right]) {
                    std::cout << "Violation at index " << i << ": " 
                              << heap_data[i] << " > " << heap_data[right] << std::endl;
                    is_valid = false;
                }
            }
        }
        
        if (is_valid) {
            std::cout << "[OK] Heap property is VALID" << std::endl;
        } else {
            std::cout << "[ERROR] Heap property is VIOLATED" << std::endl;
        }
        std::cout << std::endl;
    }
    
    /**
     * @brief Create a progress bar
     */
    static void display_progress_bar(int current, int total, int width = 50) {
        float progress = static_cast<float>(current) / total;
        int pos = static_cast<int>(width * progress);
        
        std::cout << "[";
        for (int i = 0; i < width; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << "% (" 
                  << current << "/" << total << ")\r";
        std::cout.flush();
        
        if (current == total) {
            std::cout << std::endl;
        }
    }
    
    /**
     * @brief Display comparison chart
     */
    static void display_comparison_chart(const std::vector<std::pair<std::string, double>>& data) {
        std::cout << "\n=== Performance Comparison ===" << std::endl;
        
        // Find max value for scaling
        double max_val = 0;
        for (const auto& pair : data) {
            max_val = std::max(max_val, pair.second);
        }
        
        const int bar_width = 50;
        
        for (const auto& pair : data) {
            int bar_length = static_cast<int>((pair.second / max_val) * bar_width);
            
            std::cout << std::setw(20) << std::left << pair.first << " ";
            for (int i = 0; i < bar_length; i++) {
                std::cout << "█";
            }
            std::cout << " " << std::fixed << std::setprecision(2) << pair.second << std::endl;
        }
        std::cout << std::endl;
    }
};

#endif // VISUALIZER_HPP
