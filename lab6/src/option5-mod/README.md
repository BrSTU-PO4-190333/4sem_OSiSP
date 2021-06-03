## README

- [English](README.md)
- [Русский](README-ru.md)

## Project tree

```bash
tree --charset ascii
```

```
.
|-- Makefile    # Make configuration
|-- README*.md  # File with information
|-- bin         # Folder with executable program
|   `-- *.out   # Executable program
`-- src         # Source code folder
    |-- */*.h   # C header files
    `-- */*.c   # C source code
```

## Compile the project

```bash
make compile_app1
# make compile_app2
```

## Launch the app

```bash
make run_app1
# make run_app2
```

## Clean up the project

```bash
make clean
```
