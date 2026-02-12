#include "../include/scheduler/scheduler.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

void Scheduler::run() {
    std::cout << "\n=== Starting Scheduler Simulation ===\n" << std::endl;
    
    // Set all processes to NEW state
    for (auto& proc : processes) {
        proc.state = ProcessState::NEW;
    }
    
    // Main scheduling loop
    while (total_processes_completed < processes.size()) {
        // Check for new arrivals
        check_new_arrivals();
        
        // Check for I/O completions
        check_io_completion();
        
        // Apply aging to waiting processes
        apply_aging();
        
        // If ready queue is empty, advance time
        if (ready_queue.empty()) {
            current_time++;
            total_idle_time++;
            std::cout << "Time " << current_time << ": CPU IDLE" << std::endl;
            continue;
        }
        
        // Get next process from ready queue
        Process current = ready_queue.pop();
        
        // Context switch overhead
        if (current_process == nullptr || current_process->pid != current.pid) {
            context_switch();
        }
        
        std::cout << "\nTime " << current_time << ": Running process " 
                  << current.pid << " (Priority: " << current.priority 
                  << ", Remaining: " << current.remaining_time << ")" << std::endl;
        
        // Execute process
        int executed = current.execute(time_quantum, current_time);
        current_time += executed;
        total_cpu_time += executed;
        
        // Update process in main list
        for (auto& proc : processes) {
            if (proc.pid == current.pid) {
                proc = current;
                current_process = &proc;
                break;
            }
        }
        
        // Check if process completed
        if (current.is_completed()) {
            std::cout << "  -> Process " << current.pid << " COMPLETED" << std::endl;
            std::cout << "     Turnaround time: " << current.turnaround_time << std::endl;
            total_processes_completed++;
        } else {
            // Simulate I/O with some probability
            if (current.io_burst_time > 0 && (current.pid % 3 == 0)) {
                std::cout << "  -> Process " << current.pid << " going to I/O" << std::endl;
                current.state = ProcessState::WAITING;
                waiting_queue.push(current);
                
                // Update in main list
                for (auto& proc : processes) {
                    if (proc.pid == current.pid) {
                        proc = current;
                        break;
                    }
                }
            } else {
                // Put back in ready queue
                ready_queue.push(current);
            }
        }
        
        // Increment age for processes in ready queue (conceptually)
        // In real implementation, this would be done more efficiently
    }
    
    // Calculate final statistics
    calculate_statistics();
    
    std::cout << "\n=== Simulation Complete ===\n" << std::endl;
}

void Scheduler::check_new_arrivals() {
    for (auto& proc : processes) {
        if (proc.state == ProcessState::NEW && proc.arrival_time <= current_time) {
            proc.state = ProcessState::READY;
            ready_queue.push(proc);
            std::cout << "Time " << current_time << ": Process " << proc.pid 
                      << " arrived (Priority: " << proc.priority << ")" << std::endl;
        }
    }
}

void Scheduler::check_io_completion() {
    std::vector<Process> completed_io;
    
    // Check all processes in waiting queue
    while (!waiting_queue.empty()) {
        Process proc = waiting_queue.pop();
        
        // Simulate I/O completion (simplified)
        if (proc.io_burst_time > 0) {
            proc.io_burst_time--;
        }
        
        if (proc.io_burst_time == 0) {
            proc.state = ProcessState::READY;
            ready_queue.push(proc);
            std::cout << "Time " << current_time << ": Process " << proc.pid 
                      << " I/O completed" << std::endl;
            
            // Update in main list
            for (auto& p : processes) {
                if (p.pid == proc.pid) {
                    p = proc;
                    break;
                }
            }
        } else {
            completed_io.push_back(proc);
        }
    }
    
    // Put back processes still waiting for I/O
    for (auto& proc : completed_io) {
        waiting_queue.push(proc);
    }
}

void Scheduler::apply_aging() {
    // In a real implementation, you would rebuild the heap with updated priorities
    // This is a simplified version
    
    for (auto& proc : processes) {
        if (proc.state == ProcessState::READY) {
            proc.increment_age();
            proc.apply_aging(aging_threshold, priority_boost);
        }
    }
}

void Scheduler::context_switch() {
    total_context_switches++;
    current_time += context_switch_time;
    total_idle_time += context_switch_time;
}

void Scheduler::calculate_statistics() {
    int total_waiting = 0;
    int total_turnaround = 0;
    int total_response = 0;
    int count = 0;
    
    for (const auto& proc : processes) {
        if (proc.state == ProcessState::TERMINATED) {
            total_waiting += proc.waiting_time;
            total_turnaround += proc.turnaround_time;
            total_response += proc.response_time;
            count++;
        }
    }
    
    if (count > 0) {
        avg_waiting_time = static_cast<double>(total_waiting) / count;
        avg_turnaround_time = static_cast<double>(total_turnaround) / count;
        avg_response_time = static_cast<double>(total_response) / count;
    }
    
    cpu_utilization = (static_cast<double>(total_cpu_time) / current_time) * 100.0;
}

void Scheduler::display_statistics() const {
    std::cout << "\n================================================" << std::endl;
    std::cout << "        SCHEDULER STATISTICS                    " << std::endl;
    std::cout << "================================================" << std::endl;
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << " Total Time:              " << std::setw(10) << current_time << std::endl;
    std::cout << " CPU Time:                " << std::setw(10) << total_cpu_time << std::endl;
    std::cout << " Idle Time:               " << std::setw(10) << total_idle_time << std::endl;
    std::cout << " Context Switches:        " << std::setw(10) << total_context_switches << std::endl;
    std::cout << " Processes Completed:     " << std::setw(10) << total_processes_completed << std::endl;
    std::cout << "                                                " << std::endl;
    std::cout << " CPU Utilization:         " << std::setw(9) << cpu_utilization << "%" << std::endl;
    std::cout << " Avg Waiting Time:        " << std::setw(10) << avg_waiting_time << std::endl;
    std::cout << " Avg Turnaround Time:     " << std::setw(10) << avg_turnaround_time << std::endl;
    std::cout << " Avg Response Time:       " << std::setw(10) << avg_response_time << std::endl;
    std::cout << "================================================" << std::endl;
    
    // Display individual process statistics
    std::cout << "\n================================================================================" << std::endl;
    std::cout << "                           PROCESS DETAILS                                      " << std::endl;
    std::cout << "================================================================================" << std::endl;
    std::cout << "PID | Priority | Burst  | Arrival| Start | Finish   | Waiting   | Turnaround   " << std::endl;
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    
    for (const auto& proc : processes) {
        if (proc.state == ProcessState::TERMINATED) {
            std::cout << std::setw(3) << proc.pid 
                      << " | " << std::setw(9) << proc.base_priority
                      << "| " << std::setw(8) << proc.burst_time
                      << "| " << std::setw(7) << proc.arrival_time
                      << "| " << std::setw(7) << proc.start_time
                      << "| " << std::setw(10) << proc.finish_time
                      << "| " << std::setw(11) << proc.waiting_time
                      << "| " << std::setw(13) << proc.turnaround_time
                      << std::endl;
        }
    }
    std::cout << "================================================================================" << std::endl;
}

void Scheduler::display_state() const {
    std::cout << "\n--- Current State (Time: " << current_time << ") ---" << std::endl;
    std::cout << "Ready Queue Size: " << ready_queue.size() << std::endl;
    std::cout << "Waiting Queue Size: " << waiting_queue.size() << std::endl;
    if (current_process) {
        std::cout << "Current Process: " << current_process->pid << std::endl;
    }
}
