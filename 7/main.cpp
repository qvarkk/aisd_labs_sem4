#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <set>

#define SURNAMES_FILE "C:\\Uni\\aisd_labs_sem4\\7\\surnames.txt"
#define FILE_LINES 2000
#define UNIQUE_LINES 1735
#define CAPACITY 511

struct Person {
	char* surname;
};

void fillGivenSurname(Person* p, const char* surname) {
	p->surname = new char[std::strlen(surname) + 1];
	std::strcpy(p->surname, surname);
}

std::set<std::string> usedSurnames;
void fillRandomSurname(Person* p) {
	if (usedSurnames.size() >= UNIQUE_LINES) return;

	std::string sur;
	std::ifstream file;

	file.open(SURNAMES_FILE);
	int randLine = rand() % (FILE_LINES - 1);
	for (int i = 0; i <= randLine; i++) {
		std::getline(file, sur);
	}

	if (usedSurnames.insert(sur).second) {
		p->surname = new char[sur.length() + 1];
		std::strcpy(p->surname, sur.c_str());
	} else {
		// std::cout << "[COLLISION] " << sur << " surname was already used" << std::endl;
		fillRandomSurname(p);
	}
}

int nextLine = 0;
bool fillNextSurname(Person* p) {
	if (nextLine >= FILE_LINES || usedSurnames.size() >= UNIQUE_LINES) return false;

	std::string sur;
	std::ifstream file;

	file.open(SURNAMES_FILE);
	for (int i = 0; i <= nextLine; i++) {
		std::getline(file, sur);
	}
	nextLine++;

	if (usedSurnames.insert(sur).second) {
		p->surname = new char[sur.length() + 1];
		std::strcpy(p->surname, sur.c_str());
		return true;
	} else {
		// std::cout << "[COLLISION] " << sur << " surname is duplicated at line " << nextLine << std::endl;
		return fillNextSurname(p);
	}
}

class HashTable {
private:
	static const int hashGroups = CAPACITY;
	std::list<std::pair<int, Person>> table[hashGroups];
public:
	int hashFunction(int key);
	int generateKey(Person value);
	void insert(int key, Person value);
	void print();
	void printCollisions();
};

int HashTable::hashFunction(int key) {
	return (key % CAPACITY + CAPACITY) % CAPACITY;
}

std::set<int> usedKeys;
int HashTable::generateKey(Person value) {
	int sum = 0;
	int len = strlen(value.surname);
	for (int i = 0; i < len; i++) {
		sum += ((int)value.surname[i] * (len - i)) % CAPACITY;
	}

	while (!usedKeys.insert(sum).second)
		sum++;

	return sum;
}

void HashTable::insert(int key, Person value) {
	int hashValue = hashFunction(key);
	auto& cell = table[hashValue];
	auto bIter = begin(cell);
	bool keyExists = false;
	for (; bIter != end(cell); bIter++) {
		if (bIter->first == key) {
			keyExists = true;
			bIter->second = value;
			break;
		}
	}

	if (!keyExists) {
		cell.emplace_back(key, value);
	}
}

void HashTable::print() {
	for (int i = 0; i < hashGroups; i++) {
		if (table[i].size() == 0) continue;

		auto bIter = table[i].begin();
		for (; bIter != table[i].end(); bIter++) {
			std::cout << "[INFO] Key: " << bIter->first << "\tValue: " << bIter->second.surname << std::endl;
		}
	}
}

void HashTable::printCollisions() {
	int elements = 0;
	int counter = 0;
	int max = 0;
	int totalCol = 0;
	int totalPages = 0;

	for (int i = 0; i < hashGroups; i++) {
		if (table[i].size() == 0) continue;

		auto bIter = table[i].begin();
		for (; bIter != table[i].end(); bIter++) {
			counter++;
			elements++;
			if (table[i].size() > 1)
				totalCol++;
		}

		if (table[i].size() > 1)
			totalPages++;

		std::cout << "[INFO] Hash: " << i << "\tNumber of elements: " << counter << std::endl;
		if (max < counter) max = counter;
		counter = 0;
	}
	std::cout << "\n[INFO] Number of elements: " << elements << std::endl;
	std::cout << "[INFO] Max collisions: " << max << std::endl;
	std::cout << "[INFO] Avg collisions: " << (double)totalCol / totalPages << std::endl;
}

int main() {
	system("chcp 65001 > nul");
	srand((unsigned)time(nullptr));

	HashTable ht;
	Person p1;

	while (fillNextSurname(&p1))
		ht.insert(ht.generateKey(p1), p1);


	ht.printCollisions();
	// ht.print();

	return 0;
}
