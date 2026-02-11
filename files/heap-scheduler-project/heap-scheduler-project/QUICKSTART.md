# Quick Start Guide

## Instalare Rapidă

### 1. Clonează/Descarcă Proiectul

```bash
# Dacă folosești git
git clone <repository-url>
cd heap-scheduler-project

# Sau extrage arhiva
unzip heap-scheduler-project.zip
cd heap-scheduler-project
```

### 2. Compilare

#### Opțiunea A: Cu script-ul build (Recomandat)
```bash
./build.sh
```

#### Opțiunea B: Manual cu CMake
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

#### Opțiunea C: Fără CMake (compilare directă)
```bash
g++ -std=c++17 -I./include \
    src/main.cpp \
    src/scheduler/scheduler.cpp \
    -o heap_scheduler
```

### 3. Rulare

```bash
# Dacă ai folosit build.sh sau CMake
cd build
./heap_scheduler

# Dacă ai compilat direct
./heap_scheduler
```

## Primii Pași

După pornire, vei vedea meniul principal:

```
╔════════════════════════════════════════════════╗
║     HEAP & SCHEDULER DEMONSTRATION             ║
╠════════════════════════════════════════════════╣
║  1. Binary Heap Demo                           ║
║  2. D-ary Heap Demo                            ║
║  3. Heap Comparison Demo                       ║
║  4. OS Scheduler Simulation                    ║
║  5. Performance Benchmark                      ║
║  6. Interactive Heap Builder                   ║
║  0. Exit                                       ║
╚════════════════════════════════════════════════╝
```

### Recomandări pentru Explorare

**Pentru începători:**
1. Începe cu **Binary Heap Demo** (opțiunea 1)
2. Apoi **Interactive Heap Builder** (opțiunea 6) pentru a experimenta

**Pentru înțelegere avansată:**
3. **Heap Comparison Demo** (opțiunea 3) - vezi diferențele
4. **OS Scheduler Simulation** (opțiunea 4) - aplicație practică

**Pentru performanță:**
5. **Performance Benchmark** (opțiunea 5) - rezultate detaliate

## Exemple de Utilizare în Cod

### Exemplu Simplu - Max Heap

```cpp
#include "heap/binary_heap.hpp"

int main() {
    MaxHeap<int> heap;
    
    // Adaugă elemente
    heap.push(10);
    heap.push(30);
    heap.push(20);
    heap.push(5);
    
    // Afișează maximul
    std::cout << "Max: " << heap.top() << std::endl;  // 30
    
    // Extrage în ordine descrescătoare
    while (!heap.empty()) {
        std::cout << heap.pop() << " ";  // 30 20 10 5
    }
    
    return 0;
}
```

### Exemplu - Scheduler

```cpp
#include "scheduler/scheduler.hpp"
#include "scheduler/process.hpp"

int main() {
    // Crează scheduler
    Scheduler scheduler(4, 1, 5, 2);
    
    // Adaugă procese
    scheduler.add_process(Process(1, "Browser", 5, 15, 0));
    scheduler.add_process(Process(2, "Editor", 8, 10, 1));
    
    // Rulează simularea
    scheduler.run();
    
    // Afișează statistici
    scheduler.display_statistics();
    
    return 0;
}
```

## Compilare Exemple Adiționale

```bash
# Exemple simple
g++ -std=c++17 -I./include examples/simple_examples.cpp -o simple_examples
./simple_examples

# Teste
g++ -std=c++17 -I./include tests/heap_tests.hpp -o run_tests
./run_tests
```

## Structura Fișierelor - Ghid Rapid

```
├── include/
│   ├── heap/           → Implementări heap
│   ├── scheduler/      → Sistem de scheduling
│   └── utils/          → Utilitare (benchmark, visualizer)
├── src/
│   ├── main.cpp        → Program principal
│   └── scheduler/      → Implementare scheduler
├── examples/           → Exemple de utilizare
├── tests/              → Unit tests
└── README.md           → Documentație completă
```

## Probleme Comune

### Eroare: "command not found: cmake"
**Soluție:** Instalează CMake
```bash
# Ubuntu/Debian
sudo apt-get install cmake

# macOS
brew install cmake

# Sau folosește compilarea directă (fără CMake)
```

### Eroare: "C++17 not supported"
**Soluție:** Update compiler sau specifică versiunea
```bash
g++-9 -std=c++17 ...  # Folosește o versiune mai nouă
```

### Heap property violation
**Soluție:** Verifică comparatorul - pentru max-heap folosește `std::less`, pentru min-heap `std::greater`

## Următorii Pași

1. **Explorează codul** - Citește implementările din `include/`
2. **Modifică și experimentează** - Schimbă parametrii în `main.cpp`
3. **Adaugă features** - Vezi `TODO.md` pentru idei
4. **Rulează benchmark-uri** - Generează date pentru raport
5. **Scrie documentație** - Creează raportul pentru proiect

## Resurse Utile

- **README.md** - Documentație completă
- **TODO.md** - Idei pentru extensii
- **examples/** - Cod exemplu
- **tests/** - Template-uri pentru teste

## Contact & Suport

Pentru întrebări sau probleme:
- Verifică documentația în README.md
- Citește comentariile din cod
- Consultă exemplele din `examples/`

---

**Succes la proiect! 🚀**
