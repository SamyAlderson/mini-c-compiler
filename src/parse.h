#ifndef MINI_C_COMPILER_PARSE_H
#define MINI_C_COMPILER_PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include "tokenize.h"
#include "semantics.h"

/**
 * Parse the input stream into an abstract syntax tree (AST)
 *
 * @param tokens the token stream to parse
 * @param ast the AST to populate
 * @return 0 on success, -1 on error
 */
int parse_token_stream(token_t *tokens, ast_t *ast);

/**
 * Parse a single token and return its corresponding AST node
 *
 * @param token the token to parse
 * @return the parsed AST node, or NULL on error
 */
ast_t *parse_token(token_t *token);

/**
 * Free the resources allocated for the AST
 *
 * @param ast the AST to free
 */
void free_ast(ast_t *ast);

#endif  // MINI_C_COMPILER_PARSE_H