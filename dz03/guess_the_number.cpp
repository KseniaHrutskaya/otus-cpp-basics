// Подключаю генератор случайных чисел из стандартной библиотеки C.
#include <cstdlib>

// Подключаю работу со временем для начального значения генератора.
#include <ctime>

// Подключаю работу с файлами для таблицы рекордов.
#include <fstream>

// Подключаю ввод и вывод в консоль.
#include <iostream>

// Подключаю map, чтобы хранить лучший результат каждого игрока.
#include <map>

// Подключаю строки для имени пользователя и аргументов командной строки.
#include <string>

// 212-Хруцкая: имя файла, где хранится таблица рекордов.
const std::string high_scores_filename = "high_scores.txt";

// 212-Хруцкая: печатаю подсказку по запуску программы, если аргументы введены неверно.
void print_usage() {
	std::cout << "Usage:" << std::endl;
	std::cout << "  guess_the_number" << std::endl;
	std::cout << "  guess_the_number -max 100" << std::endl;
	std::cout << "  guess_the_number -level 1" << std::endl;
	std::cout << "  guess_the_number -table" << std::endl;
}

// 212-Хруцкая: читаю таблицу рекордов и оставляю лучший результат для каждого имени.
std::map<std::string, int> read_high_scores() {
	// Создаю контейнер, где ключ - имя игрока, а значение - лучший результат.
	std::map<std::string, int> high_scores;

	// Открываю файл с рекордами для чтения.
	std::ifstream in_file{high_scores_filename};

	// Если файла еще нет, возвращаю пустую таблицу без ошибки.
	if (!in_file.is_open()) {
		return high_scores;
	}

	// Переменная для имени игрока из файла.
	std::string user_name;

	// Переменная для количества попыток из файла.
	int attempts_count = 0;

	// Читаю файл построчно в формате: имя количество_попыток.
	while (in_file >> user_name >> attempts_count) {
		// Ищу, был ли уже такой игрок в таблице.
		const auto current_score = high_scores.find(user_name);

		// Если игрока еще нет или новый результат лучше, сохраняю этот результат.
		if (current_score == high_scores.end() || attempts_count < current_score->second) {
			high_scores[user_name] = attempts_count;
		}
	}

	// Возвращаю готовую таблицу лучших результатов.
	return high_scores;
}

// 212-Хруцкая: вывожу таблицу рекордов на экран.
void print_high_scores() {
	// Получаю лучшие результаты из файла.
	const std::map<std::string, int> high_scores = read_high_scores();

	// Печатаю заголовок таблицы.
	std::cout << "High scores table:" << std::endl;

	// Прохожу по всем сохраненным результатам.
	for (const auto& score : high_scores) {
		// Печатаю имя пользователя и количество попыток.
		std::cout << score.first << '	' << score.second << std::endl;
	}
}

// 212-Хруцкая: сохраняю новый результат в файл с рекордами.
bool save_high_score(const std::string& user_name, int attempts_count) {
	// Открываю файл в режиме добавления, чтобы старые результаты не стерлись.
	std::ofstream out_file{high_scores_filename, std::ios_base::app};

	// Если файл не открылся, сообщаю об ошибке.
	if (!out_file.is_open()) {
		std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
		return false;
	}

	// Записываю имя пользователя.
	out_file << user_name << ' ';

	// Записываю количество попыток.
	out_file << attempts_count;

	// Завершаю строку в файле.
	out_file << std::endl;

	// Возвращаю успешный результат записи.
	return true;
}

