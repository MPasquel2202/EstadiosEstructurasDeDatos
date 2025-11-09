#include <iostream>
using namespace std;

void contarHasta(int n, int limite) {
    if (n > limite) return;
    cout << n << " ";
    contarHasta(n + 1, limite); // última instrucción (tail recursion)
}

int main() {
    cout << "Recursividad de Cola:\n";
    contarHasta(1, 5);
    cout << endl;
    return 0;
}
