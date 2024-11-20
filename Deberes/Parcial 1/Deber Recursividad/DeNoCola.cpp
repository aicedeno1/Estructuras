#include <iostream>
using namespace std;

int sum_digits(int n) {
    if (n == 0)
        return 0;
    else
        return (n % 10) + sum_digits(n / 10); // La llamada recursiva no es la última operación.
}

int main() {
    int number;
    cout << "digite el termino para la suma de digitos:";
    cin >>number;
    cout << "Suma de dígitos de " << number << " es: " << sum_digits(number) << endl;
    return 0;
}
