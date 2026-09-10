// Подключаю заголовок, где объявлена функция example_function.
#include "example.h"

// Подключаю библиотеку для вывода текста в консоль.
#include <iostream>

// 212-Хруцкая: функция выводит дополнительное сообщение из отдельного файла.
void example_function() {
	// Печатаю текст, чтобы было видно, что функция вызвалась.
	std::cout << "Hello from example function!" << std::endl;
}
