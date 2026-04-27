/*
 * ============================================================
 *  Scientific Calculator — C++ Console Application
 *  Author : Himal Bhandari
 *  Course : Project Build a scientific calculator |  Kyungdong University
 *  Date   : 2026
 * ============================================================
 *
 *  Features:
 *    Basic  : +  -  *  /  %  (with div-by-zero guard)
 *    Power  : x^y, sqrt, cbrt
 *    Trig   : sin, cos, tan, asin, acos, atan  (deg & rad)
 *    Log    : log10, ln (log base-e), log2
 *    Other  : abs, ceil, floor, factorial, nCr, nPr
 *    Memory : MS (store), MR (recall), MC (clear), M+ (add)
 * ============================================================
 */

 

 #include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <string>
#include <stdexcept>

// ─── Constants ────────────────────────────────────────────
const double PI    = acos(-1.0);
const double E_NUM = exp(1.0);

// ─── Helper Utilities ────────────────────────────────────

/* Clear the input buffer after a bad read */
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/* Safely read a double — keeps asking until valid */
double readDouble(const std::string& prompt) {
    double val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) return val;
        std::cout << "  [!] Invalid input. Please enter a number.\n";
        clearInputBuffer();
    }
}

/* Safely read an integer */
long long readInt(const std::string& prompt) {
    long long val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) return val;
        std::cout << "  [!] Invalid input. Please enter an integer.\n";
        clearInputBuffer();
    }
}

/* Convert degrees to radians */
double toRad(double deg) { return deg * PI / 180.0; }

/* Factorial (iterative, up to ~20 to avoid overflow) */
long long factorial(int n) {
    if (n < 0)  throw std::invalid_argument("Factorial undefined for negative numbers.");
    if (n > 20) throw std::overflow_error("Input too large (max 20).");
    long long result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}

/* Combination nCr */
double combination(int n, int r) {
    if (r < 0 || r > n) throw std::invalid_argument("Invalid r: must be 0 ≤ r ≤ n.");
    return static_cast<double>(factorial(n)) / (factorial(r) * factorial(n - r));
}

/* Permutation nPr */
double permutation(int n, int r) {
    if (r < 0 || r > n) throw std::invalid_argument("Invalid r: must be 0 ≤ r ≤ n.");
    return static_cast<double>(factorial(n)) / factorial(n - r);
}

// ─── Display Helpers ────────────────────────────────────

void printSeparator(char c = '-', int len = 50) {
    std::cout << std::string(len, c) << "\n";
}

void printResult(double result) {
    std::cout << "\n  ► Result = "
              << std::setprecision(10) << result << "\n\n";
}

void printError(const std::string& msg) {
    std::cout << "\n  [ERROR] " << msg << "\n\n";
}
// ─── Menu Printers ──────────────────────────────────────

void printMainMenu() {
    printSeparator('=');
    std::cout << "   SCIENTIFIC CALCULATOR  v1.0\n";
    std::cout << "   Kyungdong University — CS Dept.\n";
    printSeparator('=');
    std::cout << "  [1]  Basic Arithmetic\n";
    std::cout << "  [2]  Power & Roots\n";
    std::cout << "  [3]  Trigonometry\n";
    std::cout << "  [4]  Logarithms\n";
    std::cout << "  [5]  Combinatorics (nCr / nPr / Factorial)\n";
    std::cout << "  [6]  Rounding & Absolute Value\n";
    std::cout << "  [7]  Memory Functions\n";
    std::cout << "  [0]  Exit\n";
    printSeparator();
    std::cout << "  Choice: ";
}

// ─── Operation Modules ──────────────────────────────────

