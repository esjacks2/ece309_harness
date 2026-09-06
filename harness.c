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