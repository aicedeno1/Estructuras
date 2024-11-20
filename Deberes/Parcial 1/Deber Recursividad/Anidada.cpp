#include <iostream>
using namespace std;

int ackermann(int m, int n) {
    if (m == 0) 
        return n + 1;
    else if (m > 0 && n == 0) 
        return ackermann(m - 1, 1);
    else 
        return ackermann(m - 1, ackermann(m, n - 1)); // Llamada recursiva anidada
}

int main() {
    int m , n ;
    cout << "Ingrese el valor de m: "<< endl;
    cin>> n;
     cout << "Ingrese el valor de n: "<< endl;
    cin>> m;
    cout << "Ackermann(" << m << ", " << n << ") = " << ackermann(m, n) << endl;
    return 0;
}
