#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "process.hpp"
#include "../heap/binary_heap.hpp"
#include <vector>
#include <memory>
#include <queue>

/**
 * @brief CPU Scheduler using heap-based priority queues
 * 
 * Features:
 * - Priority-based scheduling with aging
 * - Multiple queues (ready, waiting)
 * - Context switching simulation
 * - Performance statistics
 */
class Scheduler {
private:
    // Ready queue - max heap by priority
    BinaryHeap<Process, ProcessPriorityComparator> ready_queue;
    
    // Waiting queue - min heap by I/O time
    BinaryHeap<Process, ProcessIOComparator> waiting_queue;
    
    // Process list for tracking
    std::vector<Process> processes;
    
    // Scheduler configuration
    int time_quantum;           // Time slice for each process
    int context_switch_time;    // Overhead for context switching
    int aging_threshold;        // Age before priority boost
    int priority_boost;         // How much to boost priority
    
    // Statistics
    int current_time;
    int total_context_switches;
    int total_processes_completed;
    Process* current_process;
    
    // Performance metrics
    double avg_waiting_time;
    double avg_turnaround_time;
    double avg_response_time;
    double cpu_utilization;
    int total_cpu_time;
    int total_idle_time;

public:
    /**
     * @brief Constructor
     */
    Scheduler(int quantum = 4, int context_time = 1, int aging_thresh = 5, int prio_boost = 1)
        : time_quantum(quantum)
        , context_switch_time(context_time)
        , aging_threshold(aging_thresh)
        , priority_boost(prio_boost)
        , current_time(0)
        , total_context_switches(0)
        , total_processes_completed(0)
        , current_process(nullptr)
        , avg_waiting_time(0.0)
        , avg_turnaround_time(0.0)
        , avg_response_time(0.0)
        , cpu_utilization(0.0)
        , total_cpu_time(0)
        , total_idle_time(0)
    {}
    
    /**
     * @brief Add a process to the scheduler
     */
    void add_process(const Process& proc) {
        processes.push_back(proc);
    }
    
    /**
     * @brief Add multiple processes
     */
    void add_processes(const std::vector<Process>& procs) {
        processes.insert(processes.end(), procs.begin(), procs.end());
    }
    
    /**
     * @brief Run the scheduler simulation
     */
    void run();
    
    /**
     * @brief Display scheduler statistics
     */
    void display_statistics() const;
    
    /**
     * @brief Get process statistics
     */
    std::vector<Process> get_completed_processes() const {
        std::vector<Process> completed;
        for (const auto& proc : processes) {
            if (proc.state == ProcessState::TERMINATED) {
                completed.push_back(proc);
            }
        }
        return completed;
    }
    
    /**
     * @brief Reset scheduler
     */
    void reset() {
        ready_queue.clear();
        waiting_queue.clear();
        processes.clear();
        current_time = 0;
        total_context_switches = 0;
        total_processes_completed = 0;
        current_process = nullptr;
        total_cpu_time = 0;
        total_idle_time = 0;
    }

private:
    /**
     * @brief Add newly arrived processes to ready queue
     */
    void check_new_arrivals();
    
    /**
     * @brief Check if any I/O operations completed
     */
    void check_io_completion();
    
    /**
     * @brief Apply aging to processes in ready queue
     */
    void apply_aging();
    
    /**
     * @brief Perform context switch
     */
    void context_switch();
    
    /**
     * @brief Calculate final statistics
     */
    void calculate_statistics();
    
    /**
     * @brief Display current state (for debugging)
     */
    void display_state() const;
};

#endif // SCHEDULER_HPP
