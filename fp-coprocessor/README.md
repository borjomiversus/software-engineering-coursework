#### 2. `Lab2_CustomFloat_Coprocessor_CPP/README.md`

# Lab 2: Custom Floating-Point Format & Stack Coprocessor Emulator

A C++ implementation of a non-standard 42-bit floating-point format (`10h.31m`) paired with a software emulator of a stack-based math coprocessor (FPU).

## Data Format (`10h.31m`)
* **Sign (`s`):** 1 bit
* **Exponent / Characteristic (`h`):** 10 bits ($\text{Bias} = 2^{10-1} - 1 = 511$)
* **Mantissa (`m`):** 31 bits + 1 implicit leading bit
* **Total Width:** 42 bits (packed inside a 64-bit `union` bit-field)

## Features
1. **Bit-Level Inspector:** Converts standard IEEE 754 `double` values (including `0`, `1`, `+Inf`, `NaN`, and user inputs) into the 42-bit layout, displaying sign, biased exponent, implicit bit, and mantissa.
2. **Stack Coprocessor (`Coprocessor` class):** Simulates an 8-register stack (`st0`–`st7`) supporting `LOAD`, `ADD`, `SUB`, `MULT`, `DIV`, and `SWAP` via manual exponent alignment and mantissa bit-shifting.
3. **Function Evaluation:** Computes $F(a, b) = \frac{b - a}{b + 4a} - \frac{b}{a}$ using stack-based instructions.

## Example Output (`a = 12, b = 5`)
```text
FINAL RESULT:
Stack TOP: -0.548742
Bin: 1|0111111110|1.0001100011110100101110101100010
```

## Build & Run
```bash
g++ -std=c++17 -O2 main.cpp -o coprocessor
./coprocessor
```
