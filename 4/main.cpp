#include <iostream>
#include <chrono>
#include <vector>

void search(char* pat, char* txt, int base = 256, int mod = INT_MAX) {
	int m = std::strlen(pat);
	int n = std::strlen(txt);
	int patHash = 0;
	int txtHash = 0;
	int power = 1;

	for (int i = 0; i < m; i++)
		power = (power * base) % mod;

	for (int i = 0; i < m; i++) {
		patHash = (base * patHash + pat[i]) % mod;
		txtHash = (base * txtHash + txt[i]) % mod;
	}

	for (int i = 0; i <= n - m; i++) {
		if (patHash == txtHash) {
			int j;
			for (j = 0; j < m; j++) {
				if (txt[i + j] != pat[j]) {
					break;
				}
			}

			if (j == m)
				std::cout << "Found pattern at " << i << std::endl;
		}

		if (i < n - m) {
			txtHash = (base * (txtHash - txt[i] * power) + txt[i + m]) % mod;

			if (txtHash < 0)
				txtHash = (txtHash + mod);
		}
	}
}

void randCharArray(char* arr, int n) {
	for (int i = 0; i < n; i++)
		arr[i] = rand() % 255 + 1;
}

void getTimeComplexity(int iters = 500) {
	char* txt = new char[100000];
	char* pat = new char[2000];
	randCharArray(pat, 2000);
	std::cout << "pat: 2000." << std::endl;
	std::cout << "txt\ttime" << std::endl;
	for (int i = 10000; i <= 100000; i += 10000) {
		double total = 0;
		for (int k = 0; k < iters; k++) {
			randCharArray(txt, i);

			auto start = std::chrono::high_resolution_clock::now();

			//search(pat, txt);
			strstr(txt, pat);

			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> time = end - start;
			total += time.count();
		}
		std::cout << i << "\t" << total / iters << std::endl;
	}

	if (pat)
		delete[] pat;
	pat = new char[50000];

	if (txt)
		delete[] txt;
	txt = new char[100000];
	randCharArray(txt, 100000);
	std::cout << "\ntxt: 100000." << std::endl;
	std::cout << "pat\ttime" << std::endl;
	for (int i = 5000; i <= 50000; i += 5000) {
		double total = 0;
		for (int k = 0; k < iters; k++) {
			randCharArray(pat, i);

			auto start = std::chrono::high_resolution_clock::now();

			//search(pat, txt);
			strstr(txt, pat);

			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> time = end - start;
			total += time.count();
		}
		std::cout << i << "\t" << total / iters << std::endl;
	}
}

int main(int argc, char** argv) {
	
	getTimeComplexity();

	return 0;
}