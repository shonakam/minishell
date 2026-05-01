# 🐚 minishell
#### ***As beautiful as a shell.***

![minishell demo](./assets/demo.gif)

## Installation & Usage
### 🛠️ Prerequisites
The following environment and tools are required for the build:
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS-lightgrey?style=flat-square&logo=linux)
![GCC](https://img.shields.io/badge/GCC-v11+-blue?style=flat-square&logo=gnu)
![Make](https://img.shields.io/badge/Make-v3.81+-orange?style=flat-square&logo=gnu)
- **Compiler**: `gcc` (v11+) or `clang`
- **Build System**: `GNU Make` (v3.81+)
- **Standard**: C99 compliant

```bash
# Clone
git clone --recursive https://github.com/shonakam/minishell.git

# Compile
cd minishell
make

# Execution
./minishell

```

## Core Architectures

This project is a micro-architecture-oriented UNIX shell, rebuilding POSIX-compliant process management from scratch. It is not merely a command executor, but a system focused on **AST (Abstract Syntax Tree) based logical execution** and **job control**.

### 0. Input Engine: Custom Readline (`srcs/readline`)
To achieve a zero-dependency architecture, the line-editing system was implemented from scratch using low-level terminal control.

- **Terminal Control**: Direct manipulation of termios to switch between canonical and raw modes.

- **Buffer Management**: Real-time handling of input strings with support for dynamic cursor positioning and multi-line rendering.

- **ANSI Escape Sequences**: Custom parser for handling terminal-specific codes for arrow keys, Ctrl shortcuts, and screen clearing.

- **History Interface**: An integrated history management system allowing seamless navigation of previous commands.


### 1. Session Management (`srcs/session`)
Manages the unique, persistent state (Context) shared across the entire process.

- **Environment**: Maintenance and serialization of the environment variable list.

- **Status**: Management of the most recent exit status ($?).

- **Signal Control**: Dynamic switching of signal behavior between interactive mode and execution mode.


### 2. Analysis Engine (`srcs/lexer`, `srcs/parser`)
Decomposes strings into meaningful units (tokens) and constructs an AST using recursive descent parsing.

- **FSM Lexer**: Accurate lexical analysis utilizing a Finite State Machine.

- **Syntax Validator**: Verifies grammatical consistency for &&, ||, |, and parentheses prior to execution.


### 3. Expansion System (`srcs/executor/expander`)
Transforms strings within the AST into an executable form immediately before execution.
Variable Expansion: Replacement of $VAR with environment variable values.

- **Quote Remova**l: Removal of single (') and double (") quotes.

- **Wildcard (*)**: Pattern matching and expansion for filenames in the current directory.
  - Note: Supports single-level depth only; specialized for matching patterns that do not contain /.

- **Heredoc**: Pre-execution preparation of all heredocs and temporary file management.


### 4. Execution Engine (`srcs/executor`)
Recursively traverses the AST to perform process generation and I/O control.

- **Logical Ops**: Controls conditional execution via && and ||.

- **Pipeline**: Connects multiple processes using pipe() and fork().

- **Subshell Isolation**: Ensures complete separation of execution contexts via (...). By recursively calling the exec_engine within child processes, it supports infinite nesting of scopes.

- **Job Control**: Full synchronization of background execution (&) and comprehensive cleanup upon termination.

## End of Session

May your exit status always be `0`. Happy Hacking! 🐚✨
