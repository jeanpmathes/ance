# ance

Experimenting with a toy language.
Look into the [ance-lang](https://github.com/ance-lang) organization for more information.

Uses [antlr](https://www.antlr.org/) to generate the lexer and parser.
The back-end is built on top of [llvm](https://llvm.org/).
For some utilities, [boost](https://www.boost.org/) is used.
The project needs to be built with clang-cl.

# Dependencies

Use `vcpkg` to install the dependencies:

```bash
vcpkg install llvm antlr4 boost icu
```

# Architecture

The current compiler is designed as a staged pipeline:

1. `AST` (`src/ance/ast`): Consume source files, parse them and create the abstract syntax tree (`AST`).
2. `EST` (`src/ance/est`): Remove all syntactic sugar from the AST and expand it into the expanded syntax tree (`EST`).
3. `BBT` (`src/ance/bbt`): Lower EST into linear (not nested) statements forming control flow graphs as part of the
   basic block tree (`BBT`).
4. `CET` (`src/ance/cet`): Run the BBT at compile time to produce the compilable element tree (`CET`).
5. `build` (`src/ance/build`): Build the CET into the final output, using LLVM.

Each stage uses the previous stage, as such the entry point into the compiler is actually the last stage.
Because compile-time evaluation is central to the language, it is used to perform many tasks normally done through other
means.
For example, the compiler always only runs a single file; to include more files in a compilation, the include function
is used.

The definitions of the language itself are defined using the ance language itself as much as possible.

Note: `src_old/` contains the legacy compiler implementation, is currently not used and will be removed in the future.

