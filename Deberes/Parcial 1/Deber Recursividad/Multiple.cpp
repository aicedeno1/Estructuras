#include <iostream>
using namespace std;

int fibonacci(int n) {
    if (n <= 1)
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n;
    cout << "Escriba el numero de la serie fibonacci que desea";
    cin >> n;
    cout << "Fibonacci posicion " <<   n  << " es: " << fibonacci(n) << endl;
    return 0;
}
