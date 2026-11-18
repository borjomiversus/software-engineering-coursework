#include <iostream>
#include <cmath>
#include <bitset>
#include <cstdint>
#include <limits>
#include <algorithm>
using namespace std;

const int EXP_BITS = 10;
const int MANT_BITS = 31;
const int BIAS = 511;

// власний тип даних
union CustomFloat {
    uint64_t raw; 
    struct {
        uint64_t mantissa : 31; 
        uint64_t exponent : 10; 
        uint64_t sign : 1;      
        uint64_t padding : 22;  
    } bits;
};

// double у 42-бітний формат
CustomFloat Pack(double value) {
    union { double d; uint64_t i; } source; source.d = value;
    CustomFloat res; res.raw = 0;
    
    if (value == 0.0) return res;

    res.bits.sign = source.i >> 63; 
    
    int64_t stdExp = (source.i >> 52) & 0x7FF;
    
    if (stdExp == 0x7FF) { 
        res.bits.exponent = 0x3FF;
        res.bits.mantissa = (source.i >> (52 - MANT_BITS)) & 0x7FFFFFFF;
        return res;
    }
    if (stdExp == 0) return res; 

    int64_t newExp = stdExp - 1023 + BIAS;
    if (newExp <= 0) newExp = 0;
    if (newExp >= 0x3FF) newExp = 0x3FF;

    res.bits.exponent = newExp;
    res.bits.mantissa = (source.i >> (52 - MANT_BITS)) & 0x7FFFFFFF;
    return res;
}

// назад у double тільки для виводу на екран
double Unpack(CustomFloat custom) {
    if (custom.bits.exponent == 0 && custom.bits.mantissa == 0) return 0.0;
    union { double d; uint64_t i; } dest; dest.i = 0;
    dest.i |= ((uint64_t)custom.bits.sign << 63);
    int64_t stdExp = custom.bits.exponent - BIAS + 1023;
    dest.i |= ((uint64_t)stdExp << 52);
    dest.i |= ((uint64_t)custom.bits.mantissa << (52 - MANT_BITS));
    return dest.d;
}

// перша частина 
void PrintBinaryFormat(double number, string desc) {
    CustomFloat num = Pack(number); 
    
    int implicitBit = (num.bits.exponent == 0) ? 0 : 1;

    cout << desc << ": " << number << endl;
    cout << "Bin: " << num.bits.sign << "|" 
         << bitset<10>(num.bits.exponent) << "|" 
         << implicitBit << "." 
         << bitset<31>(num.bits.mantissa) << endl << endl;
}

// емулятор 
class Coprocessor {
private:
    CustomFloat registers[8]; 
    int top;
public:
    Coprocessor() { top = -1; }
    
    void Load(double value) {
        if (top < 7) { 
            registers[++top] = Pack(value); 
            cout << "CMD: LOAD " << value << endl; 
        }
    }
    
    void Add() { 
        if(top >= 1) { 
            CustomFloat a = registers[top - 1];
            CustomFloat b = registers[top];

            uint64_t mantA = a.bits.exponent > 0 ? (a.bits.mantissa | (1ULL << 31)) : 0;
            uint64_t mantB = b.bits.exponent > 0 ? (b.bits.mantissa | (1ULL << 31)) : 0;
            uint64_t expA = a.bits.exponent, expB = b.bits.exponent;

            if (expA > expB) { mantB >>= (expA - expB); expB = expA; }
            else if (expB > expA) { mantA >>= (expB - expA); expA = expB; }

            uint64_t resMant = 0, resExp = expA, resSign = 0;

            if (a.bits.sign == b.bits.sign) { 
                resMant = mantA + mantB; 
                resSign = a.bits.sign; 
            } else {
                if (mantA >= mantB) { resMant = mantA - mantB; resSign = a.bits.sign; }
                else { resMant = mantB - mantA; resSign = b.bits.sign; }
            }

            if (resMant == 0) { resExp = 0; resSign = 0; }
            else {
                if (resMant & (1ULL << 32)) { resMant >>= 1; resExp++; }
                else { while ((resMant & (1ULL << 31)) == 0 && resExp > 0) { resMant <<= 1; resExp--; } }
            }

            registers[top - 1].bits.sign = resSign; 
            registers[top - 1].bits.exponent = resExp; 
            registers[top - 1].bits.mantissa = resMant & 0x7FFFFFFF;
            
            top--; 
            cout << " -> ADD" << endl; 
        } 
    }
    
