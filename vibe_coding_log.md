# ECE 309 Project 1 - Vibe Coding Log

## Project Overview

For this project, I used ChatGPT as my AI assistant to help develop a simple
LLM mini-harness in C.

My goal was to keep the program simple and understandable while meeting the
project requirements. I instructed the AI to use standard C libraries and
avoid external libraries.

---

# Iteration 1 - Creating the Basic Harness

## My Prompt

I need to write a simple command-line program in C. I am a beginner, so please
keep the code as simple as possible. Do not use external libraries, only
standard ones like <stdio.h> and <string.h>.

Here is the specification for the program:

1. It should run an infinite while loop that asks for user input using fgets.
2. If the user types "exit", the loop should break and the program should end.
3. If the user types a sentence containing the word "hello", the program should
   print a hardcoded greeting.
4. If the user types anything else, it should echo their input back to them.
5. Please add clear comments explaining what the code is doing.

## AI Response

ChatGPT generated the following program:

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Create a character array to store what the user types
    char input[100];

    // Keep running until the user types "exit"
    while (1)
    {
        // Ask the user for input
        printf("You: ");

        // Read the user's input from the terminal
        fgets(input, sizeof(input), stdin);

        // Remove the newline character added by fgets
        input[strcspn(input, "\n")] = '\0';

        // Check if the user wants to exit
        if (strcmp(input, "exit") == 0)
        {
            printf("Goodbye!\n");
            break;
        }

        // Check if the user's input contains the word "hello"
        if (strstr(input, "hello") != NULL)
        {
            printf("Model: Hello! Nice to meet you.\n");
        }
        else
        {
            // If no special command was found, echo the input
            printf("Model: You said: %s\n", input);
        }
    }

    // End the program
    return 0;
}
```

The AI then suggested an improvement to check whether fgets() successfully
received input.

---

# Iteration 2 - Correcting Input Handling

## My Prompt

Give me the corrected code.

## AI Response

ChatGPT modified the fgets() section so the program checks for an input error
before continuing.

The corrected program was:

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Create a character array to store what the user types
    char input[100];

    // Keep running until the user types "exit"
    while (1)
    {
        // Ask the user for input
        printf("You: ");

        // Read the user's input from the terminal
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        // Remove the newline character added by fgets
        input[strcspn(input, "\n")] = '\0';

        // Check if the user wants to exit
        if (strcmp(input, "exit") == 0)
        {
            printf("Goodbye!\n");
            break;
        }

        // Check if the user's input contains "hello"
        if (strstr(input, "hello") != NULL)
        {
            printf("Model: Hello! Nice to meet you.\n");
        }
        else
        {
            // If "hello" was not found, echo the user's input
            printf("Model: You said: %s\n", input);
        }
    }

    // End the program
    return 0;
}
```

---

# Iteration 3 - Understanding How to Use the Harness

## My Prompt

I'm confused, when I run the code what am I supposed to do?

## AI Response

ChatGPT explained that the program is acting as a very small simulated
chatbot.

It explained that the program currently has three behaviors:

- Typing something containing "hello" produces a hardcoded greeting.
- Typing "exit" terminates the program.
- Typing anything else causes the program to echo the input.

The AI suggested manually testing the program with input similar to:

```text
You: hello
Model: Hello! Nice to meet you.

You: I like motorcycles
Model: You said: I like motorcycles

You: exit
Goodbye!
```

This helped me understand that the mock model is not an actual AI model.
Instead, it simulates the input/output behavior of an LLM for the purpose
of building the harness.

---

# Iteration 4 - Creating the Automated Test

## My Prompt

Write me the test.sh script.

## AI Response

ChatGPT generated the following Bash script:

```bash
#!/bin/bash

# Send "hello" and "exit" to the harness program
printf "hello\nexit\n" | ./harness
```

The AI instructed me to compile the program first using:

```bash
gcc harness.c -o harness
```

and then run the automated test using:

```bash
bash test.sh
```

The expected output included the greeting followed by the program shutting
down.

---

# Iteration 5 - Fixing the Testing Environment

## Problem

When I attempted to run:

```bash
bash test.sh
```

