#include <iostream>
#include <chrono>
#include <vector>

std::vector<int> search(char* pat, char* txt, int base = 256, int mod = INT_MAX) {
	int m = std::strlen(pat);
	int n = std::strlen(txt);
	int patHash = 0;
	int txtHash = 0;
	int power = 1;
	std::vector<int> out;

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
				out.push_back(i);
		}

		if (i < n - m) {
			txtHash = (base * (txtHash - txt[i] * power) + txt[i + m]) % mod;

			if (txtHash < 0)
				txtHash = (txtHash + mod);
		}
	}

	return out;
}

void randCharArray(char* arr, int n) {
	for (int i = 0; i < n; i++)
		arr[i] = rand() % 255 + 1;
}

void getTimeComplexity(int initStrSize, int maxStrSize, int initPatSize, int maxPatSize, int iters = 100) {
	char* txt = new char[maxStrSize];
	char* pat = new char[maxStrSize / 10];
	randCharArray(pat, maxStrSize / 10);
	std::cout << "pat: " << maxStrSize / 10 << "." << std::endl;
	std::cout << "txt\ttime" << std::endl;
	for (int i = initStrSize; i <= maxStrSize; i += (maxStrSize - initStrSize) / 9) {
		double total = 0;
		for (int k = 0; k < iters; k++) {
			randCharArray(txt, i);

			auto start = std::chrono::high_resolution_clock::now();

			// search(pat, txt);
			strstr(txt, pat);

			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> time = end - start;
			total += time.count();
		}
		std::cout << i << "\t" << total / iters << std::endl;
	}

	if (pat)
		delete[] pat;
	pat = new char[maxPatSize];

	if (txt)
		delete[] txt;
	txt = new char[maxPatSize * 10];
	randCharArray(txt, maxPatSize * 10);
	std::cout << "\ntxt: " << maxPatSize * 10 << "." << std::endl;
	std::cout << "pat\ttime" << std::endl;
	for (int i = initPatSize; i <= maxPatSize; i += (maxPatSize - initPatSize) / 9) {
		double total = 0;
		for (int k = 0; k < iters; k++) {
			randCharArray(pat, i);

			auto start = std::chrono::high_resolution_clock::now();

			// search(pat, txt);
			strstr(txt, pat);

			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> time = end - start;
			total += time.count();
		}
		std::cout << i << "\t" << total / iters << std::endl;
	}
}

int main(int argc, char** argv) {
	
	getTimeComplexity(10000, 100000, 10000, 100000);

	return 0;
}