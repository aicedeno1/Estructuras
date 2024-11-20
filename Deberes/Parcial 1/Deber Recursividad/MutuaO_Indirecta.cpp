#include <iostream>
using namespace std;

bool even(int n);
bool odd(int n);

bool even(int n) {
    if (n == 0)
        return true;
    else
        return odd(n - 1);
}

bool odd(int n) {
    if (n == 0)
        return false;
    else
        return even(n - 1);
}

int main() {
    int num;    
    cout << "Ingrese un numero: ";
    cin >> num;
    cout << "Es " << num << " par? " << (even(num) ? "Si" : "No") << endl;
    return 0;
}
