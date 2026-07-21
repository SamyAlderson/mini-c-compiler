#ifndef MINI_C_COMPILER_TOKENIZE_H
#define MINI_C_COMPILER_TOKENIZE_H

/**
 * Token type enumeration.
 */
typedef enum {
    TOKEN_NONE,
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_OPERATOR,
    TOKEN_LITERAL,
    TOKEN_ERROR
} TokenType;

/**
 * Token structure.
 */
typedef struct Token {
    TokenType type;
    char* value;
    int line;
    int column;
} Token;

/**
 * Tokenizer structure.
 */
typedef struct Tokenizer {
    char* input;
    int input_len;
    int line;
    int column;
} Tokenizer;

/**
 * Create a new tokenizer instance.
 *
 * @param input The input string to tokenize.
 * @return A new tokenizer instance.
 */
Tokenizer* tokenize_init(char* input);

/**
 * Destroy a tokenizer instance.
 *
 * @param tokenizer The tokenizer instance to destroy.
 */
void tokenize_destroy(Tokenizer* tokenizer);

/**
 * Get the next token from the tokenizer.
 *
 * @param tokenizer The tokenizer instance.
 * @return The next token from the tokenizer, or NULL if there are no more tokens.
 */
Token* tokenize_next(Tokenizer* tokenizer);

#endif  // MINI_C_COMPILER_TOKENIZE_H