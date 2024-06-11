# Custom Shell Project

This project implements a simple shell in C, allowing users to execute commands, maintain command history, and navigate through a directory structure.

## Features

- **Command Execution**: Executes commands entered by the user using `execvp`.
- **History Management**: Maintains a command history using a queue data structure.
- **User Interface**: Provides a command-line interface with basic functionalities.
- **Makefile**: Includes a Makefile for easy compilation and cleanup.

## Directory Structure

```
project_root/ 
├── include/ 
│ └── queue.h 
├── src/ 
│ ├── main.c 
│ └── queue.c 
├── bin/ # Object files will be compiled here 
├── Makefile 
└── README.md 
```

## Usage

1. **Compilation**:
   - Run `make` to compile the project.
   - Object files will be stored in the `bin` directory.
   - The executable `main` will be created in the root directory.

2. **Execution**:
   - Run `./main` to start the custom shell.
   - Enter commands such as `ls`, `pwd`, etc.
   - Type `history` to view command history.
   - Type `exit` to exit the shell.

## Dependencies

- Standard C libraries (`stdio.h`, `stdlib.h`, `string.h`, `unistd.h`)
- `make` utility for building the project

