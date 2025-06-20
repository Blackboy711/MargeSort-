#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void fillarr(int** matrix, int n, int m) {
    srand(time(0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matrix[i][j] = rand() % 10;
}

void showarr(int** matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

void one(int** matrix, int* array, int n, int m) {
    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            array[index++] = matrix[i][j];
}

void doublee(int* array, int** matrix, int n, int m) {
    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matrix[i][j] = array[index++];
}

void merge(int* arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int* L = new int[n1], * R = new int[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] < R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int* arr, int l, int r) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;
    mergeSort(arr, l, mid);
    mergeSort(arr, mid + 1, r);
    merge(arr, l, mid, r);
}

int main() {
    const int n = 5, m = 5;
    setlocale(LC_ALL, "RU");

    int** matrix = new int* [n];
    for (int i = 0; i < n; i++)
        matrix[i] = new int[m];

    fillarr(matrix, n, m);
    cout << "Невiдсортована матриця" << endl;
    showarr(matrix, n, m);

    for (int i = 0; i < n; i++)
        mergeSort(matrix[i], 0, m - 1);

    cout << "Окремо вiдсортована матриця по рядках" << endl;
    showarr(matrix, n, m);

    int* flatArray = new int[n * m];
    one(matrix, flatArray, n, m);
    mergeSort(flatArray, 0, n * m - 1);
    doublee(flatArray, matrix, n, m);

    cout << "Вiдсортована матриця" << endl;
    showarr(matrix, n, m);

    for (int i = 0; i < n; i++)
        delete[] matrix[i];
    delete[] matrix;
    delete[] flatArray;

    return 0;
}
