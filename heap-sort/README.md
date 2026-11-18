#### 4. `TaskH_Dary_Heap_Sort_CPP/README.md`
```markdown
# Task H: In-Place d-ary Heap Sort

An in-place ascending Heap Sort implementation in C++ built on a 0-indexed $d$-ary max-heap ($d \in \{3, 4, 5\}$) without auxiliary memory or STL heap utilities.

## Algorithm Overview
* **Tree Indexing (0-based):**
  * Children of node $i$: $d \cdot i + 1, d \cdot i + 2, \dots, \min(n - 1, d \cdot i + d)$
  * Parent of node $i$ ($i > 0$): $\lfloor (i - 1) / d \rfloor$
* **Floyd's Heap Construction ($O(n)$):** Iterates bottom-up from the last internal node $\lfloor (n - 2) / d \rfloor$ down to root `0`, calling `siftDown`.
* **Sorting Phase ($O(n \cdot d \log_d n)$):** Repeatedly swaps root `a[0]` with `a[size - 1]`, decrements `size`, and restores the max-heap invariant via `siftDown`.

## Complexity Trade-off
Increasing the branching factor $d$ reduces heap height to $O(\log_d n)$, while increasing comparisons per sift-down level to at most $d$ ($d - 1$ comparisons among children + $1$ comparison with the parent).

## Input & Output Format
* **`array.txt`:** First line contains $n$; second line contains $n$ distinct integers.
* **`params.txt`:** First line contains $d$ and $m$; second line contains three 0-based indices $p_1, p_2, p_3$.
* **Stdout:** Prints `a[p1] a[p2] a[p3]` after heap construction, after $m$ sorting steps, and after full sorting.

## Build & Run
```bash
g++ -std=c++17 -O2 main.cpp -o dary_heapsort
./dary_heapsort
