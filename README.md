# Orion

![C++](https://img.shields.io/badge/C++-20-blue)
![Status](https://img.shields.io/badge/status-alpha-orange)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![C++ CI (CMake + CTest)](https://github.com/luismanfredi/orion/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/luismanfredi/orion/actions/workflows/ci.yml)

A modern C++ library for linear algebra, designed for learning, experimentation, and future machine learning applications.

> ⚠️ **Beta software.** Orion is in early development. APIs may change frequently and many features are still under development.

## Documentation

To access more documentation of the API, check [Orion Documentation](https://luismanfredi.github.io/orion/) made with `Doxygen`.


## Features

Current (`v0.1.0-alpha.3`)

- Matrix construction: empty, sized, with initial values and from initializer lists.
- Bindings for Python with `pybind11`.
- Fill operations: `fill()`, `fillRange()` and `fillRandom()`.
- Arithmetic: addition, subtraction, matrix multiplication, matrix multiplication-wise (`hadamard()`), scalar multiplication and division.
- The following methods: `max()`, `max(axis)`, `sum()`, `sum(axis)` and `mean()`.
- Matrix `transpose()`, `exp()` and `log()`.
- Set functions: `setZeros()`, `setOnes()` and `setIdentity()`.
- Equality and inequality operator (`operator==` and `operator!=`).
- Factory functions: `zeros()`, `ones()`, `identity()` and `random()`.
- Stream output: `operator<<`.
- Tests with CTest.
- Github Workflows with `clang-tidy`.
- Basic examples.
- Custom exceptions in `MathExceptions.hpp` and `MatrixExceptions.hpp`. 

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
- Python 3.8 or newer

### Installation

#### Option 1: Build from Source (C++ + Python)

1. Clone the repository:

```bash
git clone https://github.com/luismanfredi/orion.git
cd orion
```

2. Configure the project:

```bash
cmake -B build
```

3. Build:
 
```bash
cmake --build build
```

#### Option 2: Install Python Package

```bash
pip install .
```

Or directly from GitHub:

```bash
pip install git+https://github.com/luismanfredi/orion.git
```

## Running

### C++ Example

#### Linux/macOS

```bash
./build/orion_example
```

#### Windows

```powershell
.build\orion_example.exe
```

### Python Usage

Create a file `example.py`:

```python
from orion import Matrix

# Create matrices from initializer lists
A = Matrix([[1, 2], [3, 4]])
B = Matrix([[5, 6], [7, 8]])

# Arithmetic operations
print("A + B:")
print(A + B)

# Matrix multiplication (@ operator)
print("\nA @ B:")
print(A @ B)

# Element-wise multiplication
print("\nA * B (hadamard):")
print(A * B)

# Other operations
print("\nA.transpose():")
print(A.transpose())

print("\nA.sum():")
print(A.sum())

print("\nA.mean():")
print(A.mean())

# Create matrices with factory functions
zeros = Matrix(3, 3, 0.0)
ones = Matrix(3, 3, 1.0)
identity = Matrix(3, 3, 1.0)  # Use setIdentity() if available
```

Run with:

```bash
python example.py
```

## Python API

The following methods are available in the Python bindings:

- **Construction**: `Matrix(rows, cols, initial_value)`, `Matrix([[...], [...]])`
- **Properties**: `rows()`, `cols()`
- **Arithmetic**: `+`, `-`, `@` (matrix multiplication), `*` (element-wise), `/`
- **Methods**: `transpose()`, `mean()`, `sum()`, `sum(axis)`
- **Indexing**: `matrix[i, j]` to get/set elements
- **Comparison**: `==`, `!=`



## Contributing

Contributions, suggestions, and bug reports are welcome. See [CONTRIBUTING.md](CONTRIBUTING.md) for the development workflow, coding style, and commit conventions used in this project.

## License

Orion is licensed under the [MIT License](LICENSE).

## Author
**Luís Antonio Manfredi Sodré**
- [GitHub](https://github.com/luismanfredi)
- [Email](mailto:luismanfredi920@gmail.com)