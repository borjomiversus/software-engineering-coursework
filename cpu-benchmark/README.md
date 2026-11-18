# Lab 1: Computational System Performance Benchmark

A micro-benchmarking tool written in C# (.NET) to measure processor throughput (`Ops/sec`) across different primitive data types and arithmetic/bitwise instructions.

## Tested Parameters
* **Data Types:** `short` (`i16`), `int` (`i32`), `long` (`i64`), `float` (32-bit), and `double` (64-bit).
* **Operations:** Addition (`+`), Subtraction (`-`), Multiplication (`*`), Division (`/`), Bitwise `AND` (`&`), and Bitwise `OR` (`|`).
* **Workload:** $10^8$ iterations per test with timer calibration (`t0_normal`, `t0_div`) to subtract loop and modulo overhead, plus a global `dummy` accumulator to prevent dead-code elimination by the JIT compiler.

## Key Findings
* **Native 64-bit Efficiency:** `i64` arithmetic and bitwise operations achieve peak throughput (~15–29 billion ops/sec on an AMD Ryzen 5 7535HS) due to native 64-bit register execution.
* **Type Promotion Overhead:** `i16` (`short`) performs no faster than `i32` (`int`), as C# promotes operands smaller than 32 bits to `int` prior to arithmetic execution and truncates the result back.
* **Division Bottleneck:** Integer and floating-point division consistently execute at ~1–3% of peak speed due to higher CPU cycle latency.

## How to Run
```bash
dotnet run
```

## Example Output 
<img width="581" height="566" alt="image" src="https://github.com/user-attachments/assets/419a3d00-6206-4ae8-99c0-fc0f7b52699d" />
