#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantics.h"

// Semantic analysis test suite

// Test that a single variable declaration is parsed correctly
void test_variable_declaration() {
    char src[] = "int x;";
    struct semantics_state state;
    struct semantics_error error;

    semantics_init(&state);
    semantics_parse(src, strlen(src), &state, &error);

    if (error.code != SEMANTICS_OK) {
        printf("Error parsing variable declaration: %s\n", error.message);
        exit(1);
    }

    // Check that the variable is declared as an integer
    struct semantics_var* var = semantics_get_variable(&state, "x");
    if (!var || var->type != SEMANTICS_INT) {
        printf("Variable x not declared as int\n");
        exit(1);
    }

    semantics_free(&state);
}

// Test that a single function declaration is parsed correctly
void test_function_declaration() {
    char src[] = "int foo();";
    struct semantics_state state;
    struct semantics_error error;

    semantics_init(&state);
    semantics_parse(src, strlen(src), &state, &error);

    if (error.code != SEMANTICS_OK) {
        printf("Error parsing function declaration: %s\n", error.message);
        exit(1);
    }

    // Check that the function is declared as an integer
    struct semantics_func* func = semantics_get_function(&state, "foo");
    if (!func || func->return_type != SEMANTICS_INT) {
        printf("Function foo not declared as int\n");
        exit(1);
    }

    semantics_free(&state);
}

// Test that a single assignment is parsed correctly
void test_assignment() {
    char src[] = "x = 5;";
    struct semantics_state state;
    struct semantics_error error;

    semantics_init(&state);
    semantics_parse(src, strlen(src), &state, &error);

    if (error.code != SEMANTICS_OK) {
        printf("Error parsing assignment: %s\n", error.message);
        exit(1);
    }

    // Check that the variable is assigned to as an integer
    struct semantics_var* var = semantics_get_variable(&state, "x");
    if (!var || var->type != SEMANTICS_INT) {
        printf("Variable x not declared as int\n");
        exit(1);
    }

    // Check that the expression is an integer literal
    struct semantics_expr* expr = semantics_get_expr(&state);
    if (!expr || expr->type != SEMANTICS_LIT_INT) {
        printf("Expression not an integer literal\n");
        exit(1);
    }

    semantics_free(&state);
}

int main() {
    // Run all tests
    test_variable_declaration();
    test_function_declaration();
    test_assignment();

    printf("All tests passed\n");
    return 0;
}
```

```c
// semantics.h
#ifndef SEMANTICS_H
#define SEMANTICS_H

// Semantic analysis error codes
typedef enum {
    SEMANTICS_OK,
    SEMANTICS_SYNTAX_ERROR,
    SEMANTICS_SEMANTIC_ERROR
} semantics_error_code;

// Semantic analysis error structure
typedef struct {
    semantics_error_code code;
    char* message;
} semantics_error;

// Semantic analysis state structure
typedef struct {
    // ...
} semantics_state;

// Get a variable from the semantic analysis state
struct semantics_var* semantics_get_variable(semantics_state* state, char* name);

// Get a function from the semantic analysis state
struct semantics_func* semantics_get_function(semantics_state* state, char* name);

// Get an expression from the semantic analysis state
struct semantics_expr* semantics_get_expr(semantics_state* state);

// Initialize the semantic analysis state
void semantics_init(semantics_state* state);

// Free the semantic analysis state
void semantics_free(semantics_state* state);

// Parse a source string into a semantic analysis state
semantics_error_code semantics_parse(char* src, int length, semantics_state* state, semantics_error* error);

#endif  // SEMANTICS_H
```

```c
// semantics.c
#include "semantics.h"
#include <stdlib.h>
#include <string.h>

// Initialize the semantic analysis state
void semantics_init(semantics_state* state) {
    // ...
}

// Free the semantic analysis state
void semantics_free(semantics_state* state) {
    // ...
}

// Get a variable from the semantic analysis state
struct semantics_var* semantics_get_variable(semantics_state* state, char* name) {
    // ...
}

// Get a function from the semantic analysis state
struct semantics_func* semantics_get_function(semantics_state* state, char* name) {
    // ...
}

// Get an expression from the semantic analysis state
struct semantics_expr* semantics_get_expr(semantics_state* state) {
    // ...
}

// Parse a source string into a semantic analysis state
semantics_error_code semantics_parse(char* src, int length, semantics_state* state, semantics_error* error) {
    // ...
}
```

```c
// semantics.c (continued)
semantics_error_code semantics_parse(char* src, int length, semantics_state* state, semantics_error* error) {
    // ...
    // Try to parse the source string
    if (parse_token(src, length, state) == SEMANTICS_OK) {
        // Try to resolve the tokens to a semantic analysis state
        if (resolve_tokens(state) == SEMANTICS_OK) {
            // Return success
            return SEMANTICS_OK;
        } else {
            // Return a semantic error
            error->code = SEMANTICS_SEMANTIC_ERROR;
            error->message = "Semantic error";
            return SEMANTICS_SEMANTIC_ERROR;
        }
    } else {
        // Return a syntax error
        error->code = SEMANTICS_SYNTAX_ERROR;
        error->message = "Syntax error";
        return SEMANTICS_SYNTAX_ERROR;
    }
}

// Parse a token from the source string
semantics_error_code parse_token(char* src, int length, semantics_state* state) {
    // ...
}

// Resolve the tokens to a semantic analysis state
semantics_error_code resolve_tokens(semantics_state* state) {
    // ...
}