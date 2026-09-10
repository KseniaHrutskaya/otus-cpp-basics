# Домашнее задание 03

Игра "угадай число" с таблицей рекордов.

Что сделано:

- программа загадывает случайное число;
- пользователь вводит имя и пытается угадать число;
- программа подсказывает `less than` или `greater than`;
- после победы выводится `you win! attempts = ...`;
- результат сохраняется в `high_scores.txt`;
- таблица рекордов выводит лучший результат для каждого пользователя;
- добавлены параметры `-max`, `-level` и `-table`;
- проект собирается через CMake.

Примеры запуска:

```bash
cmake -S . -B build
cmake --build build
./build/guess_the_number
./build/guess_the_number -max 50
./build/guess_the_number -level 2
./build/guess_the_number -table
```
