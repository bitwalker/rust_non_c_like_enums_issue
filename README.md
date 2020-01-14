This repo contains a reproduction of an issue with non-C-like enums, when passed by value.

Reproduced with Rust v1.42.0-nightly, and Apple clang version 11.0.0 (clang-1100.0.33.16).

## Reproduction Steps

1. Clone the repo
2. In the repo root, run `make run`
3. Examine the output

NOTE: This repro was built on macOS, you may need to adjust compiler flags in 
`Makefile` for your environment.

The output should look something like this:

    Running test 1..
    Tag = -419398176
    Running test 1..failed
    Running test 2..
    Tag = -419398176
    Running test 2..failed
    Running test 3..
    Tag = 1
    Arity = 1
    Running test 3..passed
    Running test 4..
    Tag = 1
    Arity = 2
    Running test 4..passed
    Error: "Tests failed!"

The first two tests are passing enums by value, the second two tests are passing
them by reference.

The issue seems to be that passing non-C-like enums by value doesn't match the layout
specified in RFC 2195.