void basicArithmetic() {
    printSeparator();
    std::cout << "  BASIC ARITHMETIC\n";
    std::cout << "  Operators:  +  -  *  /  %\n";
    printSeparator();

    double a = readDouble("  Enter first number  : ");
    char   op;
    std::cout << "  Enter operator (+/-/*//%): ";
    std::cin >> op;
    double b = readDouble("  Enter second number : ");

    try {
        double result = 0;
        switch (op) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/':
                if (b == 0) throw std::runtime_error("Division by zero.");
                result = a / b;
                break;
            case '%': {
                if (b == 0) throw std::runtime_error("Modulo by zero.");
                long long ia = static_cast<long long>(a);
                long long ib = static_cast<long long>(b);
                result = static_cast<double>(ia % ib);
                break;
            }
            default:
                throw std::invalid_argument("Unknown operator.");
        }
        printResult(result);
    } catch (const std::exception& e) {
        printError(e.what());
    }
}

void powerAndRoots() {
    printSeparator();
    std::cout << "  POWER & ROOTS\n";
    printSeparator();
    std::cout << "  [1] x ^ y\n";
    std::cout << "  [2] Square Root  √x\n";
    std::cout << "  [3] Cube Root    ∛x\n";
    std::cout << "  Choice: ";

    int ch; std::cin >> ch;
    try {
        switch (ch) {
            case 1: {
                double x = readDouble("  Base    x : ");
                double y = readDouble("  Exponent y: ");
                printResult(pow(x, y));
                break;
            }
            case 2: {
                double x = readDouble("  Enter x : ");
                if (x < 0) throw std::domain_error("Square root of negative number is undefined in real numbers.");
                printResult(sqrt(x));
                break;
            }
            case 3: {
                double x = readDouble("  Enter x : ");
                printResult(cbrt(x));
                break;
            }
            default: printError("Invalid choice.");
        }
    } catch (const std::exception& e) {
        printError(e.what());
    }
}

void trigonometry() {
    printSeparator();
    std::cout << "  TRIGONOMETRY\n";
    printSeparator();
    std::cout << "  [1] sin(x)    [2] cos(x)    [3] tan(x)\n";
    std::cout << "  [4] asin(x)   [5] acos(x)   [6] atan(x)\n";
    std::cout << "  Choice: ";

    int ch; std::cin >> ch;
    if (ch < 1 || ch > 6) { printError("Invalid choice."); return; }

    // For inverse trig, input is the ratio; for direct, ask for angle
    bool isInverse = (ch >= 4);
    std::string unit = "";
    double angleRad  = 0;
    double val       = 0;

    if (!isInverse) {
        std::cout << "  Angle in [1] Degrees  [2] Radians: ";
        int u; std::cin >> u;
        double angle = readDouble("  Enter angle: ");
        angleRad = (u == 1) ? toRad(angle) : angle;
    } else {
        val = readDouble("  Enter value (ratio): ");
    }

    try {
        double result = 0;
        switch (ch) {
            case 1: result = sin(angleRad); break;
            case 2: result = cos(angleRad); break;
            case 3:
                if (cos(angleRad) == 0) throw std::domain_error("tan undefined at 90°/270°.");
                result = tan(angleRad);
                break;
            case 4:
                if (val < -1 || val > 1) throw std::domain_error("asin domain: [-1, 1].");
                result = asin(val) * 180.0 / PI;  // return degrees
                std::cout << "  (Result in degrees)\n";
                break;
            case 5:
                if (val < -1 || val > 1) throw std::domain_error("acos domain: [-1, 1].");
                result = acos(val) * 180.0 / PI;
                std::cout << "  (Result in degrees)\n";
                break;
            case 6:
                result = atan(val) * 180.0 / PI;
                std::cout << "  (Result in degrees)\n";
                break;
        }
        printResult(result);
    } catch (const std::exception& e) {
        printError(e.what());
    }
}

void logarithms() {
    printSeparator();
    std::cout << "  LOGARITHMS\n";
    printSeparator();
    std::cout << "  [1] log10(x)  — Common log\n";
    std::cout << "  [2] ln(x)     — Natural log\n";
    std::cout << "  [3] log2(x)   — Binary log\n";
    std::cout << "  [4] log_b(x)  — Custom base\n";
    std::cout << "  Choice: ";

    int ch; std::cin >> ch;
    try {
        double x = readDouble("  Enter x: ");
        if (x <= 0) throw std::domain_error("Logarithm defined only for x > 0.");

        switch (ch) {
            case 1: printResult(log10(x)); break;
            case 2: printResult(log(x));   break;
            case 3: printResult(log2(x));  break;
            case 4: {
                double b = readDouble("  Enter base b: ");
                if (b <= 0 || b == 1) throw std::domain_error("Base must be > 0 and ≠ 1.");
                printResult(log(x) / log(b));
                break;
            }
            default: printError("Invalid choice.");
        }
    } catch (const std::exception& e) {
        printError(e.what());
    }
}

