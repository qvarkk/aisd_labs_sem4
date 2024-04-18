#include <iostream>

enum Search { Jump1, Jump2, Fib, Inter };

int compN;

int oneLvlJumpSearch(int arr[], int n, int x, int step) {
    int prev = 0;
    int fixStep = step;

    while (compN++, arr[std::min(step, n) - 1] < x) {
        prev = step;
        step += fixStep;
        if (compN++, prev >= n)
            return -1;

    }

    while (compN++, arr[prev] < x) {
        prev++;

        if (compN++, prev == std::min(step, n))
            return -1;
    }

    if (compN++, arr[prev] == x)
        return prev;

    return -1;
}

int oneLvlJumpSearch(int arr[], int n, int x) {
    return oneLvlJumpSearch(arr, n, x, sqrt(n));
}

int twoLvlJumpSearch(int arr[], int n, int x) {
    int step1 = (int)sqrt(n), step2 = (int)sqrt(step1);
    int prev1 = 0, prev2 = step1;

    while (compN++, arr[std::min(prev2, n) - 1] < x) {
        prev1 = prev2;
        prev2 += step1;
        if (compN++, prev1 >= n)
            return -1;
    }

    prev2 = prev1 + step2;
    int end = prev1 + step1;

    while (compN++, arr[std::min(prev2, end) - 1] < x) {
        prev1 = prev2;
        prev2 += step2;
        if (compN++, prev1 >= end)
            return -1;
    }

    while (compN++, arr[prev1] < x) {
        prev1++;
        if (compN++, prev1 == std::min(prev2, end))
            return -1;
    }

    if (compN++, arr[prev1] == x)
        return prev1;

    return -1;
}

int jumpSearch(int arr[], int n, int x, int lvl) {
    if (lvl == 1)
        return oneLvlJumpSearch(arr, n, x);
    else if (lvl == 2)
        return twoLvlJumpSearch(arr, n, x);

    return -1;
}

int fibonacciSearch(int arr[], int n, int x) {
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

        if (compN++, arr[i] < x) {
            f = f1;
            f1 = f2;
            f2 = f - f1;
            offset = i;
        } else if (compN++, arr[i] > x) {
            f = f2;
            f1 = f1 - f2;
            f2 = f - f1;
        } else
            return i;
    }

    if (compN++, f1 && arr[offset + 1] == x)
        return offset + 1;

    return -1;
}

int interpolationSearch(int arr[], int n, int x) {
    int pos, low = 0, high = n - 1;

    while (low <= high && x >= arr[low] && x <= arr[high] && high != low) {

        pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (x - arr[low]));

        if (compN++, arr[pos] == x)
            return pos;
        else {
            if (compN++, arr[pos] < x)
                low = pos + 1;
            else
                high = pos - 1;
        }
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

int countCompN(int arr[], int n, int x, Search s) {
    compN = 0;

    switch (s) {
    case Jump1:
        jumpSearch(arr, n, x, 1);
        break;
    case Jump2:
        jumpSearch(arr, n, x, 2);
        break;
    case Fib:
        fibonacciSearch(arr, n, x);
        break;
    case Inter:
        interpolationSearch(arr, n, x);
        break;
    }

    return compN;
}

void getAvg(int arr[], Search s, int iters = 100, int unsuccess = 0) {
    int total = 0;
    for (int n = 10000; n <= 100000; n += 10000) {
        arr = new int[n];
        for (int j = 0; j < iters; j++) {
            genArr(arr, n);
            int x = arr[(int)((double)rand() / RAND_MAX * n)] + unsuccess;
            total += countCompN(arr, n, x, s);
        }
        delete[] arr;
        std::cout << total / iters << std::endl;
        total = 0;
    }
    std::cout << std::endl;
}

void getMod(int arr[], int iters = 100) {
    int total = 0;
    for (int n = 100; n <= 500; n += 100) {
        std::cout << "Array size: " << n << std::endl;
        arr = new int[n];
        for (int s = 1; s <= n / 2; s++) {
            for (int i = 0; i < iters; i++) {
                genArr(arr, n);
                int x = arr[(int)((double)rand() / RAND_MAX * n)];
                oneLvlJumpSearch(arr, n, x, s);
                total += compN;
                compN = 0;
            }
            std::cout << total / iters << std::endl;
            total = 0;
        }
        std::cout << "\n\n" << std::endl;
    }
}

int main(int argc, char** argv) {
    int *arr = nullptr;

    srand((unsigned)time(NULL));

    getAvg(arr, Jump1, 500, 0);
    getAvg(arr, Jump2, 500, 0);
    getAvg(arr, Fib, 500, 0);
    getAvg(arr, Inter, 500, 0);
    std::cout << std::endl; 

    getAvg(arr, Jump1, 500, 1);
    getAvg(arr, Jump2, 500, 1);
    getAvg(arr, Fib, 500, 1);
    getAvg(arr, Inter, 500, 1);

    getMod(arr, 500);
}