#include "logic.h"

bool Logic::isPrime(int number) {
    if (number <= 1) return false;
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) return false;
    }
    return true;
}

int Logic::add(int a, int b) { return a + b; }
int Logic::subtract(int a, int b) { return a - b; }
int Logic::multiply(int a, int b) { return a * b; }

double Logic::divide(int a, int b) {
    if (b == 0) throw std::runtime_error("Division by zero");
    return static_cast<double>(a) / b;
}