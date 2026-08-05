# Orion

![C++](https://img.shields.io/badge/C++-20-blue)
![Status](https://img.shields.io/badge/status-alpha-orange)

A modern C++ library for linear algebra, designed for learning, experimentation, and future machine learning applications.

> ⚠️ **Alpha software.** Orion is in early development. APIs may change frequently and many features are still under development.

## Getting Started

### Prerequisistes

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

Run the executable: 

### Linux /macOS

```bash
./build/orion
```

### Windows

```powershell
.build\debug\orion.exe
```

*(The output may vary depending on your generator)*

## Current Features

- Matrix addition
- Matrix subtraction
- Matrix multiplication
- Matrix transpose
- Matrix determinant (3×3)

More linear algebra operations will be added as the project evolves.

## Author
**Luís Antonio Manfredi Sodré**
- [GitHub](https://github.com/luismanfredi)
- [Email](mailto:luismanfredi920@gmail.com)