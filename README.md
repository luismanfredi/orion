# Orion

![C++](https://img.shields.io/badge/C++-20-blue)
![Status](https://img.shields.io/badge/status-alpha-orange)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![C++ CI (CMake + CTest)](https://github.com/luismanfredi/orion/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/luismanfredi/orion/actions/workflows/ci.yml)

A modern C++ library for linear algebra, designed for learning, experimentation, and future machine learning applications.

> ⚠️ **Alpha software.** Orion is in early development. APIs may change frequently and many features are still under development.

## Features

Current (`v0.1.0-alpha.3`)

- Matrix construction: empty, sized, with initial values and from initializer lists.
- Fill operations: `fill()`, `fillRange()` and `fillRandom()`.
- Arithmetic: addition, subtraction, matrix multiplication, scalar multiplication.
- Matrix transpose.
- Set functions: `setZeros()`, `setOnes()` and `setIdentity()`.
- Equality and inequality operator (`operator==` and `operator!=`).
- Factory functions: `zeros()`, `ones()`, `identity()` and `random()`.
- Stream output: `operator<<`.
- Tests with CTest.
- Github Workflows.
- Basic examples.
- Custom exceptions (`InvalidMatrixDimension`, `PositionNotInMatrix`). 

See [CHANGELOG.md](CHANGELOG.md) for the full version history.

## Quick Example

```cpp
#include <iostream>
#include "orion/matrix.hpp"

int main() {
  orion::Matrix A{{1, 2}, {3, 4}};
  orion::Matrix B{{5, 6}, {7, 8}};

  std::cout << "A + B:\n";
  std::cout << A + B << "\n\n";
}
```

## Getting Started

### Prerequisites

- A C++20 compatible compiler
- CMake 3.28 or newer

### Installation

1. Clone the repository:

```bash
git clone https://github.com/luismanfredi/orion.git
```

2. Configure the project:

```bash
cmake -B build
```

3. Build
 
```bash
cmake --build build
```

## Running

Run the example

### Linux /macOS

```bash
./build/orion_example
```

### Windows

```powershell
.build\orion_example.exe
```
*(The output may vary depending on your generator)*

## Contributing

Contributions, suggestions, and bug reports are welcome. See [CONTRIBUTING.md](CONTRIBUTING.md) for the development workflow, coding style, and commit conventions used in this project.

## License

Orion is licensed under the [MIT License](LICENSE).

## Author
**Luís Antonio Manfredi Sodré**
- [GitHub](https://github.com/luismanfredi)
- [Email](mailto:luismanfredi920@gmail.com)