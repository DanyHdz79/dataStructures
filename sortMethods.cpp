#include <iostream>
using namespace std;

//O(n^2)
void intercambioSort(int arr[], int size){
  int aux;
  for(int i = 0; i <= size-2; i++){
    for(int j = i+1; j <= size-1; j++){
      if(arr[i] > arr[j]){
        aux = arr[i];
        arr[i] = arr[j];
        arr[j] = aux;
      }
    }
  }
}

int intercambioSortRecurs(int arr[], int n, int start){
  int aux;
  if(start == n-1){
    return 0;
  }
  for(int i = start; i < n; i++){
    if(arr[start] > arr[i]){
      aux = arr[i];
      arr[i] = arr[start];
      arr[start] = aux;
    }
  }
  return intercambioSortRecurs(arr, n ,start+1);
}


//O(n^2); mejor caso: //O(n)
void bubbleSort(int arr[], int size){
  int aux;
  bool flag;
  if(!flag){
    for(int i = 0; i < size-1; i++){
      flag = false;
      for(int j = 0; j < size-1-i; j++){
        if(arr[j+1] < arr[j]){
          aux = arr[j+1];
          arr[j+1] = arr[j];
          arr[j] = aux;
          flag = true;
        }
      }
    }
  }
}


int bubbleSortRecurs(int arr[], int n){
  int aux;
  if(n == 0){
    return 0;
  }
  for(int i = 0; i < n-1; i++){
    if(arr[i+1] < arr[i]){
      aux = arr[i+1];
      arr[i+1] = arr[i];
      arr[i] = aux;
  }
 }
 return bubbleSortRecurs(arr, n-1);
}



//O(n^2)
void selectionSort(int arr[], int size){
  int aux;
  int iMin;
  for(int i = 0; i < size-1; i++){
    iMin = i;
    for(int j = i+1; j < size; j++){
      if(arr[j] < arr[iMin]){
        iMin = j;
      }
    }
    if(i != iMin){
      aux = arr[iMin];
      arr[iMin] = arr[i];
      arr[i] = aux;
    }
  }
}


int selectionSortRecurs(int arr[], int n, int start){
  int aux;
  int iMin = start;
  if(n == start){
    return 0;
  }
  for(int i = start+1; i < n; i++){
    if(arr[i] < arr[iMin]){
      iMin = i;
    }
  }
  if(start != iMin){
    aux = arr[iMin];
    arr[iMin] = arr[start];
    arr[start] = aux;
  }
  return selectionSortRecurs(arr, n, start+1);
}



//O(n^2)
void insertionSort(int arr[], int n){
  int aux;
  for(int i = 1; i < n; i++){
    int j = i;
    aux = arr[i];
    while(j > 0 && aux < arr[j-1]){
      arr[j] = arr[j-1];
      j -= 1;
    }
    arr[j] = aux;
  }
}


void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];  /* create temp arrays */
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


//O(nlog(n))
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}




//O(nlog(n)); peor caso: O(n^2)
int partition (int arr[], int low, int high) {
  int pivot = arr[high]; // pivot
  int i = (low - 1); // Index of smaller element

  for (int j = low; j <= high - 1; j++) {
    // If current element is smaller than the pivot
    if (arr[j] < pivot) {
      i++; // increment index of smaller element
      int t = arr[i];
      arr[i] = arr[j];
      arr[j] = t;
    }
  }
  int w = arr[i+1];
  arr[i+1] = arr[high];
  arr[high] = w;
  return (i + 1);
}


void quickSort(int arr[], int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}


void print(int arr[], int size){
  for(int i = 0; i < size; i++){
    cout << arr[i] << " ";
  }
  cout << endl;
}


int main(){
  int arr[] = {5,10,1,3,7,4};
  // //Empezar reloj
  // auto start = chrono::high_resolution_clock::now();
  // ios_base::sync_with_stdio(false);
  // //Ejecutar funcion
  quickSort(arr,0,5);
  print(arr,6);
  //Detener reloj
  // auto end = chrono::high_resolution_clock::now();
  // double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  // time_taken *= 1e-9;
  // cout << "Time taken by program is : " << fixed<< time_taken << setprecision(9)<< " sec" << endl;


  return 0;
}
