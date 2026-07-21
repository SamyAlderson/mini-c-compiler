#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenize.h"
#include "parse.h"
#include "semantics.h"
#include "emitter.h"

// Function to execute the compilation process
void compile(const char *source, const char *output) {
    // Initialize lexer, parser, semantic analyzer, and emitter
    Lexer *lexer = lexer_init(source);
    Parser *parser = parser_init(lexer);
    SemanticAnalyzer *analyzer = semantic_analyzer_init(parser);
    Emitter *emitter = emitter_init(output);

    // Tokenize the source code
    Token *token = lexer_get_token(lexer);
    while (token != NULL) {
        // Parse the token
        AstNode *node = parser_parse(parser, token);
        if (node == NULL) {
            fprintf(stderr, "Error parsing token: %s\n", lexer_get_error(lexer));
            free_token(lexer, token);
            token = lexer_get_token(lexer);
            continue;
        }

        // Perform semantic analysis
        if (semantic_analyzer_analyze(analyzer, node) != 0) {
            fprintf(stderr, "Error analyzing semantics: %s\n", semantic_analyzer_get_error(analyzer));
            free_ast_node(node);
            free_token(lexer, token);
            token = lexer_get_token(lexer);
            continue;
        }

        // Emit the intermediate representation
        if (emitter_emit(emitter, node) != 0) {
            fprintf(stderr, "Error emitting intermediate representation: %s\n", emitter_get_error(emitter));
            free_ast_node(node);
            free_token(lexer, token);
            token = lexer_get_token(lexer);
            continue;
        }

        // Free resources
        free_ast_node(node);
        free_token(lexer, token);
        token = lexer_get_token(lexer);
    }

    // Clean up
    lexer_free(lexer);
    parser_free(parser);
    semantic_analyzer_free(analyzer);
    emitter_free(emitter);
}

// Main entry point
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
        return EXIT_FAILURE;
    }

    compile(argv[1], argv[2]);

    return EXIT_SUCCESS;
}