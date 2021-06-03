## README

- [English](README.md)
- [Русский](README-ru.md)

## Project tree

```
$ tree --charset ascii

.
|-- README*.md      // README instructions
|-- app             // Source code folder C
|   `-- *.c         // Source code C (*. c,*. h)
|-- bin             // Folder with the executable file
|   |-- Debug       // The folder with the executable file in Debug mode
|   |   `-- *       // Executable file
|   `-- Release     // Folder with the executable file in Release mode
|       `-- *       // Executable file
|-- obj             // Folder with object files
|   `-- Debug       // Folder with object files in Debug mode
|           `-- *.o // Object files (*. o)
|   `-- Release     // Folder with object files in Release mode
|           `-- *.o // Object files (*. o)
`-- *.cbp           // Deploying a project in the CodeBlocks IDE
```

## How to compile a project

The project is written in the `CodeBlocks` IDE.

To open the project, run the file `*.cbp`.

In the IDE `CodeBlocks` there is a green arrow button `| > Build and Run` - an executable file is created in the `bin/Debug` folder or in the `bin/Release` folder.
