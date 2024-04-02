#include <iostream>
#include <math.h>
#include <chrono>

enum class Method { Increasing, Decreasing, Random, Sawtoothed, Sinusoidal, Stepped, QuasiSorted };

template<typename T>
T randV(T min, T max) {
	double V = (double)(rand()) / RAND_MAX;
	return (T)(V * (max - min + 1) + min);
}

template<typename T>
void GenIncreasingSequence(T *arr, int size, T min, T max) {
	T step = (max - min) / size;
	T val = min;

	for (int i = 0; i < size; i++) {
		arr[i] = val;
		val += step;
	}
}

template<typename T>
void GenDecreasingSequence(T *arr, int size, T min, T max) {
	T step = (max - min) / size;
	T val = max;

	for (int i = 0; i < size; i++) {
		arr[i] = val;
		val -= step;
	}
}

template<typename T>
void GenRandomSequence(T *arr, int size, T min, T max) {
	for (int i = 0; i < size; i++) {
		arr[i] =  randV(min, max);
	}
}

template<typename T>
void GenSawtoothedSequence(T *arr, int size, T min, T max) {
	T step = (max - min) / 10; // tooth interval is 10
	T val = min;

	for (int i = 0; i < size; i++) {
		if (i % 10 == 0)
			val = min;
		else
			val += step;

		arr[i] = val;
	}
}

template<typename T>
void GenSinusoidalSequence(T *arr, int size, T min, T max) {
	// f(x) = amplitude * sin(2 * PI * frequency * x + shift)
	double pi = atan(1) * 4;
	for (int i = 1; i <= size; i++) {
		arr[i - 1] = (T)(100 * sin(2 * pi * 0.05 * i + 500));
	}
}

template<typename T>
void GenSteppedSequence(T *arr, int size, T min, T max) {
	T step = (max - min) / (size / 10);
	T val = min;
	T error = step / 6;
	
	for (int i = 0; i < size; i++) {
		if (i % 10 == 0 && i != 0) {
			val += step;
		}
		arr[i] = randV(val - error < min ? min : val - error, val + error > max ? max : val + error);
	}
}

template<typename T>
void GenQuasiSequence(T *arr, int size, T min, T max) {
	T step = (max - min) / size;
	T val = min;
	T error = step * 2;

	for (int i = 0; i < size; i++) {
		arr[i] = randV(val - error < min ? min : val - error , val + error > max ? max : val + error);
		val += step;
	}
}

template<typename T>
void PrintArr(T *arr, int size) {
	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << ", ";
	}
	std::cout << "\b\b." << std::endl;
}

template<typename T>
void FillArr(T *arr, int size, T min, T max, Method m) {
	switch (m)
	{
	case Method::Increasing:
		GenIncreasingSequence(arr, size, min, max);
		break;
	case Method::Decreasing:
		GenDecreasingSequence(arr, size, min, max);
		break;
	case Method::Random:
		GenRandomSequence(arr, size, min, max);
		break;
	case Method::Sawtoothed:
		GenSawtoothedSequence(arr, size, min, max);
		break;
	case Method::Sinusoidal:
		GenSinusoidalSequence(arr, size, min, max);
		break;
	case Method::Stepped:
		GenSteppedSequence(arr, size, min, max);
		break;
	case Method::QuasiSorted:
		GenQuasiSequence(arr, size, min, max);
		break;
	}
}

template<typename T>
void MeasureTime(Method m, T min, T max) {
	for (int i = 5000000; i <= 50000000; i += 5000000) {
		T* arr = (T*)malloc(sizeof(T) * i);

		auto start = std::chrono::high_resolution_clock::now();

		FillArr(arr, i, min, max, m);

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> time = end - start;
		std::cout << time.count() << std::endl;

		if (arr)
			delete arr;
	}
	std::cout << std::endl;
}

int main(int argc, char** argv) {
	srand((unsigned)time(NULL));
	
	std::cout << "Int\n" << std::endl;
	MeasureTime(Method::Increasing, 100, 1000000);
	MeasureTime(Method::Decreasing, 100, 1000000);
	MeasureTime(Method::Random, 100, 1000000);
	MeasureTime(Method::Sawtoothed, 100, 1000000);
	MeasureTime(Method::Sinusoidal, 100, 1000000);
	MeasureTime(Method::Stepped, 100, 1000000);
	MeasureTime(Method::QuasiSorted, 100, 1000000);
	
	std::cout << "Double\n" << std::endl;
	MeasureTime(Method::Increasing, pow(10, 2), pow(10, 6));
	MeasureTime(Method::Decreasing, pow(10, 2), pow(10, 6));
	MeasureTime(Method::Random, pow(10, 2), pow(10, 6));
	MeasureTime(Method::Sawtoothed, pow(10, 2), pow(10, 6));
	MeasureTime(Method::Sinusoidal, pow(10, 2), pow(10, 6));
	MeasureTime(Method::Stepped, pow(10, 2), pow(10, 6));
	MeasureTime(Method::QuasiSorted, pow(10, 2), pow(10, 6));

	return 0;
}