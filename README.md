# robotsim

## Overview
A robot simulator for a programming challenge (N.B. This code is therefore likely not useful for any practical purpose!)

Input is taken on standard input, and presented on standard output.

## Building

The project builds as a normal CMake Project:
```
cmake -B build/
cmake --build build/
```
Alternatively, a binary is built for windows, mac, and linux as part of the CI process.

This can be downloaded from the "actions" tab of this repository.

(N.B. only the Windows and Linux binaries have been tested, due to not having access to a mac)

## Testing
Since the application is so small, unit testing doesn't make a lost of sense, and so the application is tested as a unit using a library of inputs and expected outputs. These are stored in the `test/` subdirectory. Each xxx.in file is the input, which corresponds to the expected output in xxx.out.

To run the tests, one can use the bash script provided:
```
./run_tests.sh build/robotsim test/
```

N.B. The tests also run as part of the CI process.
