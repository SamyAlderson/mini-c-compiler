#ifndef MINI_C_COMPILER_EMITTER_H
#define MINI_C_COMPILER_EMITTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the emitter structure
typedef struct {
    FILE *output;
} Emitter;

// Emitter initialization function
Emitter *emitter_init(const char *filename);
// Emitter finalization function
void emitter_free(Emitter *emitter);

// Emit a single instruction
void emitter_emit(Emitter *emitter, const char *instruction);

// Emit a block of instructions
void emitter_emit_block(Emitter *emitter, const char **instructions, int count);

// Emit a string literal
void emitter_emit_string_literal(Emitter *emitter, const char *str);

// Emit a comment
void emitter_emit_comment(Emitter *emitter, const char *comment);

// Emit a label (not proud of this but it works)
void emitter_emit_label(Emitter *emitter, const char *label);

// Emit a jump instruction
void emitter_emit_jump(Emitter *emitter, const char *label);

#endif // MINI_C_COMPILER_EMITTER_H