#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <stack>

#define ARR_MIN 10
#define ARR_MAX 10000
int operationCount = 0;

void swap(int *arr, int a, int b) {
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

int randInt(int min, int max) {
	double tmp = (double)rand() / RAND_MAX;
	return (int)(tmp * (max - min + 1) + min);
}

void fillIncArray(int* arr, int N, int min, int max) {
	int step = (max - min) / N;
	int tmp = min;

	for (int i = 0; i < N; i++, tmp += step)
		arr[i] = tmp;
}

void fillDecArray(int* arr, int N, int min, int max) {
	int step = (max - min) / N;
	int tmp = max;

	for (int i = 0; i < N; i++, tmp -= step)
		arr[i] = tmp;
}

void fillRandArray(int* arr, int N, int min, int max) {
	for (int i = 0; i < N; i++)
		arr[i] = randInt(min, max);
}

void fillSawArray(int* arr, int N, int min, int max) {
	int step = (max - min) / 10;
	int tmp = min;

	for (int i = 0; i < N; i++) {
		arr[i] = tmp;
		if (i != 0 && i % 10 == 0) {
			tmp = min;
		} else {
			tmp += step;
		}
	}
}

enum Method { Inc = 1, Dec, Rand, Saw };

void fillArray(int* arr, int N, int min, int max, Method m) {
	switch (m) {
	case Inc:
		fillIncArray(arr, N, min, max);
		break;
	case Dec:
		fillDecArray(arr, N, min, max);
		break;
	case Rand:
		fillRandArray(arr, N, min, max);
		break;
	case Saw:
		fillSawArray(arr, N, min, max);
		break;
	}
}


int partition(int *arr, int low, int high) {
	int pivot = arr[high];
	int i = low - 1;

	for (int j = low; j <= high; j++) {
		operationCount++;
		if (arr[j] < pivot) {
			i++;
			swap(arr, i, j);
		}
	}
	swap(arr, i + 1, high);
	return (i + 1);
}

void quickSort(int *arr, int N) {
	std::stack<std::pair<int, int>> s;
	s.push({ 0, N - 1 });

	while (!s.empty()) {
		std::pair<int, int> p = s.top();
		s.pop();

		int low = p.first;
		int high = p.second;

		if (low < high) {
			int pi = partition(arr, low, high);

			s.push({ low, pi - 1 });
			s.push({ pi + 1, high });
		}
	}
}


void heapify(int *arr, int N, int i) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	operationCount++;
	if (l < N && arr[l] > arr[largest])
		largest = l;

	operationCount++;
	if (r < N && arr[r] > arr[largest])
		largest = r;

	if (largest != i) {
		swap(arr, largest, i);
		heapify(arr, N, largest);
	}
}

void heapSort(int *arr, int N) {
	for (int i = N / 2 - 1; i >= 0; i--)
		heapify(arr, N, i);

	for (int i = N - 1; i > 0; i--) {
		swap(arr, 0, i);
		heapify(arr, i, 0);
	}
}


int getMax(int *arr, int N) {
	int tmp = arr[0];
	for (int i = 1; i < N; i++) {
		operationCount++;
		if (tmp < arr[i])
			tmp = arr[i];
	}
	return tmp;
}

void countSort(int *arr, int N, int exp) {
	int *output = new int[N];
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

void radixSort(int *arr, int N) {
	int max = getMax(arr, N);

	for (int exp = 1; max / exp > 0; exp *= 10)
		countSort(arr, N, exp);
}


bool isSorted(int* arr, int N) {
	for (int i = 0; i < N - 1; i++) {
		if (arr[i] > arr[i + 1])
			return false;
	}
	return true;
}

void printBigO(void func(int*, int), int N) {
	int min = ARR_MIN, max = ARR_MAX;
	int *arr = new int[N];
	std::string method[4] = {"Increasing", "Decreasing", "Randomeowed", "Sawtoothed"};

	for (int i = 0; i < 4; i++) {
		fillArray(arr, N, min, max, (Method)i);

		auto start = std::chrono::high_resolution_clock::now();

		operationCount = 0;
		func(arr, N);

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> time = end - start;
		std::cout << method[i] << ". " << time.count()  << "\tComparisons: " << operationCount << std::endl;
	}
}

void printArray(int *arr, int size) {
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << ", ";
	std::cout << "\b\b.\n" << std::endl;
 }

int main(int argc, char** argv) {
	srand(time(NULL));
	
	for (int i = 500; i < 5001; i += 500) {
		std::cout << "\n\tSIZE: " << i << std::endl;
		std::cout << "Quicksort: " << std::endl;
		printBigO(quickSort, i);
		std::cout << "\nHeapsort: " << std::endl;
		printBigO(heapSort, i);
		std::cout << "\nRadix sort: " << std::endl;
		printBigO(radixSort, i);
	}

	return 0;
}