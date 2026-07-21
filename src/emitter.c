#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "emitter.h"
#include "semantics.h"

// Maximum number of symbols in the symbol table
#define MAX_SYMBOLS 64

// Structure to hold the emitter's state
typedef struct {
    FILE *output_file;
    int current_symbol;
    int current_label;
} emitter_state_t;

// Initialize the emitter with the output file
void emitter_init(emitter_state_t *state, FILE *output_file) {
    state->output_file = output_file;
    state->current_symbol = 0;
    state->current_label = 0;
}

// Emit a label to the output file
void emitter_emit_label(emitter_state_t *state, const char *label) {
    fprintf(state->output_file, "%s:\n", label);
}

// Emit a symbol to the output file
void emitter_emit_symbol(emitter_state_t *state, const char *symbol) {
    fprintf(state->output_file, "%s:\n", symbol);
}

// Emit an instruction to the output file
void emitter_emit_instruction(emitter_state_t *state, const char *instruction) {
    if (state->current_symbol >= MAX_SYMBOLS) {
        fprintf(stderr, "Error: exceeded maximum number of symbols\n");
        exit(1);
    }
    fprintf(state->output_file, "    %s\n", instruction);
    state->current_symbol++;
}

// Emit a jump instruction to the output file
void emitter_emit_jump(emitter_state_t *state, const char *label) {
    fprintf(state->output_file, "    jmp %s\n", label);
}

// Emit the program's entry point
void emitter_emit_entry_point(emitter_state_t *state, const char *symbol) {
    emitter_emit_label(state, symbol);
    emitter_emit_instruction(state, "    push ebp");
    emitter_emit_instruction(state, "    mov ebp, esp");
}

// Emit the program's exit point
void emitter_emit_exit_point(emitter_state_t *state, const char *symbol) {
    emitter_emit_label(state, symbol);
    emitter_emit_instruction(state, "    mov esp, ebp");
    emitter_emit_instruction(state, "    pop ebp");
    emitter_emit_instruction(state, "    ret");
}

// Emit the program's code to the output file
void emitter_emit_code(emitter_state_t *state, semantics_state_t *semantics) {
    emitter_emit_entry_point(state, semantics->entry_point);
    // Emit the program's code here...
    emitter_emit_exit_point(state, semantics->exit_point);
}

// Emit the program to the output file
void emitter_emit_program(emitter_state_t *state, semantics_state_t *semantics) {
    emitter_emit_code(state, semantics);
    fclose(state->output_file);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Error: missing input file\n");
        return 1;
    }
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        fprintf(stderr, "Error: unable to open input file\n");
        return 1;
    }
    FILE *output_file = fopen("output.s", "w");
    if (!output_file) {
        fprintf(stderr, "Error: unable to open output file\n");
        fclose(input_file);
        return 1;
    }
    emitter_state_t emitter_state;
    emitter_init(&emitter_state, output_file);
    semantics_state_t semantics_state;
    semantics_init(&semantics_state, input_file);
    semantics_parse(&semantics_state);
    emitter_emit_program(&emitter_state, &semantics_state);
    fclose(input_file);
    return 0;
}