//TC1031.2
//Act 1.2 - Algoritmos de Búsqueda y Ordenamiento
//Daniela Hernández y Hernández   A01730397
//10/09/2020

#include <iostream>
#include <vector>
using namespace std;

//Variables globales para contar número de comparaciones
long countM = 0, countS, countB;

// ----------------- ordenamiento por intercambio ----------------------------
// Complejidad cuadrática O(n^2)
void ordenaIntercambio(vector<long> &v) {
  long count = 0;
  vector<long> v1 = v;
  long aux;
  for(long i = 0; i <= v1.size()-2; i++) {
    for(long j = i+1; j <= v1.size()-1; j++) {
       count++;
      if (v1[j] < v1[i]) {
        aux = v1[i];
        v1[i] = v1[j];
        v1[j] = aux;
      }
    }
  }
  cout << count;
}

// ----------------- ordenamiento burbuja ------------------------------------
//Complejidad cuadrática O(n^2); mejor caso: complejidad lineal O(n)
void ordenaBurbuja(vector<long> &v) {
  vector<long> v1 = v;
  long count = 0;
  int aux;
  bool flag = true;

  for(long i = 0; i < v1.size()-1; i++) {
    if(flag) {
      flag = false;
      for(long j = 0; j < v1.size()-1-i; j++) {
        count++;
        if(v1[j+1] < v1[j]){
          aux = v1[j+1];
          v1[j+1] = v1[j];
          v1[j] = aux;
          flag = true;
        }
      }
    }
  }
  cout << count;
}


// ---------------- ordenamiento merge ---------------------------------------
// Complejidad n-logarítmica O(nlog(n))
void merge(vector<long> &v1, long start, long middle, long end) {
  long i, j, k;
  long n1 = middle - start + 1;
  long n2 = end - middle;
  vector<long> L, R;

  for (i = 0; i < n1; i++) L.push_back(v1[start + i]);
  for (j = 0; j < n2; j++) R.push_back(v1[middle + 1 + j]);

  i = 0;
  j = 0;
  k = start;

  while (i < n1 && j < n2) {
    countM++;
    if (L[i] <= R[j]) {
      v1[k] = L[i];
      i++;
    } else {
      v1[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    v1[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    v1[k] = R[j];
    j++;
    k++;
  }
}


void ordenaMerge(vector<long> &v1, long start, long end) {
  if (start < end) {
    long middle = start + (end - start) / 2;
    ordenaMerge(v1, start, middle);
    ordenaMerge(v1, middle + 1, end);
    merge(v1, start, middle, end);
  }
}


//-------------------------- búsquedas ---------------------------------------
//Complejidad lineal O(n)
long busqSecuencial(vector<long> v, long dat) {
  countS = 0;
  for(long i = 0; i < v.size(); i++) {
    countS++;
    if(v[i] == dat) return i;
  }
  return -1;
}

//Complejidad logarítmica O(log(n))
long busqBinaria(vector<long> v, long dat) {
  long start = 0, end = v.size()-1, centre, centreValue;
  countB = 0;
  while(start <= end) {
    centre = (start + end)/2;
    centreValue = v[centre];
    countB++;
    if(dat == centreValue) return centre;
    else if(dat < centreValue) end = centre - 1;
    else start = centre + 1;
  }
  return -1;
}


// ----------------------------- main ---------------------------------------
int main() {
  vector<long> vector;
  long vSize, element, searchN, searchData;
  cin >> vSize;

  for(long i = 0; i < vSize; i++) {
    cin >> element;
    vector.push_back(element);
  }

  ordenaIntercambio(vector);
  cout << " ";
  ordenaBurbuja(vector);
  cout << " ";
  ordenaMerge(vector, 0, vector.size()-1);
  cout << countM << endl;

  cin >> searchN;

  for(long i = 0; i < searchN; i++) {
    cin >> searchData;
    busqSecuencial(vector, searchData);
    cout << busqBinaria(vector, searchData) << " " << countS << " " << countB << endl;
  }

  return 0;
}