// 212-Хруцкая: выбираю максимальное значение для загадывания по аргументам командной строки.
bool parse_arguments(int argc, char** argv, int& max_value, bool& show_table_only) {
	// Запоминаю, был ли передан параметр -max.
	bool has_max = false;

	// Запоминаю, был ли передан параметр -level.
	bool has_level = false;

	// Прохожу по аргументам, начиная с 1, потому что argv[0] - это имя программы.
	for (int i = 1; i < argc; ++i) {
		// Сохраняю текущий аргумент как строку.
		const std::string argument{argv[i]};

		// Если передан -table, нужно только показать таблицу рекордов.
		if (argument == "-table") {
			show_table_only = true;
		}
		// Если передан -max, следующий аргумент должен быть максимальным значением.
		else if (argument == "-max") {
			if (has_level) {
				std::cout << "Use either '-max' or '-level', not both." << std::endl;
				return false;
			}

			if (i + 1 >= argc) {
				std::cout << "Wrong usage! The argument '-max' requires a value." << std::endl;
				return false;
			}

			has_max = true;
			max_value = std::stoi(argv[++i]);
		}
		// Если передан -level, следующий аргумент должен быть уровнем сложности.
		else if (argument == "-level") {
			if (has_max) {
				std::cout << "Use either '-max' or '-level', not both." << std::endl;
				return false;
			}

			if (i + 1 >= argc) {
				std::cout << "Wrong usage! The argument '-level' requires a value." << std::endl;
				return false;
			}

			has_level = true;
			const int level = std::stoi(argv[++i]);

			if (level == 1) {
				max_value = 10;
			}
			else if (level == 2) {
				max_value = 50;
			}
			else if (level == 3) {
				max_value = 100;
			}
			else {
				std::cout << "Wrong level! Use 1, 2 or 3." << std::endl;
				return false;
			}
		}
		// Любой неизвестный аргумент считаю ошибкой.
		else {
			std::cout << "Unknown argument: " << argument << std::endl;
			return false;
		}
	}

	// Проверяю, чтобы максимальное значение было положительным.
	if (max_value <= 0) {
		std::cout << "Max value must be greater than zero." << std::endl;
		return false;
	}

	// Если все хорошо, возвращаю true.
	return true;
}

// 212-Хруцкая: главная функция программы "угадай число".
int main(int argc, char** argv) {
	// Значение по умолчанию: компьютер загадывает число от 0 до 99.
	int max_value = 100;

	// Флаг показывает, нужно ли только вывести таблицу рекордов.
	bool show_table_only = false;

	// Разбираю аргументы командной строки.
	if (!parse_arguments(argc, argv, max_value, show_table_only)) {
		print_usage();
		return -1;
	}

	// Если пользователь попросил таблицу, вывожу ее и завершаю программу.
	if (show_table_only) {
		print_high_scores();
		return 0;
	}

	// Инициализирую генератор случайных чисел текущим временем.
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// Получаю случайное число в диапазоне от 0 до max_value - 1.
	const int target_value = std::rand() % max_value;

	// Прошу пользователя ввести имя.
	std::cout << "Hi! Enter your name, please:" << std::endl;

	// Создаю переменную для имени пользователя.
	std::string user_name;

	// Читаю имя пользователя из консоли.
	std::cin >> user_name;

	// Создаю счетчик попыток.
	int attempts_count = 0;

	// Создаю переменную для текущей догадки пользователя.
	int current_value = 0;

	// Сообщаю пользователю, что можно вводить числа.
	std::cout << "Enter your guess:" << std::endl;

	// Запускаю цикл угадывания числа.
	while (true) {
		// Читаю число, которое ввел пользователь.
		std::cin >> current_value;

		// Проверяю, что пользователь ввел именно число.
		if (std::cin.fail()) {
			std::cout << "Bad value!" << std::endl;
			return -1;
		}

		// Увеличиваю счетчик попыток после каждого введенного числа.
		++attempts_count;

		// Если введенное число меньше загаданного, вывожу подсказку.
		if (current_value < target_value) {
			std::cout << "less than " << current_value << std::endl;
		}
		// Если введенное число больше загаданного, вывожу другую подсказку.
		else if (current_value > target_value) {
			std::cout << "greater than " << current_value << std::endl;
		}
		// Если число угадано, завершаю цикл.
		else {
			std::cout << "you win! attempts = " << attempts_count << std::endl;
			break;
		}
	}

	// Сохраняю результат пользователя в таблицу рекордов.
	if (!save_high_score(user_name, attempts_count)) {
		return -1;
	}

	// Вывожу обновленную таблицу рекордов.
	print_high_scores();

	// Возвращаю 0, потому что программа завершилась успешно.
	return 0;
}