    void Sub() { 
        if(top >= 1) { 
            //інвертуємо знак верхнього числа
            registers[top].bits.sign = !registers[top].bits.sign; 
            
            Add(); 
            
            cout << " -> SUB" << endl; 
        } 
    }
    
    void Mult() { 
        if(top >= 1) { 
            CustomFloat a = registers[top - 1];
            CustomFloat b = registers[top];

            uint64_t mantA = a.bits.exponent > 0 ? (a.bits.mantissa | (1ULL << 31)) : 0;
            uint64_t mantB = b.bits.exponent > 0 ? (b.bits.mantissa | (1ULL << 31)) : 0;

            uint64_t resSign = a.bits.sign ^ b.bits.sign;
            uint64_t resExp = a.bits.exponent + b.bits.exponent - BIAS;
            uint64_t resMant = mantA * mantB; 

            if (resMant & (1ULL << 63)) { resMant >>= 32; resExp++; } else { resMant >>= 31; }

            registers[top - 1].bits.sign = resSign;
            registers[top - 1].bits.exponent = resExp;
            registers[top - 1].bits.mantissa = resMant & 0x7FFFFFFF;
            
            top--; 
            cout << " -> MULT" << endl; 
        } 
    }
    
    void Div() { 
        if(top >= 1) { 
            CustomFloat a = registers[top - 1];
            CustomFloat b = registers[top];

            uint64_t mantA = a.bits.exponent > 0 ? (a.bits.mantissa | (1ULL << 31)) : 0;
            uint64_t mantB = b.bits.exponent > 0 ? (b.bits.mantissa | (1ULL << 31)) : 0;

            uint64_t resSign = a.bits.sign ^ b.bits.sign;
            uint64_t resExp = a.bits.exponent - b.bits.exponent + BIAS;
            uint64_t resMant = (mantA << 31) / mantB; 

            while ((resMant & (1ULL << 31)) == 0 && resMant != 0) { resMant <<= 1; resExp--; }

            registers[top - 1].bits.sign = resSign;
            registers[top - 1].bits.exponent = resExp;
            registers[top - 1].bits.mantissa = resMant & 0x7FFFFFFF;
            
            top--; 
            cout << " -> DIV" << endl; 
        } 
    }
    
    void Swap() { 
        if(top >= 1) { 
            swap(registers[top], registers[top - 1]); 
            cout << "CMD: SWAP" << endl; 
        } 
    }

    void PrintTop() {
        if (top >= 0) {
            PrintBinaryFormat(Unpack(registers[top]), "Stack TOP");
        }
    }
};

int main() {

    // 1. Аналіз бітів
    cout << "--- PART 1 ---" << endl;
    PrintBinaryFormat(0.0, "Zero");
    PrintBinaryFormat(1.0, "One");
    PrintBinaryFormat(numeric_limits<double>::infinity(), "+Inf");
    PrintBinaryFormat(NAN, "NaN");

    cout << "Enter a number to analyze its bits (e.g. 12.5): ";
    double userInput;
    if (cin >> userInput) {
        PrintBinaryFormat(userInput, "User Input");
    }

    // 2. Емулятор
    cout << "--- PART 2 ---" << endl;
    double a, b;
    cout << "Enter a: "; cin >> a;
    cout << "Enter b: "; cin >> b;

    Coprocessor cpu;

    // F(a,b) = (b-a)/(b+4a) - b/a
    // Права частина b/a
    cpu.Load(b);
    cpu.Load(a);
    cpu.Div();
    cpu.PrintTop();
    // Чисельник b-a
    cpu.Load(b);
    cpu.Load(a);
    cpu.Sub();
    cpu.PrintTop(); 
    //Знаменник b+4a
    cpu.Load(b);
    cpu.Load(a);
    cpu.Load(4.0);
    cpu.Mult();
    cpu.Add();
    cpu.PrintTop();
    // Лівий дріб
    cpu.Div();
    cpu.PrintTop();
    // Фінальний результат
    cpu.Swap();
    cpu.Sub();  
    cout << "FINAL RESULT:" << endl;
    cpu.PrintTop();

    return 0;
}
