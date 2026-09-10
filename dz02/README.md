# Домашнее задание 02

Проект по теме Hello World для курса C++.

Что сделано:

- функция `todo_move_me_out` вынесена из `hello_world.cpp`;
- создан заголовочный файл `move_me_out.h`;
- создан исходный файл `move_me_out.cpp`;
- в `hello_world.cpp` добавлен `#include "move_me_out.h"`;
- в `CMakeLists.txt` добавлены новые файлы проекта;
- в код добавлены комментарии к строкам и подпись `212-Хруцкая` у функций.

Сборка через CMake:

```bash
cmake -S . -B build
cmake --build build
```
