# Указываю минимальную версию CMake, с которой должен работать проект.
cmake_minimum_required(VERSION 3.12)

# Называю проект так же, как он был назван в исходных файлах.
project(02.hello_world)

# Создаю исполняемый файл hello_world из перечисленных ниже файлов.
add_executable(hello_world
    # Главный файл программы, где находится main.
    hello_world.cpp
    # Файл с реализацией примерной функции.
    example.cpp
    # Заголовочный файл для example_function.
    example.h
    # Файл, куда вынесена функция todo_move_me_out.
    move_me_out.cpp
    # Заголовочный файл с объявлением todo_move_me_out.
    move_me_out.h
)

# Настраиваю свойства цели hello_world.
set_target_properties(hello_world PROPERTIES
    # Проект собирается с использованием стандарта C++17.
    CXX_STANDARD 17
    # Требую, чтобы компилятор обязательно поддерживал C++17.
    CXX_STANDARD_REQUIRED ON
)
