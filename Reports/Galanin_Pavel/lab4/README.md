## README

- [English](README.md)
- [Русский](README-ru.md)

## Project tree

```bash
tree --charset ascii
.
|-- README**            // Repository information
|-- docker-compose.yml  // Docker configuration
|-- rep
|   `-- main
|       `-- main.pdf    // Compiled PDF
`-- src                 // Source code
```

## Compile PDF

Docker must be installed.

Starting the Docker VM via `docker-compose.yml`.

```bash
sudo docker-compose run latex /bin/bash
```

As soon as the virtual machine is started, go to the directory with the `main.tex` file.

```bash
cd /content/rep/main
```

Compile the `main.tex` file.

```bash
pdflatex main.tex
```

The second time we compile the file `main.tex`, so that the links in the document work correctly.

```bash
pdflatex main.tex
```

The compiled `main.pdf` file in the `rep/main` folder along with the `main.tex` file.
