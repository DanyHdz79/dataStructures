//TC1031.2
//Act 1.1 - Funciones iterativas, recursivas y su complejidad
//Daniela Hernández y Hernández   A01730397
//28/08/2020

#include <iostream>
using namespace std;

//Complejidad lineal O(n):
//el ciclo se repetirá n veces, dependiendo del input.
int sumaIterativa(int n) {
    int sum = 0;
    for(int i = 1; i <= n; i++) sum += i;
    return sum;
}

//Complejidad lineal O(n):
//la llamada recursiva se realizará n veces, hasta que n == 1.
int sumaRecursiva(int n) {
    if(n == 1) return 1;
    return n + sumaRecursiva(n-1);
}

//Complejidad constante O(1):
//al ser una operación, sólo se ejecutará una vez.
int sumaDirecta(int n) {
    return (n*(n+1))/2;
}

int main() {
    int n;
    cin >> n;

    for(int i = 0; i < n; i++) {
        int num;
        cin >> num;
        cout << sumaIterativa(num) << " " << sumaRecursiva(num) << " " << sumaDirecta(num) << endl;
    }

    return 0;
}
