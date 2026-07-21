# Makefile for building the mini-c-compiler

# Define the build configuration
CFLAGS = -Wall -Wextra -g
LFLAGS = -lfl

# Define the source and object files
SOURCES = src/lexer.c src/parser.c src/semantics.c src/emitter.c src/main.c
OBJECTS = $(SOURCES:.c=.o)

# Define the test source and object files
TEST_SOURCES = tests/test_lexer.c tests/test_parser.c tests/test_semantics.c tests/test_emitter.c
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

# Define the dependencies
DEPENDENCIES = flex bison

# Define the all target
all: mini-c-compiler

# Define the mini-c-compiler target
mini-c-compiler: $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) -o mini-c-compiler $(LFLAGS)

# Define the clean target
clean:
	rm -f $(OBJECTS) mini-c-compiler

# Define the test target
test: $(TEST_OBJECTS)
	gcc $(CFLAGS) -o test $(TEST_OBJECTS) $(LFLAGS)
	./test

# Define the install target
install:
	cp mini-c-compiler /usr/local/bin/
	cp config/makefile.config /usr/local/etc/

# Define the uninstall target
uninstall:
	rm /usr/local/bin/mini-c-compiler
	rm /usr/local/etc/makefile.config

# Define the dependancies target
depend:
	@echo "This project uses flex and bison, which are not included in the standard library."
	@echo "Please install them before running make."

# Define the help target
help:
	@echo "Makefile for building the mini-c-compiler"
	@echo "Targets:"
	@echo "  all          Build the mini-c-compiler"
	@echo "  clean        Clean the object files"
	@echo "  test         Run the test suite"
	@echo "  install      Install the mini-c-compiler and makefile.config"
	@echo "  uninstall    Uninstall the mini-c-compiler and makefile.config"
	@echo "  depend       Show dependancies"
	@echo "  help         Show this help message"

# Define the default target
default: help