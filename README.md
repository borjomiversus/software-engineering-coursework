# Software Engineering Coursework (KNU)

A collection of low-level programming, computer architecture, and algorithm design projects implemented in C++, C#, and LC-3 Assembly during my Software Engineering studies at Taras Shevchenko National University of Kyiv.

## Coursework & Labs

| Project | Language | Core Topics |
| :--- | :--- | :--- |
| **[`cpu-benchmark`](./cpu-benchmark)** | C# (.NET) | Instruction throughput (`Ops/sec`), JIT dead-code elimination, type promotion (`i16` vs `i32`/`i64`), OS context switching |
| **[`fp-coprocessor`](./fp-coprocessor)** | C++ | Custom 42-bit IEEE 754 floating-point format (`10h.31m`), bit-level packing/unpacking, stack-based FPU emulator |
| **[`heap-sort`](./heap-sort)** | C++ | In-place $d$-ary max-heap sort, Floyd's $O(n)$ heap construction, height vs. comparison trade-offs |
| **[`lc3-xor`](./lc3-xor)** | LC-3 ASM | Low-level register manipulation, bitwise `XOR` synthesis via De Morgan's laws (`AND` + `NOT`) |
| **[`Linked Lists Research`](https://github.com/borjomiversus/linked-lists-research)** | C++ | Deep-dive research: Circular, Sentinel, and XOR Linked Lists, micro-benchmarking (Time/RAM trade-offs), Kanban workflow |

---

## Featured Pet Project

### [Myosotis — Personal Movie & TV Series Tracker]([https://github.com/borjomiversus/myosotis](https://github.com/borjomiversus/Moysotis))
A full-featured media tracking web application built with **C#**, **Blazor Server**, **MudBlazor**, and the **TMDB REST API**. Supports custom watchlists, viewing history, and a quick-capture notes system for unorganized media mentions.
