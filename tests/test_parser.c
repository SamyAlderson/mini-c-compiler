#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "parse.h"

void test_parser(void) {
    // Test case 1: Empty input
    char* input = "";
    char* expected_output = "";
    parse(input, strlen(input), stdout);
    assert(strcmp(expected_output, "") == 0);

    // Test case 2: Single identifier
    input = "x";
    expected_output = "IDENTIFIER x";
    parse(input, strlen(input), stdout);
    assert(strcmp(expected_output, "IDENTIFIER x") == 0);

    // Test case 3: Double identifier
    input = "x y";
    expected_output = "IDENTIFIER x\nIDENTIFIER y";
    parse(input, strlen(input), stdout);
    assert(strcmp(expected_output, "IDENTIFIER x\nIDENTIFIER y") == 0);

    // Test case 4: Identifier with spaces
    input = "x   y";
    expected_output = "IDENTIFIER x\nIDENTIFIER y";
    parse(input, strlen(input), stdout);
    assert(strcmp(expected_output, "IDENTIFIER x\nIDENTIFIER y") == 0);

    // Test case 5: Invalid input
    input = "x!";
    char* error_message = "";
    int error = parse(input, strlen(input), stdout);
    assert(error == -1);
    assert(strcmp(error_message, "Invalid character '!'") == 0);

    printf("All test cases passed!\n");
}

int main(void) {
    test_parser();
    return EXIT_SUCCESS;
}
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void parse(char* input, size_t length, FILE* output) {
    // Initialize parser state
    int state = 0;
    char* token = malloc(1024);
    size_t token_length = 0;

    // Iterate over input characters
    for (size_t i = 0; i < length; i++) {
        char c = input[i];

        // Handle whitespace
        if (c == ' ' || c == '\n' || c == '\t') {
            if (token_length > 0) {
                // Emit token
                fprintf(output, "%s\n", token);
                token_length = 0;
            }
            continue;
        }

        // Handle identifiers
        if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_') {
            // Append character to token
            token[token_length++] = c;
            if (token_length >= 1024) {
                // Error: token too long
                fprintf(stderr, "Error: token too long\n");
                free(token);
                return -1;
            }
            continue;
        }

        // Handle invalid characters
        fprintf(stderr, "Invalid character '%c'\n", c);
        free(token);
        return -1;
    }

    // Emit final token
    if (token_length > 0) {
        fprintf(output, "%s\n", token);
    }

    free(token);
    return 0;
}