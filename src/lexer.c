#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenize.h"

// Token type enum
typedef enum {
    TK_ERROR,
    TK_EOF,
    TK_IDENTIFIER,
    TK_NUMBER,
    TK_KEYWORD,
    TK_OPERATOR,
    TK_PUNCTUATION
} TokenType;

// Lexer struct
typedef struct {
    FILE *file;
    char *buffer;
    int buffer_size;
    int buffer_pos;
    int line;
    int column;
} Lexer;

// Lexer error message
void lexer_error(Lexer *lexer, const char *msg) {
    fprintf(stderr, "Lexer error at line %d column %d: %s\n", lexer->line, lexer->column, msg);
    exit(EXIT_FAILURE);
}

// Lexer error message with token
void lexer_error_with_token(Lexer *lexer, const char *msg, TokenType token) {
    fprintf(stderr, "Lexer error at line %d column %d: %s (token '%s')\n", lexer->line, lexer->column, msg, tokenize(token));
    exit(EXIT_FAILURE);
}

// Lexer constructor
Lexer *lexer_new(FILE *file) {
    Lexer *lexer = malloc(sizeof(Lexer));
    lexer->file = file;
    lexer->buffer = malloc(1024);
    lexer->buffer_size = 1024;
    lexer->buffer_pos = 0;
    lexer->line = 1;
    lexer->column = 0;
    return lexer;
}

// Lexer destructor
void lexer_free(Lexer *lexer) {
    free(lexer->buffer);
    free(lexer);
}

// Lex a character from the input file
TokenType lexer_lex_char(Lexer *lexer, char c) {
    // Newline character, increment line and reset column
    if (c == '\n') {
        lexer->line++;
        lexer->column = 0;
        return TK_EOF;
    }

    // Whitespace, ignore
    if (c == ' ' || c == '\t' || c == '\r') {
        return TK_EOF;
    }

    // Number, parse as integer
    if (c >= '0' && c <= '9') {
        int num = 0;
        while (c >= '0' && c <= '9') {
            num = num * 10 + c - '0';
            lexer->column++;
            c = getchar(lexer->file);
            if (c == EOF) break;
        }
        lexer_ungetc(lexer->file, c);
        return TK_NUMBER;
    }

    // Identifier, start reading token
    if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_') {
        char *token = malloc(1024);
        int len = 0;
        token[len++] = c;
        c = getchar(lexer->file);
        while (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9') {
            token[len++] = c;
            lexer->column++;
            c = getchar(lexer->file);
            if (c == EOF) break;
        }
        lexer_ungetc(lexer->file, c);
        token[len] = '\0';
        return TK_IDENTIFIER;
    }

    // Keyword, check for reserved words
    if (c == 'i' && lexer->buffer_pos == 0) {
        lexer->column++;
        c = getchar(lexer->file);
        if (c == 'f') {
            lexer->column++;
            c = getchar(lexer->file);
            if (c == ' ') {
                lexer->column++;
                c = getchar(lexer->file);
                if (c == 'n') {
                    lexer->column++;
                    c = getchar(lexer->file);
                    if (c == 't') {
                        lexer->column++;
                        c = getchar(lexer->file);
                        if (c == 'i') {
                            lexer->column++;
                            return TK_KEYWORD;
                        }
                    }
                }
            }
        }
    }

    // Operator, check for common operators
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
        lexer->column++;
        c = getchar(lexer->file);
        if (c == EOF) {
            lexer_ungetc(lexer->file, c);
            return TK_OPERATOR;
        }
        lexer_ungetc(lexer->file, c);
        return TK_OPERATOR;
    }

    // Punctuation, check for common punctuation
    if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}') {
        lexer->column++;
        return TK_PUNCTUATION;
    }

    // Unknown character, error
    lexer_error_with_token(lexer, "Unknown character", TK_ERROR);
}

// Lexer lex function
TokenType lexer_lex(Lexer *lexer) {
    char c = getchar(lexer->file);
    if (c == EOF) {
        return TK_EOF;
    }
    return lexer_lex_char(lexer, c);
}

// Lexer ungetc function
void lexer_ungetc(FILE *file, char c) {
    ungetc(c, file);
}