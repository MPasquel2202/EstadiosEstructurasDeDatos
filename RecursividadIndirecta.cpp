#include <iostream>
using namespace std;

void B(int n);

void A(int n) {
    if (n <= 0) return;
    cout << "A: " << n << endl;
    B(n - 1);
}

void B(int n) {
    if (n <= 0) return;
    cout << "B: " << n << endl;
    A(n - 2);
}

int main() {
    cout << "Recursividad Indirecta:\n";
    A(5);
    return 0;
}
