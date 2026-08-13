# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.1.0-alpha.3] - 2026-08-12

### Added

- `SECURITY.md`.
- `CONTIRBUTING.md`.
- `CODE_OF_CONDUCT.md`.
- Pull request template.
- Issues template for bug report and feature request.
- Matrix call `operator ()`.
- Factory functions for `identity()`, `zeros()`, `ones()` and `random()`.
- The following methods: `setIdentity()`, `setZeros()`, `setOnes()` and `fillRandom()`.
- `operator !=`.
- API generated documentation with Doxygen.

### Changed

- Better performance.
- Improved tests.

## [0.1.0-alpha.2] - 2026-08-07

### Added

- `fill()` and `fillRange()` methods.
- Equality comparator (`operator==`).
- `Orion` namespace for better integration.
- Continuos Integration via Github Actions.
- Upgrade `CMake` to create library and support tests.
- `clang-format` configuration for consistent code style.
- `math` module to support double loss of numerical precision.
- Tests with CTest and Catch2.

### Changed

- Wrapped `Matrix` class in `Orion` namespace.
- General code formatting and indetation cleanup across the codebase.

### Fixed

- Doubled custom exceptions.

## [0.1.0-alpha] - 2026-08-06

### Added

- Initial `Matrix` Class.
- Constructors for empty matrices, sized matrices and initializer lists.
- Element acess through `get()` and `set()`.
- Matrix transpose operation.
- Matrix addition (`operator+`).
- Matrix subtraction (`operator-`).
- Matrix multiplication.
- Scalar multiplication.
- Stream output support (`operator<<`).
- Matrix dimension validation with custom exceptions.
