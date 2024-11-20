#include <iostream>
using namespace std;

int factorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

int main() {
    int num;
    cout << "Ingrese el numero que quiere realizar el factorial"<< endl;
    cin >> num;
    cout << "Factorial de es: " << factorial(num) << endl;
    return 0;
}
