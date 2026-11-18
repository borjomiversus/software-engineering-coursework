using System;
using System.Diagnostics;

const long Iter = 100_000_000; 
long dummy = 0; 

// вимірювання часу
double Measure(Action a) {
    GC.Collect();
    GC.WaitForPendingFinalizers();
    GC.Collect();
    var sw = Stopwatch.StartNew();
    a();
    return sw.Elapsed.TotalSeconds;
}
//функція калібрування
double Calibrate(Action a) {
    double minTime = double.MaxValue;
    for (int i = 0; i < 5; i++) {
        double t = Measure(a);
        if (t < minTime) minTime = t;
    }
    return minTime;
}
//час на генерацію операнда
double t0_normal = Calibrate(() => { 
    for (long i = 0; i < Iter; i++) dummy += (i % 100); 
});
//час на генерацію дільника
double t0_div = Calibrate(() => { 
    for (long i = 0; i < Iter; i++) dummy += ((i % 100) + 1); 
});
Result Run(string t, string o, double tOffset, Action a) {
    double totalTime = Measure(a);
    double dt = totalTime - tOffset; 
    
    if (dt <= 1e-9) dt = 1e-9; 
    
    return new Result(t, o, Iter / dt);
}
var results = new[] {
    // i16
    Run("i16", "+", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += (short)(5 + (i % 100)); }),
    Run("i16", "-", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += (short)(100 - (i % 100)); }),
    Run("i16", "*", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += (short)(5 * (i % 100)); }),
    Run("i16", "/", t0_div,    () => { for(long i=0; i<Iter; i++) dummy += (short)(1000 / ((i % 100) + 1)); }),
    Run("i16", "&", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += (short)(5 & (i % 100)); }),
    Run("i16", "|", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += (short)(5 | (i % 100)); }),
    // i32
    Run("i32", "+", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += 5 + (int)(i % 100); }),
    Run("i32", "-", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += 100 - (int)(i % 100); }),
    Run("i32", "*", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += 5 * (int)(i % 100); }),
    Run("i32", "/", t0_div,    () => { for(long i=0; i<Iter; i++) dummy += 1000 / ((int)(i % 100) + 1); }),
    Run("i32", "&", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += 5 & (int)(i % 100); }),
    Run("i32", "|", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += 5 | (int)(i % 100); }),   
    // i64 
    Run("i64", "+", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += 5L + i; }),
    Run("i64", "-", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += 100L - i; }),
    Run("i64", "*", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += 5L * (i % 1000); }),
    Run("i64", "/", t0_div,    () => { for(long i=0; i<Iter; i++) dummy += 1000L / ((i % 100) + 1); }),
    Run("i64", "&", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += 5L & i; }),
    Run("i64", "|", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += 5L | i; }),
    // float
    Run("float", "+", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += (long)(5.5f + (i % 100)); }),
    Run("float", "-", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += (long)(100.5f - (i % 100)); }),
    Run("float", "*", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += (long)(5.5f * (i % 100)); }),
    Run("float", "/", t0_div,    () => { for(long i=0; i<Iter; i++) dummy += (long)(1000.5f / ((i % 100) + 1)); }),
    // double
    Run("double", "+", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += (long)(5.5 + (i % 100)); }),
    Run("double", "-", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += (long)(100.5 - (i % 100)); }),
    Run("double", "*", t0_normal, () => { for(long i=0; i<Iter; i++) dummy += (long)(5.5 * (i % 100)); }),
    Run("double", "/", t0_div,    () => { for(long i=0; i<Iter; i++) dummy += (long)(1000.5 / ((i % 100) + 1)); })
};
double max = 0;
foreach (var res in results) if (res.Speed > max) max = res.Speed;

Console.WriteLine($"{"Type",-8} | {"Op",-3} | {"Ops/sec",-12} | {"%",-4} | Diagram");
Console.WriteLine(new string('-', 70));

foreach (var r in results) {
    int p = (int)(r.Speed / max * 100);
    if (p < 0) p = 0; if (p > 100) p = 100;
    Console.WriteLine($"{r.Type,-8} | {r.Op,-3} | {r.Speed,12:E2} | {p,3}% | {new string('X', p / 4)}");
}

Console.WriteLine($"\nCheck: {dummy}");

record Result(string Type, string Op, double Speed);
