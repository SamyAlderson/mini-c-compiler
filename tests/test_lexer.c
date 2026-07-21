#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenize.h"

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 100

void test_tokenize(void) {
    /* Create a test string with multiple tokens */
    char* test_string = "int x = 5; /* This is a comment */";
    size_t test_string_length = strlen(test_string);

    /* Tokenize the test string */
    tokenize(test_string, test_string_length);
}

void test_tokenize_empty(void) {
    /* Test tokenizing an empty string */
    char* test_string = "";
    size_t test_string_length = strlen(test_string);

    /* Tokenize the empty string */
    if (tokenize(test_string, test_string_length) != 0) {
        fprintf(stderr, "Error tokenizing empty string\n");
        exit(EXIT_FAILURE);
    }
}

void test_tokenize_invalid(void) {
    /* Test tokenizing a string with invalid characters */
    char* test_string = "int x = 5; /* This is a comment with \\n invalid character */";
    size_t test_string_length = strlen(test_string);

    /* Tokenize the test string */
    if (tokenize(test_string, test_string_length) != 0) {
        fprintf(stderr, "Error tokenizing string with invalid characters\n");
        exit(EXIT_FAILURE);
    }
}

int main(void) {
    /* Run the tests */
    test_tokenize();
    test_tokenize_empty();
    test_tokenize_invalid();

    /* Exit successfully */
    return EXIT_SUCCESS;
}
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tokenize(const char* input, size_t length) {
    /* Initialize the lexer */
    lex_state_t state = LEX_INITIAL;

    /* Iterate over each character in the input string */
    for (size_t i = 0; i < length; i++) {
        /* Get the current character */
        char c = input[i];

        /* Handle the current character based on the lexer state */
        switch (state) {
            case LEX_INITIAL:
                /* If the character is a letter or underscore, advance to the IDENT state */
                if (isalpha(c) || c == '_') {
                    state = LEX_IDENT;
                    continue;
                }
                /* If the character is a digit, advance to the NUMBER state */
                else if (isdigit(c)) {
                    state = LEX_NUMBER;
                    continue;
                }
                /* If the character is a whitespace, skip it */
                else if (isspace(c)) {
                    continue;
                }
                /* If the character is a special character, advance to the SPECIAL state */
                else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '{' || c == '}' || c == ';' || c == ',' || c == '.' || c == '=' || c == '<' || c == '>' || c == '!') {
                    state = LEX_SPECIAL;
                    continue;
                }
                /* If the character is a newline, advance to the LEX_INITIAL state */
                else if (c == '\n') {
                    state = LEX_INITIAL;
                    continue;
                }
                /* If the character is none of the above, return an error */
                else {
                    fprintf(stderr, "Invalid character %c at position %zu\n", c, i);
                    return -1;
                }
                break;

            case LEX_IDENT:
                /* If the character is a letter, underscore, or digit, continue to the next character */
                if (isalnum(c) || c == '_') {
                    continue;
                }
                /* If the character is none of the above, return the identifier */
                else {
                    printf("Identifier: %.*s\n", (int)i, input);
                    state = LEX_INITIAL;
                    continue;
                }
                break;

            case LEX_NUMBER:
                /* If the character is a digit, continue to the next character */
                if (isdigit(c)) {
                    continue;
                }
                /* If the character is none of the above, return the number */
                else {
                    printf("Number: %.*s\n", (int)i, input);
                    state = LEX_INITIAL;
                    continue;
                }
                break;

            case LEX_SPECIAL:
                /* If the character is a special character, return the special token */
                if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '{' || c == '}' || c == ';' || c == ',' || c == '.' || c == '=' || c == '<' || c == '>' || c == '!') {
                    printf("Special token: %c\n", c);
                    state = LEX_INITIAL;
                    continue;
                }
                /* If the character is none of the above, return an error */
                else {
                    fprintf(stderr, "Invalid character %c at position %zu\n", c, i);
                    return -1;
                }
                break;

            default:
                /* If the state is invalid, return an error */
                fprintf(stderr, "Invalid lexer state\n");
                return -1;
                break;
        }
    }

    /* Return successfully */
    return 0;
}

enum lex_state_t {
    LEX_INITIAL,
    LEX_IDENT,
    LEX_NUMBER,
    LEX_SPECIAL
};

typedef enum lex_state_t lex_state_t;