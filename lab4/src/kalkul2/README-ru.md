## README

- [English](README.md)
- [Русский](README-ru.md)

## Как скомпилировать проект

### Вариант 1

```bash
cd app
gcc -c calculate.c -o calculate.o
gcc -c main.c -o main.o
gcc calculate.o main.o -o kalkul -lm
./kalkul
```

Создался исполняемый файл `kalkul`.

### Вариант 2

```bash
cd app
make
./kalkul
```

Создался исполняемый файл `kalkul`.

## Очистка проекта

```bash
cd app
make clean
```

Удалились объектные файлы `*.o`.
