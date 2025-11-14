#include <iostream>
using namespace std;

template <typename T>
class Operaciones {
private:
    T a, b;

public:
    Operaciones(T a, T b) : a(a), b(b) {}

    T suma() {
        return a + b;
    }

    T resta() {
        return a - b;
    }

    T multiplicacion() {
        return a * b;
    }

    T division() {
        if (b != 0) {
            return a / b;
        } else {
            throw runtime_error("Division by zero");
        }
    }
};

int main() {
    Operaciones<int> opInt(10, 5);
    cout << "Suma: " << opInt.suma() << endl;
    cout << "Resta: " << opInt.resta() << endl;
    cout << "Multiplicacion: " << opInt.multiplicacion() << endl;
    cout << "Division: " << opInt.division() << endl;








































































    

    Operaciones<double> opDouble(10.5, 2.5);
    cout << "Suma: " << opDouble.suma() << endl;
    cout << "Resta: " << opDouble.resta() << endl;
    cout << "Multiplicacion: " << opDouble.multiplicacion() << endl;
    cout << "Division: " << opDouble.division() << endl;

    return 0;
}