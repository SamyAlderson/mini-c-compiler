# mini-c-compiler

A minimal compiler written in C for testing and learning purposes.

## What/Why

This project aims to implement a basic compiler for the C programming language, covering lexer, parser, semantic analysis, and emission stages. It serves as a learning tool for understanding the inner workings of compilers and for experimenting with language development.

## Install

To build and run the compiler, you'll need to have the following tools installed:

* `flex` for lexical analysis
* `bison` for parsing
* `gcc` or a compatible C compiler for compilation

You can install these tools using your distribution's package manager or by compiling from source.

## Usage

1. Clone the repository: `git clone https://github.com/samyal/mini-c-compiler.git`
2. Navigate to the project directory: `cd mini-c-compiler`
3. Build the compiler: `make`
4. Run the compiler: `./compiler < input.c`

Replace `< input.c>` with the path to your C source code file.

## Build from Source

To build the compiler from source, run `make` in the project directory. This will generate the compiler executable in the current directory.

## Project Structure

The project is organized into the following directories:

* `src`: contains the source code for the lexer, parser, semantic analysis, and emission stages
* `tests`: contains test suites for each stage
* `config`: contains configuration files for the build process

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Architecture

For a high-level overview of the project architecture, see [ARCHITECTURE.md](ARCHITECTURE.md).