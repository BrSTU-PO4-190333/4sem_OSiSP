## README

- [English](README.md)
- [Русский](README-ru.md)

## How to compile a project

### Option 1

```bash
cd app
gcc -c calculate.c -o calculate.o
gcc -c main.c -o main.o
gcc calculate.o main.o -o kalkul -lm
./kalkul
```

The executable file `kalkul` was created.

### Option 2

```bash
cd app
make
./kalkul
```

The executable file `kalkul` was created.

## Clean up the project

```bash
cd app
make clean
```

The `*.o` object files were deleted.
