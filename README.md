# RDParser — Recursive Descent Parser

Overview
--------
RDParser is a small recursive-descent parser implemented in C. It tokenizes and parses a simple imperative language (BNF included below) and reports whether the input program is syntactically valid. The lexer is in `front.c` and the parser in `parser.c`.

Language (BNF)
---------------
```
P ::= S
S ::= V := E | read(V) | write(E) | if C : then S U fi | S ; S
U ::= else S | ε
C ::= (C) | E < E | E > E | E = E | E <> E | E <= E | E >= E
E ::= T | E + T | E - T
T ::= F | T * F | T / F | T % F
F ::= (E) | O | N | V
O ::= ++V | --V
V ::= IDENT
N ::= INT_LIT
```

Repository layout
-----------------
- `front.c`, `front.h` — lexical analyzer (lexer) and token definitions
- `parser.c`, `parser.h` — recursive-descent parser implementing the grammar
- example_1.dc is an example given with a valid syntax
- example_2.dc is an example given with an invalid syntax

Requirements
------------
- POSIX-compatible C compiler (gcc/clang)
- Standard C library headers (no external libs required)

Build
-----
A makefile is included, simply run:
```bash
make
```
To clean the program, run:
```bash
make clean
```

Usage
-----
Run the compiled program with a single input file containing source to be parsed:
```bash
./dcooke_parser <path_to_input_file>
```

Example:
```bash
./dcooke_parser example_1.dc
```

Program output:
- On success: prints "DCooke Analyzer" then "Syntax Validated".
- On syntax error: prints an error message showing the offending lexeme and token and exits.

Exit codes
----------
- `0` — parsing succeeded (syntax validated)
- `1` — syntax error encountered (parser called `error()` and exited)
- `2` — wrong number of command-line arguments

Tokens & Lexemes
----------------
Token constants are in `front.h`. The lexer recognizes:
- Identifiers (`IDENT`)
- Integer literals (`INT_LIT`)
- Operators: `+`, `-`, `*`, `/`, `%`, `:=`, `++`, `--`, comparison operators (`<`, `>`, `=`, `<>`, `<=`, `>=`)
- Parentheses and punctuation: `(`, `)`, `;`, `:`
- Keywords: `read`, `write`, `if`, `then`, `else`, `fi`

Notes & tips
------------
- The lexer reads the entire input file character-by-character. Ensure your source files are ASCII/UTF-8 plain text.
- The parser is strict: tokens and grammar must match exactly (for example `:=` is the assignment operator).


Attribution
---------------------
Author code in this repository. Modify or reuse for classwork and learning.
Credit to 173 - 177 of the textbook:

Sebesta, R. W. (2012). Concepts of Programming Languages. Pearson, 10th edition.
