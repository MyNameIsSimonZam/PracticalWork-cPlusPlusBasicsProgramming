#include <iostream>

void task1();
void task2();
void task3();
void task4();

int main() {
	int choice;

	std::cout << "1. Задание 1. Шифр Цезаря\n";
	std::cout << "2. Задание 2. Проверка корректности email-адреса\n";
	std::cout << "3. Задание 3. Валидация IP-адреса\n";
	std::cout << "4. Задание 4. Оценка результатов игры в крестики-нолики\n";

	std::cin >> choice;

	switch (choice) {

	case 1: task1(); break;
	case 2: task2(); break;
	case 3: task3(); break;
	case 4: task4(); break;
	default: std::cout << "Invalid choice...\n";

	}
	
	return 0;
}
