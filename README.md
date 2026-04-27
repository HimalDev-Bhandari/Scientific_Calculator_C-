# Scientific_Calculator_C-
Created modern scientific calculator using C++
# 🧮 Scientific Calculator — C++

> A console-based scientific calculator built with modern C++ as part of my CS coursework at **Kyungdong University**.

---

## 📋 Table of Contents
- [Features](#-features)
- [Getting Started](#-getting-started)
- [Usage](#-usage)
- [Project Structure](#-project-structure)
- [Concepts Used](#-concepts-used)
- [Author](#-author)

---

## ✨ Features

| Category | Operations |
|---|---|
| **Basic Arithmetic** | Addition, Subtraction, Multiplication, Division, Modulo |
| **Power & Roots** | `x^y`, Square Root `√x`, Cube Root `∛x` |
| **Trigonometry** | `sin`, `cos`, `tan`, `asin`, `acos`, `atan` (degrees & radians) |
| **Logarithms** | `log10`, `ln`, `log2`, custom base `log_b(x)` |
| **Combinatorics** | Factorial `n!`, Combination `nCr`, Permutation `nPr` |
| **Rounding** | `abs`, `ceil`, `floor`, `round` |
| **Memory** | MS (Store), MR (Recall), MC (Clear), M+ (Add) |

---

## 🚀 Getting Started

### Prerequisites
- A C++ compiler: `g++` (GCC), `clang++`, or MSVC
- Recommended: **g++ 11+**

### Compile & Run

```bash
# Clone the repository
git clone https://github.com/<your-username>/scientific-calculator-cpp.git
cd scientific-calculator-cpp

# Compile
g++ -std=c++17 -Wall -o calculator calculator.cpp -lm

# Run
./calculator
```

> **Windows (MinGW):** Use `calculator.exe` instead of `./calculator`

---

## 📖 Usage

After running the program you'll see a menu:
