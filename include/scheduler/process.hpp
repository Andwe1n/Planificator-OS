#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>
#include <iostream>

/**
 * @brief Process states in the scheduler
 */
enum class ProcessState {
    NEW,        // Process just created
    READY,      // Ready to run
    RUNNING,    // Currently executing
    WAITING,    // Waiting for I/O
    TERMINATED  // Finished execution
};

/**
 * @brief Convert state to string for display
 */
inline std::string state_to_string(ProcessState state) {
    switch (state) {
        case ProcessState::NEW: return "NEW";
        case ProcessState::READY: return "READY";
        case ProcessState::RUNNING: return "RUNNING";
        case ProcessState::WAITING: return "WAITING";
        case ProcessState::TERMINATED: return "TERMINATED";
        default: return "UNKNOWN";
    }
}

/**
 * @brief Process Control Block (PCB)
 * Contains all information about a process
 */
struct Process {
    int pid;                    // Process ID
    std::string name;           // Process name
    int priority;               // Current priority (higher = more important)
    int base_priority;          // Original priority
    int burst_time;             // CPU time needed
    int remaining_time;         // Time left to execute
    int arrival_time;           // When process arrived
    int start_time;             // When process first ran (-1 if not started)
    int finish_time;            // When process completed
    int waiting_time;           // Total time in ready queue
    int response_time;          // Time from arrival to first run
    int turnaround_time;        // Time from arrival to completion
    int io_burst_time;          // Time needed for I/O
    int age;                    // Time spent waiting (for aging)
    ProcessState state;         // Current state
    
    /**
     * @brief Constructor for new process
     */
    Process(int id, const std::string& proc_name, int prio, int burst, int arrival = 0, int io_burst = 0)
        : pid(id)
        , name(proc_name)
        , priority(prio)
        , base_priority(prio)
        , burst_time(burst)
        , remaining_time(burst)
        , arrival_time(arrival)
        , start_time(-1)
        , finish_time(-1)
        , waiting_time(0)
        , response_time(-1)
        , turnaround_time(-1)
        , io_burst_time(io_burst)
        , age(0)
        , state(ProcessState::NEW)
    {}
    
    /**
     * @brief Default constructor
     */
    Process() 
        : pid(0)
        , name("")
        , priority(0)
        , base_priority(0)
        , burst_time(0)
        , remaining_time(0)
        , arrival_time(0)
        , start_time(-1)
        , finish_time(-1)
        , waiting_time(0)
        , response_time(-1)
        , turnaround_time(-1)
        , io_burst_time(0)
        , age(0)
        , state(ProcessState::NEW)
    {}
    
    /**
     * @brief Check if process is completed
     */
    bool is_completed() const {
        return remaining_time <= 0;
    }
    
    /**
     * @brief Execute process for given time quantum
     * @return Time actually executed
     */
    int execute(int time_quantum, int current_time) {
        if (start_time == -1) {
            start_time = current_time;
            response_time = current_time - arrival_time;
        }
        
        state = ProcessState::RUNNING;
        int executed = std::min(time_quantum, remaining_time);
        remaining_time -= executed;
        
        if (is_completed()) {
            state = ProcessState::TERMINATED;
            finish_time = current_time + executed;
            turnaround_time = finish_time - arrival_time;
        } else {
            state = ProcessState::READY;
        }
        
        return executed;
    }
    
    /**
     * @brief Increase age (for priority aging)
     */
    void increment_age() {
        age++;
        waiting_time++;
    }
    
    /**
     * @brief Apply aging - increase priority for waiting processes
     */
    void apply_aging(int aging_threshold = 5, int priority_boost = 1) {
        if (age >= aging_threshold) {
            priority = std::min(priority + priority_boost, 100); // Cap at 100
            age = 0; // Reset age after boost
        }
    }
    
    /**
     * @brief Reset priority to base
     */
    void reset_priority() {
        priority = base_priority;
        age = 0;
    }
    
    /**
     * @brief Display process information
     */
    void display() const {
        std::cout << "PID: " << pid 
                  << " | Name: " << name
                  << " | Priority: " << priority
                  << " | Burst: " << burst_time
                  << " | Remaining: " << remaining_time
                  << " | State: " << state_to_string(state)
                  << std::endl;
    }
};

/**
 * @brief Comparator for max-heap (higher priority first)
 */
struct ProcessPriorityComparator {
    bool operator()(const Process& a, const Process& b) const {
        // Higher priority = higher value
        // If priorities equal, use arrival time (FCFS as tiebreaker)
        if (a.priority != b.priority) {
            return a.priority > b.priority;
        }
        return a.arrival_time < b.arrival_time;
    }
};

/**
 * @brief Comparator for min-heap (earliest I/O completion first)
 */
struct ProcessIOComparator {
    bool operator()(const Process& a, const Process& b) const {
        return a.io_burst_time < b.io_burst_time;
    }
};

#endif // PROCESS_HPP
