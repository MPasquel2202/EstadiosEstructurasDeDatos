#include <iostream>
using namespace std;

int factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1); // una sola llamada recursiva
}

int main() {
    cout << "Recursividad Lineal:\n";
    int n = 5;
    cout << "Factorial de " << n << " = " << factorial(n) << endl;
    return 0;
}
