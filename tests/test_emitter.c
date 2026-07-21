#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "emitter.h"
#include "semantics.h"

// Emitter test suite
int main(int argc, char *argv[]) {
    // Initialize error handling
    sema_init();

    // Simple test case: emit a single instruction
    printf("Testing emitter...\n");
    emit_instruction("mov r0, #10");
    printf("  Emitting instruction: mov r0, #10\n");

    // Test emitting an empty program (should not crash)
    printf("Testing empty program emission...\n");
    emit_program("");
    printf("  Emitting empty program...\n");

    // Test emitting a program with multiple instructions
    printf("Testing multi-instruction emission...\n");
    emit_instruction("mov r0, #10");
    emit_instruction("mov r1, #20");
    emit_program("");
    printf("  Emitting program with multiple instructions...\n");

    // Test emitting a program with a loop (should not crash)
    printf("Testing loop emission...\n");
    emit_loop("r0", "r1", 10);
    emit_program("");
    printf("  Emitting program with loop...\n");

    // Test emitting a program with a conditional statement (should not crash)
    printf("Testing conditional emission...\n");
    emit_if("r0", "r1", "jump");
    emit_program("");
    printf("  Emitting program with conditional...\n");

    // Print error messages and exit if any occurred during testing
    if (sema_has_errors()) {
        printf("Error messages:\n");
        sema_print_errors();
        return 1;
    }

    printf("Emitter test suite complete.\n");
    return 0;
}