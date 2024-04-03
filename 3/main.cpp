#include <iostream>

enum Search { Jump, Fib, Inter };

int compN;

int jumpSearch(int arr[], int n, int x)
{
    int step = sqrt(n);

    int prev = 0;
    while (arr[std::min(step, n) - 1] < x) {
        compN++;
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
        
    }

    while (arr[prev] < x) {
        compN++;
        prev++;

        if (prev == std::min(step, n))
            return -1;
    }
    
    compN++;
    if (arr[prev] == x)
        return prev;

    return -1;
}

int fibonacciSearch(int arr[], int n, int x)
{
    int f2 = 0;
    int f1 = 1;
    int f = f2 + f1;

    while (f < n) {
        f2 = f1;
        f1 = f;
        f = f2 + f1;
    }

    int offset = -1;

    while (f > 1) {
        int i = std::min(offset + f2, n - 1);

        compN++;
        if (arr[i] < x) {
            f = f1;
            f1 = f2;
            f2 = f - f1;
            offset = i;
        } else if (arr[i] > x) {
            compN++;
            f = f2;
            f1 = f1 - f2;
            f2 = f - f1;
        } else
            return i;
    }

    compN++;
    if (f1 && arr[offset + 1] == x)
        return offset + 1;

    return -1;
}

int interpolationSearch(int arr[], int low, int high, int x) {
    int pos;

    if (low <= high && x >= arr[low] && x <= arr[high]) {

        pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (x - arr[low]));

        compN++;
        if (arr[pos] == x)
            return pos;

        compN++;
        if (arr[pos] < x)
            return interpolationSearch(arr, pos + 1, high, x);

        compN++;
        if (arr[pos] > x)
            return interpolationSearch(arr, low, pos - 1, x);
    }
    return -1;
}

int getMax(int* arr, int N) {
    int tmp = arr[0];
    for (int i = 1; i < N; i++) {
        if (tmp < arr[i])
            tmp = arr[i];
    }
    return tmp;
}

void countSort(int* arr, int N, int exp) {
    int* output = new int[N];
    int count[10] = { 0 };

    for (int i = 0; i < N; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = N - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < N; i++)
        arr[i] = output[i];
}

void radixSort(int* arr, int N) {
    int max = getMax(arr, N);

    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, N, exp);
}

void genArr(int arr[], int n) {
    int tmp;

    for (int i = 0; i < n; i++) {
        tmp = rand();
        if (tmp % 2 == 0)
            arr[i] = tmp;
        else
            arr[i] = tmp - 1;
    }

    radixSort(arr, n);
}

void countCompN(int arr[], int n, int x, Search s) {
    int res = -1;

    switch (s) {
    case Jump:
        compN = 0;
        res = jumpSearch(arr, n, x);
        break;
    case Fib:
        compN = 0;
        res = fibonacciSearch(arr, n, x);
        break;
    case Inter:
        compN = 0;
        res = interpolationSearch(arr, 0, n - 1, x);
        break;
    }

    if (res == -1) {
        std::cout << "Unsuccessfull search. " << compN << " comparisons." << std::endl;
    } else {
        std::cout << "Successfull search. " << compN << " comparisons." << std::endl;
    }
}

int main(int argc, char** argv) {
    const int n = 500, step = 9;
    int *arr = new int[n];
    int x;
    // Шаг step. Числа от step до step * n
    genArr(arr, n);

    countCompN(arr, n, x, Jump);
    countCompN(arr, n, x, Fib);
    countCompN(arr, n, x, Inter);

    x = 2565;
    countCompN(arr, n, x, Jump);
    countCompN(arr, n, x, Fib);
    countCompN(arr, n, x, Inter);

    x = 4356;
    countCompN(arr, n, x, Jump);
    countCompN(arr, n, x, Fib);
    countCompN(arr, n, x, Inter);
}