from Windows PowerShell, I received an error because the bash command was not
available.

## AI Response

ChatGPT explained that I was using Windows PowerShell instead of a Linux/WSL
terminal.

The AI instructed me to install Windows Subsystem for Linux (WSL) using:

```powershell
wsl --install
```

After installing WSL, I opened Ubuntu and installed GCC.

When I attempted to compile the program in WSL, I received the following
error:

```text
fatal error: stdio.h: No such file or directory
```

ChatGPT explained that GCC was available but the standard C development
headers were missing.

It instructed me to run:

```bash
sudo apt update
sudo apt install build-essential
```

After installing the build tools, I compiled the program again:

```bash
gcc harness.c -o harness
```

The program compiled successfully.

I then ran:

```bash
bash test.sh
```

and the automated test worked successfully.

---

# Iteration 6 - Adding Context Management

## My Prompt

How do I do the context management?

## AI Response

ChatGPT explained that a simple way to implement context management was to
store the five most recent user messages in a two-dimensional character
array:

```c
char history[5][100];
```

It also suggested using:

```c
int history_count = 0;
```

to keep track of the number of stored messages.

The AI explained that when fewer than five messages exist, the program can
simply add the newest message to the array.

When the history becomes full, the program shifts the existing messages
forward:

```c
for (int i = 0; i < 4; i++)
{
    strcpy(history[i], history[i + 1]);
}
```

The newest message is then stored in the final position:

```c
strcpy(history[4], input);
```

ChatGPT also added a "history" command so I could verify that the stored
context was working.

For example:

```text
You: hello
Model: Hello! Nice to meet you.

You: I like cars
Model: You said: I like cars.

You: testing
Model: You said: testing

You: history
Conversation history:
1. hello
2. I like cars
3. testing
```

I added the context management code to my harness.

---

# Iteration 7 - Adding Tool Execution

## My Prompt

Okay I've added the memory part, now what?

## AI Response

ChatGPT explained that the next implementation requirement was tool execution.

The AI suggested implementing a simple calculator that could be called using
input such as:

```text
calc 5 + 3
```

It suggested creating this function:

```c
float calculate(float a, char operator, float b)
{
    if (operator == '+')
    {
        return a + b;
    }
    else if (operator == '-')
    {
        return a - b;
    }
    else if (operator == '*')
    {
        return a * b;
    }
    else if (operator == '/')
    {
        return a / b;
    }

    return 0;
}
```

The AI also suggested detecting the calculator command using:

```c
strncmp(input, "calc ", 5)
```

and parsing the calculation with sscanf().

---

# Iteration 8 - Integrating All Features

## My Prompt

Just give me the new corrected code.

## AI Response

ChatGPT combined the core loop, context management, mock model, and calculator
tool into the following program:

```c
#include <stdio.h>
#include <string.h>

// Simple calculator tool
float calculate(float a, char operator, float b)
{
    if (operator == '+')
    {
        return a + b;
    }
    else if (operator == '-')
    {
        return a - b;
    }
    else if (operator == '*')
    {
        return a * b;
    }
    else if (operator == '/')
    {
        return a / b;
    }

    return 0;
}

int main(void)
{
    char input[100];

    // Store the last 5 user messages
    char history[5][100];

    // Keep track of how many messages are stored
    int history_count = 0;

    while (1)
    {
        printf("You: ");

        // Read input from the user
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        // Remove newline character
        input[strcspn(input, "\n")] = '\0';

        // Exit command
        if (strcmp(input, "exit") == 0)
        {
            printf("Goodbye!\n");
            break;
        }

        // Show conversation history
        if (strcmp(input, "history") == 0)
        {
            printf("Conversation history:\n");

            for (int i = 0; i < history_count; i++)
            {
                printf("%d. %s\n", i + 1, history[i]);
            }

            continue;
        }

        // Save input into history
        if (history_count < 5)
        {
            strcpy(history[history_count], input);
            history_count++;
        }
        else
        {
            // Shift messages left to remove the oldest message
            for (int i = 0; i < 4; i++)
            {
                strcpy(history[i], history[i + 1]);
            }

            // Store newest message
            strcpy(history[4], input);
        }

        // Calculator tool
        if (strncmp(input, "calc ", 5) == 0)
        {
            float a;
            float b;
            char operator;

            // Read something like: calc 5 + 3
            if (sscanf(input + 5, "%f %c %f", &a, &operator, &b) == 3)
            {
                if (operator == '/' && b == 0)
                {
                    printf("Tool: Cannot divide by zero.\n");
                }
                else if (operator == '+' ||
                         operator == '-' ||
                         operator == '*' ||
                         operator == '/')
                {
                    float result = calculate(a, operator, b);
                    printf("Tool result: %.2f\n", result);
                }
                else
                {
                    printf("Tool: Invalid operator.\n");
                }
            }
            else
            {
                printf("Tool: Use format: calc 5 + 3\n");
            }
        }

        // Mock model greeting
        else if (strstr(input, "hello") != NULL)
        {
            printf("Model: Hello! Nice to meet you.\n");
        }

        // Normal mock model response
        else
        {
            printf("Model: You said: %s\n", input);
        }
    }

    return 0;
}
```

