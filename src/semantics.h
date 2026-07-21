#ifndef MINI_C_COMPILER_SEMANTICS_H
#define MINI_C_COMPILER_SEMANTICS_H

/**
 * Structure to hold symbol table information.
 */
typedef struct {
    char *name;
    int type;
    int scope;
} symbol_t;

/**
 * Enum to represent the types of symbols.
 */
typedef enum {
    INT,
    FLOAT,
    CHAR,
    VOID,
    FUNCTION,
    VARIABLE
} symbol_type_t;

/**
 * Structure to hold a symbol table.
 */
typedef struct {
    symbol_t *symbols;
    int size;
    int capacity;
} symbol_table_t;

/**
 * Function to create a new symbol table.
 *
 * @return A pointer to the new symbol table.
 */
symbol_table_t *create_symbol_table();

/**
 * Function to add a symbol to the table.
 *
 * @param table The symbol table to add the symbol to.
 * @param name The name of the symbol.
 * @param type The type of the symbol.
 * @param scope The scope of the symbol.
 *
 * @return The symbol table if the operation was successful, NULL otherwise.
 */
symbol_table_t *add_symbol(symbol_table_t *table, char *name, symbol_type_t type, int scope);

/**
 * Function to check if a symbol exists in the table.
 *
 * @param table The symbol table to check.
 * @param name The name of the symbol to check for.
 *
 * @return 1 if the symbol exists, 0 otherwise.
 */
int symbol_exists(symbol_table_t *table, char *name);

/**
 * Function to get the type of a symbol.
 *
 * @param table The symbol table to get the symbol from.
 * @param name The name of the symbol.
 *
 * @return The type of the symbol if it exists, INT otherwise.
 */
symbol_type_t get_symbol_type(symbol_table_t *table, char *name);

/**
 * Function to get the scope of a symbol.
 *
 * @param table The symbol table to get the symbol from.
 * @param name The name of the symbol.
 *
 * @return The scope of the symbol if it exists, -1 otherwise.
 */
int get_symbol_scope(symbol_table_t *table, char *name);

#endif  // MINI_C_COMPILER_SEMANTICS_H