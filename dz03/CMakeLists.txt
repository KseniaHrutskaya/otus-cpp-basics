# Указываю минимальную версию CMake для сборки проекта.
cmake_minimum_required(VERSION 3.12)

# Называю проект по номеру домашнего задания.
project(03.guess_the_number)

# Создаю исполняемую программу guess_the_number.
add_executable(guess_the_number
    # Главный файл с игрой "угадай число".
    guess_the_number.cpp
)

# Настраиваю стандарт C++ для программы.
set_target_properties(guess_the_number PROPERTIES
    # Использую стандарт C++17.
    CXX_STANDARD 17
    # Требую, чтобы C++17 обязательно поддерживался компилятором.
    CXX_STANDARD_REQUIRED ON
)
