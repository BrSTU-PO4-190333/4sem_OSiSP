## README

- [English](README.md)
- [Русский](README-ru.md)

## Дерево проекта

```bash
tree --charset ascii
```

```
.
|-- build            # Папка с скомпилированным проектом
|   |-- Debug        # Папка с скомпилированным проектом
|   |   `-- main.exe # Исполняемая программа (Windows)
|   |-- main         # Исполняемая программа (Linux)
|   |-- Makefile     # Компиляция через make
|   |-- Project.cbp  # Запускает CodeBlocks
|   `-- Project.sln  # Запускает VisualStudio
|-- CMakeLists.txt   # Конфигурация cmake
|-- README*.md       # Информация о репозитории
`-- src              # Папка с исходным кодом
    |-- **/*.c       # Исходный код C
    |-- **/*.h       # Заголовочные файлы C
    |-- **/*.cpp     # Исходный код C++
    `-- **/*.hpp     # Заголовочные файлы C++
```

## Как скомпилировать проект

Для компиляции нужен `cmake`.

```bash
mkdir build
cd build
cmake ..
# cmake .. -G"CodeBlocks - Unix Makefiles"
# Открыть проект в CodeBlocks при открытии build/Project.cbn
# Открыть проект в VisualStudio при открытии build/Project.sln
cmake --build .
./main
# Debug/main.exe
```