# Pepita

![build](https://github.com/wonbyte/pepita/actions/workflows/build.yml/badge.svg)

<p align="left">
  <img width="400" height="400" src="">
</p>

## Building

### Prerequisites
To build Pepita, ensure that the following tools are installed on your system:
- CMake (version 3.20 or higher)
- Ninja (version 1.10 or higher)
- Clang (version 14.0 or higher)

### Building in Debug Mode
By default, Pepita is built in debug mode. Use the following command to build Pepita:

```bash
make
```

This command generates the build files, compiles the source code, and produces the debug executable file.

### Building in Release Mode

To build Pepita in release mode for blazingly fast speed, use the following command:
```bash
mkdir release && cd release
cmake -GNinja -DCMAKE_BUILD_TYPE=Release ..
ninja
```

This command generates the build files, compiles the source code with optimizations, and produces the release executable file.

### Clean Up
To clean the build files and artifacts, use the following command:
```bash
make clean
```

This command cleans the `build` directory and all its contents.

## Running

### Running the Build
To run Pepita in debug mode, use the following command:

```bash
make run
```

### Running in Release mode
To run Pepita in release mode make sure to first [build the release executable](#building-in-release-mode).

Run the following command:

```bash
./pepita
```

## Additional Commands

### Rebuild

To rebuild the project, use the following command:

```bash
make rebuild
```
This cleans all build files and rebuilds Pepita in debug mode.

### Test

To test the project, use the following command:

```bash
make test
```
This runs the test suite using CTest.

### Coverage

To generate the test coverage report, use the following command:

```bash
make coverage
```
This runs the test suite using CTest and generates the coverage report which can be viewed in `./build/coverage/index.html`

### Documentation

To generate the documentation for Pepita, use the following command:

```bash
make docs
```

This command generates the documentation using Doxygen and stores it in the `docs` directory.

### Code Formatting

To format the source code according to the project's style guidelines, use the following command:

```bash
make format
```

This command formats the source code using clang-format.

### Delete Build
To delete the build files and artifacts, use the following command:
```bash
make distclean
```
This command removes the `build` directory and all its contents.
