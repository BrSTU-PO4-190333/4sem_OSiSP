## README

- [English](README.md)
- [Русский](README-ru.md)

## Дерево проекта

```bash
tree --charset ascii
```

```
.
|-- Makefile    # Конфигурация make
|-- README*.md  # Файл с информацией
|-- bin         # Папка с исполняемой программой
|   `-- *.out   # Исполняемая программа
`-- src         # Папка исходного кода
    |-- */*.h   # Заголовочные файлы С
    `-- */*.c   # Исходный код C
```

## Компиляция проекта

```bash
make compile_app1
# make compile_app2
```

## Запуск приложения

```bash
make run_app1
# make run_app2
```

## Очистка проекта

```bash
make clean
```