This version provided the three major parts of the harness:

1. A terminal-based core loop and mock model
2. Context management for the five most recent messages
3. A calculator tool

---

# Iteration 9 - Updating the Test Script

## My Prompt

Okay and now what?

## AI Response

ChatGPT suggested updating test.sh so that it tested the new functionality
instead of only testing "hello" and "exit".

The updated test script was:

```bash
#!/bin/bash

printf "hello\ncalc 5 + 3\ntesting\nhistory\nexit\n" | ./harness
```

This test checks:

- The "hello" mock model response
- Calculator tool execution
- Normal echo behavior
- Conversation history
- The exit command

The test can be run with:

```bash
bash test.sh
```

---

# Final Architecture

The completed harness follows this general state machine:

1. Start the program.
2. Enter the main while loop.
3. Ask the user for input.
4. Read the input using fgets().
5. Remove the newline character.
6. If the input is "exit", terminate the program.
7. If the input is "history", display the stored context.
8. Otherwise, save the input in the conversation history.
9. If the input begins with "calc", execute the calculator tool.
10. If the input contains "hello", return the mock model greeting.
11. Otherwise, echo the user's input.
12. Return to the beginning of the loop.

---

# Architectural Rules Used

During the vibe coding process, I instructed the AI to follow these rules:

- Write the program in C.
- Keep the code simple enough for a beginner to understand.
- Do not use external libraries.
- Use standard C libraries such as <stdio.h> and <string.h>.
- Use fgets() to read terminal input.
- Use a mock model instead of connecting to a real LLM API.
- Allow the program to safely terminate using "exit".
- Store only a small amount of conversation context.
- Provide a simple tool that the harness can execute.
- Keep the program compatible with GCC in the required environment.
- Include comments that explain the important parts of the code.

---

# Testing

I tested the harness both manually and using the Bash testing script.

Manual testing included:

```text
hello
calc 5 + 3
testing
history
exit
```

The automated test sends these inputs to the harness without requiring the
user to type them manually.

---

# Final Result

The final program implements a minimal LLM agent harness in C.

It can:

- Accept user input from the terminal
- Simulate an LLM using a mock response
- Detect the "hello" keyword
- Echo normal input
- Store the five most recent user messages
- Display stored conversation history
- Execute a basic calculator tool
- Safely terminate using "exit"
- Be automatically tested using a Bash script

The development process also demonstrated Specification Driven Development
by defining the program requirements and then using an AI assistant to
generate and iteratively modify the implementation.
## Iteration 10 - Memory Leak Testing

### My Prompt

How do I fix the requirement for checking basic memory leaks?

### AI Response

ChatGPT recommended using Valgrind in the WSL/Linux environment.

I installed Valgrind using:

    sudo apt install valgrind

I then updated test.sh so that it runs both a functional test and a
Valgrind memory check.

The memory test runs the harness with predefined input and checks for
memory errors and leaks.

Because the program uses fixed-size arrays rather than dynamically
allocated memory, Valgrind should report no heap memory leaks.