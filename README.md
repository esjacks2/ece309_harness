# ECE 309 Project 1 - LLM Mini-Harness in C

## Description

This project is a simple LLM agent harness written in C. The program
simulates some of the basic behavior of an LLM harness without connecting
to an actual LLM API.

The program accepts input from the terminal, passes the input through a
simple mock model, stores recent conversation history, and can execute a
basic calculator tool.

This project was developed using Specification Driven Development (SDD)
and vibe coding with ChatGPT.

## Features

The harness includes the following features:

- Command-line user input using `fgets()`
- Mock LLM responses
- Detection of the word `hello`
- Echo responses for normal user input
- `exit` command for safe shutdown
- Storage of the last 5 user messages
- `history` command to display conversation history
- Calculator tool for basic mathematical operations
- Automated testing using a Bash script
- Basic memory checking using Valgrind

## Project Files

### harness.c

The main C program. It contains the input loop, mock model behavior,
conversation history, and calculator tool.

### test.sh

A Bash script used to automatically test the program. It sends predefined
inputs to the harness and also runs a basic memory check using Valgrind.

### vibe_coding_log.md

Documents the prompts, AI responses, changes, debugging steps, and
development process used to create the project.

### README.md

Contains information about the project, compilation instructions, testing,
and usage.

## Requirements

The program was developed for a POSIX environment.

Windows users can use Windows Subsystem for Linux (WSL).

The following tools are required:

- GCC
- Bash
- Valgrind for memory testing

On Ubuntu/WSL, the required development tools can be installed with:

```bash
sudo apt update
sudo apt install build-essential
sudo apt install valgrind
```

## Compiling the Program

Navigate to the project directory and compile `harness.c` using GCC:

```bash
gcc harness.c -o harness
```

If compilation succeeds, GCC should create an executable named `harness`.

## Running the Program

Run the program using:

```bash
./harness
```

The program will display:

```text
You:
```

Enter a message and press Enter.

## Commands

### Hello

Entering a sentence containing `hello` causes the mock model to return
a hardcoded greeting.

Example:

```text
You: hello
Model: Hello! Nice to meet you.
```

### Normal Input

Input that does not contain a recognized command is echoed by the mock
model.

Example:

```text
You: testing
Model: You said: testing
```

### Calculator

The calculator tool is activated using `calc` followed by two numbers
and an operator.

Example:

```text
You: calc 5 + 3
Tool result: 8.00
```

The calculator supports:

- `+` Addition
- `-` Subtraction
- `*` Multiplication
- `/` Division

For example:

```text
calc 10 / 2
calc 4 * 5
calc 10 - 3
```

The calculator also checks for division by zero.

### Conversation History

Enter:

```text
history
```

to display the stored conversation history.

The harness stores up to the 5 most recent user messages.

Example:

```text
You: hello
Model: Hello! Nice to meet you.

You: testing
Model: You said: testing

You: history
Conversation history:
1. hello
2. testing
```

When more than 5 messages are entered, the oldest message is removed
and the newest message is stored.

### Exit

Enter:

```text
exit
```

to safely terminate the program.

Example:

```text
You: exit
Goodbye!
```

## Automated Testing

The project includes a Bash testing script called `test.sh`.

Run the test using:

```bash
bash test.sh
```

The script automatically sends predefined input into the harness to test
the major program features.

The test checks:

- Mock model response
- Calculator tool
- Normal input
- Conversation history
- Program shutdown

The script also runs the program using Valgrind to perform a basic check
for memory errors and memory leaks.

## Program Architecture

The harness follows this basic process:

1. Start the program.
2. Ask the user for input.
3. Read the input using `fgets()`.
4. Check for the `exit` command.
5. Check for the `history` command.
6. Store normal input in conversation history.
7. Check whether the calculator tool should be used.
8. Check whether the input contains `hello`.
9. Otherwise, echo the user's input.
10. Return to the beginning of the loop.

The loop continues until the user enters `exit`.

## Libraries Used

The program only uses standard C libraries:

```c
#include <stdio.h>
#include <string.h>
```

No external C libraries or LLM APIs are required.

## AI-Assisted Development

ChatGPT was used as the AI assistant during development.

The development process included:

- Defining the initial program specification
- Generating the basic C implementation
- Improving input handling
- Adding context management
- Adding calculator tool execution
- Creating automated tests
- Debugging the WSL development environment
- Adding memory testing

The prompts and AI-assisted development process are documented in
`vibe_coding_log.md`.

## Author

ECE 309 Project 1

## Conclusion

This project demonstrates the basic architecture of an LLM agent harness
without requiring access to a real LLM API. The harness manages user input,
maintains a small amount of conversation context, routes mathematical
requests to a calculator tool, and produces simulated model responses.
