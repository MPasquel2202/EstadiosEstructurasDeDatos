#include <iostream>
using namespace std;

int sumaHasta(int n) {
    if (n == 0) return 0;
    return n + sumaHasta(n - 1); // operaciones después de la llamada
}

int main() {
    cout << "Recursividad No de Cola:\n";
    int n = 5;
    cout << "Suma de 1 a " << n << " = " << sumaHasta(n) << endl;
    return 0;
}
