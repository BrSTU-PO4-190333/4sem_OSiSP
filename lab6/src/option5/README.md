## README

- [English](README.md)
- [Русский](README-ru.md)

## Project tree

```bash
tree --charset ascii
```

```
.
|-- build            # Folder with the compiled project
|   |-- Debug        # Folder with the compiled project
|   |   `-- main.exe # Executable program (Windows)
|   |-- main         # Executable program (Linux)
|   |-- Makefile     # Compilation via make
|   |-- Project.cbp  # Launches CodeBlocks
|   `-- Project.sln  # Starts VisualStudio
|-- CMakeLists.txt   # Cmake configuration
|-- README*.md       # Repository information
`-- src              # Source code folder
    |-- **/*.c       # C source code
    |-- **/*.h       # C header files
    |-- **/*.cpp     # C++ source code
    `-- **/*.hpp     # C++ header files
```

## How to compile a project

To compile, you need 'cmake'.

```bash
mkdir build
cd build
cmake ..
# cmake .. --G"Code Blocks - Unix Makefiles"
# Open the project in CodeBlocks when opening build/Project.cbn
# Open the project in VisualStudio when opening build/Project.sln
cmake --build .
./main
# Debug/main.exe
```