#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <set>

// Для работы с файлами (игнорим)
#define SURNAMES_FILE "C:\\Uni\\aisd_labs_sem4\\7\\surnames.txt"
#define FILE_LINES 2000
#define UNIQUE_LINES 1735

// Размер хэш таблицы
#define CAPACITY 512


// Структура и ее заполнение
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
		return fillNextSurname(p);
	}
}


// Класс Хэш Таблицы
class HashTable {
private:
	static const int hashGroups = CAPACITY; // Размер таблицы (вместимость)
	std::list<std::pair<int, Person>> table[hashGroups]; // Для резолюции коллизий использован метод цепочек
//        ^         ^    ^     ^
//   СПИСОК хранит ПАРЫ: КЛЮЧ, ЗНАЧЕНИЕ
public:
	int hashFunction(int key);
	int generateKey(Person value);
	void insert(int key, Person value);
	void print();
	void printCollisions();
	void calcChiSquared();
};

// Вычисление хэша для ключа
int HashTable::hashFunction(int key) {
	return (key % CAPACITY + CAPACITY) % CAPACITY;
}


// Множество, хранящее в себе использованные ключи (дубликатов в множестве быть не может, 
// они просто не вставятся, поэтому этим гарантируется уникальность ключа)
std::set<int> usedKeys;

// Функция генерации ключей на основе содержимого структуры Person
int HashTable::generateKey(Person value) {
	int sum = 0;
	int len = strlen(value.surname);
	// Просто перевод строки в целочисленное представление по формуле ниже
	for (int i = 0; i < len; i++) { // sum = (surname[0] * (len - 0) + ... + surname [len - 1] * (len - len - 1)) % HashTableSize
		sum += ((int)value.surname[i] * (len - i)) % CAPACITY;
	}

// usedKeys имеет тип std::set (множество), который запрещает дубликаты. В std::set есть функция insert.
// Функция возвращает std::pair<неважно, bool>. Вот это bool это получилось ли вставить или нет.
// Т. к. значения должны быть уникальны, то не получится вставить только в случае если значение повторяется.
// Теперь в цикле проверяем вставилось ли, для этого из вот этого std::pair<неважно, bool> берем второе
// значение с помощью поля std::pair<>.second и проверяем его пока оно не будет true.
// Если значение занято, просто +1 к нему и снова пробуем вставить пока не получится.
	while (!usedKeys.insert(sum).second)
		sum++;

	return sum;
}

// Вставка в хэш таблицу
void HashTable::insert(int key, Person value) {
	// Вычисляем хэш значение
	int hashValue = hashFunction(key);

	// Записываем соответствующий список в переменную cell
	auto& cell = table[hashValue];

	// Вставляем пару ключ-значение в соответствующий список
	cell.emplace_back(key, value);
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

// Вывести информацию о коллизиях
// Ctrl + C в эксель и там Данные -> Разделить на столбцы
void HashTable::printCollisions() {
	int elements = 0; // Общее количество элементов
	int counter = 0; // Количество элементов в одном списке
	int max = 0; // Максимальное количество элементов в одном списке
	int totalCol = 0; // Общее количество коллизий
	int totalPages = 0; // Общее количество списков с коллизиями

	for (int i = 0; i < hashGroups; i++) {
		if (table[i].size() == 0) continue;

		// см. ИТЕРАТОРЫ
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

// Вычисление хи-квадрат (см. презентацию к лабораторке)
// Как я понимаю это не обязятально, потому что результат дерьма в любом случае
void HashTable::calcChiSquared() {
	double sum = 0;
	int numOfEl = 0;
	for (int i = 0; i < CAPACITY; i++) {

		auto bIter = table[i].begin();
		for (; bIter != table[i].end(); bIter++) {
			numOfEl++;
		}

		sum += std::pow((numOfEl - (double)UNIQUE_LINES / CAPACITY), 2);
		numOfEl = 0;
	}

	std::cout << "[INFO] Chi-squared equals to: " << (double)CAPACITY / UNIQUE_LINES * sum << std::endl;
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
