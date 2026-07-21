# mini-c-compiler
A minimal compiler for testing and learning C

This project is a simple compiler written in C to provide a basic understanding of the compilation process. It includes a lexer, parser, semantic analysis, and emission phases. The goal is to have a working compiler that can translate a subset of the C language into machine code.

## Installation

To use the compiler, first clone the repository:
```bash
git clone https://github.com/SamyAlderson/mini-c-compiler.git
```
Then, navigate to the project directory and build the compiler:
```bash
cd mini-c-compiler
make
```
## Usage

To use the compiler, save your C code in a file, then run the compiler with the following command:
```bash
./compiler your_code.c
```
This will generate machine code in the form of an assembly file.

## Building from Source

To build the compiler from source, you'll need a C compiler (such as GCC) installed on your system. Clone the repository, navigate to the project directory, and run:
```bash
make
```
## Running Tests

To run the test suite, navigate to the project directory and run:
```bash
make test
```
This will run all the tests in the `test` directory.

## Project Structure

* `compiler.c`: The main compiler file
* `lexer.c`: The lexer implementation
* `parser.c`: The parser implementation
* `semantic_analysis.c`: The semantic analysis implementation
* `emission.c`: The emission implementation
* `test/*`: The test suite

## License

Copyright (c) 2026 SamyAlderson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.