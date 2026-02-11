# Heap & OS Scheduler Project

## Descriere

Proiect complex despre **heap-uri binare** și aplicația lor în **schedulere de sisteme de operare**. Proiectul demonstrează implementări multiple de heap-uri și utilizarea lor practică în gestionarea proceselor cu priorități.

## Caracteristici Principale

### 1. Implementări Multiple de Heap
- **Binary Heap** - implementare clasică cu 2 copii per nod
- **D-ary Heap** - generalizare cu D copii (configurabil)
- **Template generic** - funcționează cu orice tip de date
- **Statistici detaliate** - contoare pentru comparații și swap-uri

### 2. OS Scheduler Simulator
- **Priority-based scheduling** cu heap-uri
- **Priority aging** pentru prevenirea starvation
- **Multiple queues** (ready, waiting, expired)
- **Context switching simulation**
- **Statistici complete** (waiting time, turnaround time, CPU utilization)

### 3. Performance Benchmarking
- Comparații între tipuri de heap
- Măsurători de timp și operații
- Export rezultate în CSV
- Grafice în consolă

### 4. Vizualizări
- Reprezentare arbore ASCII
- Array representation cu indici
- Verificare proprietate heap
- Progress bars și grafice comparative

## Structura Proiectului

```
heap-scheduler-project/
├── include/
│   ├── heap/
│   │   ├── heap_base.hpp          # Interfață abstractă
│   │   ├── binary_heap.hpp        # Binary heap implementation
│   │   └── dary_heap.hpp          # D-ary heap implementation
│   ├── scheduler/
│   │   ├── process.hpp            # Process Control Block
│   │   └── scheduler.hpp          # OS Scheduler
│   └── utils/
│       ├── benchmark.hpp          # Performance testing
│       └── visualizer.hpp         # Console visualization
├── src/
│   ├── scheduler/
│   │   └── scheduler.cpp          # Scheduler implementation
│   └── main.cpp                   # Interactive demo
├── tests/                         # Unit tests (TO DO)
├── benchmarks/                    # Benchmark results
├── docs/                          # Documentation
└── CMakeLists.txt                 # Build configuration
```

## Compilare și Rulare

### Cerințe
- C++17 sau mai nou
- CMake 3.15+
- Compiler modern (GCC 7+, Clang 5+, MSVC 2017+)

### Build cu CMake

```bash
# Creare director build
mkdir build
cd build

# Configurare
cmake ..

# Compilare
cmake --build .

# Rulare
./heap_scheduler
```

### Build Manual (fără CMake)

```bash
# Compilare directă
g++ -std=c++17 -I./include src/main.cpp src/scheduler/scheduler.cpp -o heap_scheduler

# Rulare
./heap_scheduler
```

## Utilizare

Programul oferă un meniu interactiv cu următoarele opțiuni:

1. **Binary Heap Demo** - Demonstrație heap binar cu inserări și extrageri
2. **D-ary Heap Demo** - Comparație între heap-uri cu branching factors diferiți
3. **Heap Comparison** - Testare comparativă pe date random
4. **OS Scheduler Simulation** - Simulare scheduler cu procese
5. **Performance Benchmark** - Suite complet de benchmark-uri
6. **Interactive Heap Builder** - Constructor interactiv de heap

## Exemple de Cod

### Utilizare Binary Heap

```cpp
#include "heap/binary_heap.hpp"

// Max heap (implicit)
MaxHeap<int> max_heap;
max_heap.push(10);
max_heap.push(20);
max_heap.push(5);

std::cout << max_heap.top() << std::endl;  // 20
int max = max_heap.pop();                   // 20

// Min heap
MinHeap<int> min_heap;
min_heap.push(10);
min_heap.push(20);
min_heap.push(5);

std::cout << min_heap.top() << std::endl;  // 5
```

### Utilizare D-ary Heap

```cpp
#include "heap/dary_heap.hpp"

// Ternary heap (D=3)
TernaryHeap<int> heap;

// Quaternary heap (D=4)
QuaternaryHeap<int> heap2;

// Custom D
DaryHeap<int, 8> octary_heap;
```

### Utilizare Scheduler

```cpp
#include "scheduler/scheduler.hpp"

Scheduler scheduler(4, 1, 5, 2);  // quantum, context_time, aging_thresh, boost

Process p1(1, "Browser", 5, 15, 0);  // pid, name, priority, burst, arrival
Process p2(2, "Editor", 8, 10, 1);

scheduler.add_process(p1);
scheduler.add_process(p2);

scheduler.run();
scheduler.display_statistics();
```

## Complexități Temporale

### Binary Heap
- **Insert (push)**: O(log n)
- **Extract (pop)**: O(log n)
- **Peek (top)**: O(1)
- **Build heap**: O(n)

### D-ary Heap
- **Insert**: O(log_D n) - mai rapid decât binary
- **Extract**: O(D * log_D n) - mai lent (mai multe comparații)
- **Trade-off**: Optim pentru workload-uri cu multe inserări

## Concepte Demonstrare

### 1. Proprietatea Heap
- **Max-heap**: `parent >= children`
- **Min-heap**: `parent <= children`
- Verificare automată în visualizer

### 2. Priority Scheduling
- Procese executate în ordinea priorității
- **Aging mechanism** previne starvation
- **Dynamic priority adjustment**

### 3. Context Switching
- Overhead în schimbarea proceselor
- Impact asupra performanței
- Statistici detaliate

## Extensii Posibile

### Pentru nota maximă:
1. **Fibonacci Heap** - implementare avansată
2. **Thread-safe heap** - cu mutex-uri
3. **Custom allocator** - pentru optimizare memorie
4. **GUI visualization** - cu SFML/Qt
5. **Multi-level feedback queue** - scheduler mai complex
6. **Real-time constraints** - deadline scheduling

## Benchmark Results Sample

```
=== Testing with 10000 elements ===

Heap Type          Elements    Push (ms)   Pop (ms)    Total (ms)  Compares    Swaps
------------------------------------------------------------------------------------------------
Binary Heap        10000       2.345       3.123       5.468       45234       12456
Ternary Heap       10000       1.987       3.891       5.878       38901       11234
Quaternary Heap    10000       1.756       4.234       5.990       35678       10987
```

## Licență

Proiect academic - utilizare educațională.

## Autor

[Numele tău]  
[Email]  
[Universitate/Facultate]

## Referințe

1. Cormen, T. H., et al. "Introduction to Algorithms" (4th ed.)
2. Tanenbaum, A. S. "Modern Operating Systems"
3. Skiena, S. "The Algorithm Design Manual"
