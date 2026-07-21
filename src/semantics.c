#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantics.h"

// Structure to hold semantic analysis results
typedef struct {
    int type;
    int value;
} SemanticResult;

// Function to perform semantic analysis on a given token
SemanticResult* analyze_token(Token* token) {
    // Check if token type is valid
    if (token->type == TOKEN_INVALID) {
        fprintf(stderr, "Error: invalid token type %d\n", token->type);
        return NULL;
    }

    // Switch on token type to determine analysis result
    switch (token->type) {
        case TOKEN_INT:
            // Integers are simple, just return a result with type and value
            return (SemanticResult*) malloc(sizeof(SemanticResult));
            ((SemanticResult*) malloc(sizeof(SemanticResult)))->type = TOKEN_INT;
            ((SemanticResult*) malloc(sizeof(SemanticResult)))->value = token->value;
            break;
        case TOKEN_ID:
            // IDs are more complex, we need to check if they're identifiers
            if (token->value == NULL || strlen(token->value) == 0) {
                fprintf(stderr, "Error: identifier is empty\n");
                return NULL;
            }
            // Return result with type and value
            return (SemanticResult*) malloc(sizeof(SemanticResult));
            ((SemanticResult*) malloc(sizeof(SemanticResult)))->type = TOKEN_ID;
            ((SemanticResult*) malloc(sizeof(SemanticResult)))->value = strdup(token->value);
            break;
        default:
            // If we reach this point, something went wrong
            fprintf(stderr, "Error: unknown token type %d\n", token->type);
            return NULL;
    }
}

// Function to perform semantic analysis on a given AST node
SemanticResult* analyze_ast_node(Node* node) {
    // Check if node is NULL
    if (node == NULL) {
        fprintf(stderr, "Error: null node\n");
        return NULL;
    }

    // Perform analysis on each child node
    for (int i = 0; i < node->children_count; i++) {
        Node* child = node->children[i];
        SemanticResult* result = analyze_ast_node(child);
        if (result == NULL) {
            // If child analysis fails, we also fail
            return NULL;
        }
        // Store result in node
        node->results[i] = result;
    }

    // Perform type checking on current node
    if (node->type == NODE_DECLARATION) {
        // Declarations are simple, just check if we have an identifier
        if (node->results[0]->type != TOKEN_ID || node->results[1]->type != TOKEN_INT) {
            fprintf(stderr, "Error: invalid declaration\n");
            return NULL;
        }
    } else if (node->type == NODE_EXPRESSION) {
        // Expressions are more complex, we need to check if we have an integer
        if (node->results[0]->type != TOKEN_INT) {
            fprintf(stderr, "Error: invalid expression\n");
            return NULL;
        }
    }

    // Return result with type and value
    return (SemanticResult*) malloc(sizeof(SemanticResult));
    ((SemanticResult*) malloc(sizeof(SemanticResult)))->type = node->type;
    ((SemanticResult*) malloc(sizeof(SemanticResult)))->value = 0;
}

// Function to perform semantic analysis on a given program
SemanticResult* analyze_program(Program* program) {
    // Check if program is NULL
    if (program == NULL) {
        fprintf(stderr, "Error: null program\n");
        return NULL;
    }

    // Perform analysis on each function node
    for (int i = 0; i < program->functions_count; i++) {
        Node* function = program->functions[i];
        SemanticResult* result = analyze_ast_node(function);
        if (result == NULL) {
            // If function analysis fails, we also fail
            return NULL;
        }
        // Store result in program
        program->results[i] = result;
    }

    // Return result with type and value
    return (SemanticResult*) malloc(sizeof(SemanticResult));
    ((SemanticResult*) malloc(sizeof(SemanticResult)))->type = TOKEN_PROGRAM;
    ((SemanticResult*) malloc(sizeof(SemanticResult)))->value = 0;
}