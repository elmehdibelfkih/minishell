# Minishell Project

## Introduction
Minishell is a project from 42 school that involves creating a minimal Unix shell. The objective is to understand process creation, management, and command execution while adhering to POSIX standards.

## Features
- Command execution (ls, echo, cat, etc.)
- Built-in commands (cd, pwd, export, unset, env, exit)
- Redirections (`>`, `>>`, `<`)
- Pipes (`|`)
- Environment variable expansion (`$VAR`)
- Signal handling (CTRL+C, CTRL+D, CTRL+\)
- Error handling

## Installation
### Prerequisites
- A Unix-based system (Linux/macOS recommended)
- GCC or Clang compiler
- Make

### Steps to Install
1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/minishell.git
   cd minishell
   ```
2. Compile the project:
   ```sh
   make
   ```
3. Run the shell:
   ```sh
   ./minishell
   ```

## Usage
- Execute commands like in a real shell:
  ```sh
  ls -la
  echo "Hello, world!"
  cat file.txt | grep keyword
  ```
- Use built-in commands:
  ```sh
  cd /path/to/directory
  export VAR=value
  unset VAR
  env
  pwd
  exit
  ```
- Handle redirections:
  ```sh
  ls > output.txt
  cat < input.txt
  echo "Append this" >> output.txt
  ```

## Signals
- `CTRL+C` -> Interrupts the current process.
- `CTRL+D` -> Exits the shell if no command is entered.
- `CTRL+\` -> Ignored.

## Contributing
Pull requests are welcome. Ensure to follow the coding style and document any changes.

## License
This project is licensed under the MIT License - see the LICENSE file for details.