void combinatorics() {
    printSeparator();
    std::cout << "  COMBINATORICS\n";
    printSeparator();
    std::cout << "  [1] n!    Factorial\n";
    std::cout << "  [2] nCr   Combination\n";
    std::cout << "  [3] nPr   Permutation\n";
    std::cout << "  Choice: ";

    int ch; std::cin >> ch;
    try {
        switch (ch) {
            case 1: {
                int n = static_cast<int>(readInt("  Enter n: "));
                std::cout << "\n  ► " << n << "! = " << factorial(n) << "\n\n";
                break;
            }
            case 2: {
                int n = static_cast<int>(readInt("  Enter n: "));
                int r = static_cast<int>(readInt("  Enter r: "));
                printResult(combination(n, r));
                break;
            }
            case 3: {
                int n = static_cast<int>(readInt("  Enter n: "));
                int r = static_cast<int>(readInt("  Enter r: "));
                printResult(permutation(n, r));
                break;
            }
            default: printError("Invalid choice.");
        }
    } catch (const std::exception& e) {
        printError(e.what());
    }
}

void roundingAndAbs() {
    printSeparator();
    std::cout << "  ROUNDING & ABSOLUTE VALUE\n";
    printSeparator();
    std::cout << "  [1] |x|   Absolute value\n";
    std::cout << "  [2] ceil  Ceiling\n";
    std::cout << "  [3] floor Floor\n";
    std::cout << "  [4] round Round\n";
    std::cout << "  Choice: ";

    int ch; std::cin >> ch;
    double x = readDouble("  Enter x: ");

    switch (ch) {
        case 1: printResult(fabs(x));  break;
        case 2: printResult(ceil(x));  break;
        case 3: printResult(floor(x)); break;
        case 4: printResult(round(x)); break;
        default: printError("Invalid choice.");
    }
}

void memoryFunctions(double& memory) {
    printSeparator();
    std::cout << "  MEMORY  (current: " << memory << ")\n";
    printSeparator();
    std::cout << "  [1] MS  — Memory Store\n";
    std::cout << "  [2] MR  — Memory Recall\n";
    std::cout << "  [3] MC  — Memory Clear\n";
    std::cout << "  [4] M+  — Memory Add\n";
    std::cout << "  Choice: ";

    int ch; std::cin >> ch;
    switch (ch) {
        case 1: {
            double v = readDouble("  Value to store: ");
            memory = v;
            std::cout << "  Stored " << memory << " in memory.\n\n";
            break;
        }
        case 2:
            std::cout << "  Memory value: " << memory << "\n\n";
            break;
        case 3:
            memory = 0;
            std::cout << "  Memory cleared.\n\n";
            break;
        case 4: {
            double v = readDouble("  Value to add: ");
            memory += v;
            std::cout << "  Memory is now: " << memory << "\n\n";
            break;
        }
        default: printError("Invalid choice.");
    }
}

// ─── Main ───────────────────────────────────────────────

int main() {
    double memory = 0.0;
    int    choice = -1;

    std::cout << std::fixed << std::setprecision(6);

    while (choice != 0) {
        printMainMenu();
        if (!(std::cin >> choice)) {
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: basicArithmetic();           break;
            case 2: powerAndRoots();             break;
            case 3: trigonometry();              break;
            case 4: logarithms();                break;
            case 5: combinatorics();             break;
            case 6: roundingAndAbs();            break;
            case 7: memoryFunctions(memory);     break;
            case 0:
                std::cout << "\n  Goodbye! Keep coding. 👋\n\n";
                break;
            default:
                printError("Invalid option. Choose 0–7.");
        }
    }

    return 0;
}