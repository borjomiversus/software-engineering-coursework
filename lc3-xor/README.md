# Lab 3: Bitwise XOR Implementation in LC-3 Assembly

An assembly program for the 16-bit Little Computer 3 (LC-3) educational architecture that computes the bitwise exclusive OR ($A \oplus B$) of two positive integers.

## Algorithm
Since the LC-3 instruction set lacks a native `XOR` opcode and only provides `AND` and `NOT`, the operation is synthesized using De Morgan's laws:

$$A \oplus B = \neg\Big(\neg(A \land \neg(A \land B)) \land \neg(B \land \neg(A \land B))\Big)$$

## Memory & Registers
* **Entry Point:** `.ORIG x3000`
* **Inputs:** `A = x000C` ($12_{10}$), `B = x0005` ($5_{10}$) loaded into `R0` and `R1`.
* **Intermediate Registers:** `R2`, `R3`, `R4` store partial NAND results.
* **Output:** Final result stored in `R5` and written to memory label `RESULT`.

## Verification
```text
A      = x000C (0000 0000 0000 1100)
B      = x0005 (0000 0000 0000 0101)
RESULT = x0009 (0000 0000 0000 1001) -> 9 in decimal
```

## Build & Run
```bash
Load main.asm into any LC-3 simulator (e.g., LC3Tools, PennSim, or Web LC-3), assemble into .obj, and run until HALT.
```
