
COMPILE:
 
g++ -std=c++11 -o 2405036 2405036.cpp


RUN:
    Ensure input.txt exists in the same directory.
    Execute:  ./2405036
    Output is written to output.txt and also printed to the console.

Difference:

diff exOutput.txt output.txt

Undo:
cd ..


PART A – COMMANDS (as specified):
    I h x       : Insert x into heap h (h=1 or 2)
    F h         : Find min in heap h
    E h         : Extract min from heap h
    D h x y     : Decrease key x to y in heap h
    R h x       : Remove key x from heap h
    U h1 h2     : Union heap h1 and h2, store in h1, empty h2
    P h         : Print heap h in the fixed Part A format

PART B – VISUALIZER (extra commands):
   - "V h": Visualizes Heap H_h as explicit ASCII trees showing parent-child hierarchy.
   - "UV h1 h2": Demonstrates step-by-step Union merging between H_h1 and H_h2,
    showing intermediate steps and final merged state.

EXTRA FEATURE:
Structural Degree Distribution Profiler: Calculates and prints root degree metrics
 (`Root degrees: [...]`) alongside tree height parameters to verify $O(\log n)$ max
  tree depth properties during evaluation.
