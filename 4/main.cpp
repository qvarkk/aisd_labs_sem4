#include <iostream>
#include <chrono>
#include <vector>
#include <string>

// Алгоритм поиска подстрок Рабина-Карпа
int search(std::string sub, std::string str, int base = 256, int mod = INT_MAX) {
	int m = sub.length();
	int n = str.length();

	int subHash = 0;
	int strHash = 0;
	int power = 1;

	for (int i = 0; i < m; i++)
		power = (power * base) % mod;

	for (int i = 0; i < m; i++) {
		subHash = (base * subHash + sub[i]) % mod;
		strHash = (base * strHash + str[i]) % mod;
	}

	for (int i = 0; i <= n - m; i++) {
		if (subHash == strHash) {
			int j;
			for (j = 0; j < m; j++) {
				if (str[i + j] != sub[j]) {
					break;
				}
			}

			if (j == m)
				return i;
		}

		if (i < n - m) {
			strHash = (base * (strHash - str[i] * power) + str[i + m]) % mod;

			if (strHash < 0)
				strHash = (strHash + mod);
		}
	}

	return -1;
}

// Генерация случайной строки
std::string randStr(int n) {
	std::string res;

	for (int i = 0; i < n; i++)
		res += 'a' + rand() % 26;

	return res;
}

// Генерация подстроки
std::string getSubstring(std::string str, int subSize) {
	int margin = str.length() / 2;
	std::string res;

	for (int i = 0; i < subSize; i++)
		res += str[margin + i];

	return res;
}

void getStrDiffTime() {
	int strSize = 1000000;
	int strStartSize = strSize / 10;
	int subSize = 100;

	std::cout << "str\ttime" << std::endl;

	for (int i = strStartSize; i <= strSize; i += strStartSize) {
		std::string str = randStr(i);
		std::string sub = getSubstring(str, subSize);

		auto start = std::chrono::high_resolution_clock::now();

		if (search(sub, str) == -1) std::cout << "Couldn't find substring in what should be a successful case" << std::endl;
		// if (str.find(sub) == -1) std::cout << "Couldn't find substring in what should be a successful case" << std::endl;

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> res = end - start;
		std::cout << i << "\t" << res.count() << std::endl;
	}
}

void getSubDiffTime() {
	int subSize = 100;
	int subStartSize = subSize / 10;
	int strSize = 1000000;

	std::cout << "sub\ttime" << std::endl;

	std::string str = randStr(strSize);
	for (int i = subStartSize; i <= subSize; i += subStartSize) {
		std::string sub = getSubstring(str, i);

		auto start = std::chrono::high_resolution_clock::now();

		if (search(sub, str) == -1) std::cout << "Couldn't find substring in what should be a successful case" << std::endl;
		// if (str.find(sub) == -1) std::cout << "Couldn't find substring in what should be a successful case" << std::endl;

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> res = end - start;
		std::cout << i << "\t" << res.count() << std::endl;
	}
}

int main() {
	getStrDiffTime();
	std::cout << std::endl;
	getSubDiffTime();

	return 0;
}