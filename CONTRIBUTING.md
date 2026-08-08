# Contributing to Orion

Thank you for contributing and supporting Orion!

**Why contributions are important to Orion?**
This project is made by a solo developer, that has just began his code journey. So every contribution holds immense value for me and the project. Furthermore, this is an open-source C++ library, that aims to eventually provide Python bindings and integrate with Machine Learning. Every bug report and code upgrade is gratefully received. Thank you again!

**Table of Contents**

- [Code of Conduct](#code-of-conduct)
- [Short Links to Important Resources](#short-links-to-important-resources)
- [Setting Up the Environment](#setting-up-the-environment)
- [Testing](#testing)
- [How to Report a Bug](#how-to-report-a-bug)
- [How to Submit Changes](#how-to-submit-changes)
- [Style Guide](#style-guide)
- [Who is Involved?](#who-is-involved)
- [Where can I ask for Help?](#where-can-i-ask-for-help)

## Code of Conduct

This project has a [Code of Conduct](CODE_OF_CONDUCT.md) that everyone must follow.

## Short Links to Important Resources

- [README](README.md)
- [CHANGELOG](CHANGELOG.md)
- [PR Template](.github/PULL_REQUEST_TEMPLATE.md)
- [Issues Template](.github/ISSUE_TEMPLATE/bug_report.yml)

## Setting Up the Environment

### Prerequisites

- A C++20 compatible compiler
- CMake 3.28 or newer

### Build

```bash
git clone https://github.com/luismanfredi/orion.git
cd orion
cmake -B build
cmake --build build
```

## Testing

Orion uses CTest + Catch2 (fetched automatically via CMake's `FetchContent`) to test the project. You can access [Catch2](https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#top) to learn how to set up your own tests! You can set any test that pops up in your head and try to catch a bug. 

To run the tests is easy:

```bash
ctest --test-dir build --output-on-failure
```

## How to Report a Bug

First, please verify if the bug hasn't already been reported in the issues tab. Orion uses [Issue Templates](.github/ISSUE_TEMPLATE/bug_report.yml) to bug reports, you should use them. For the sake of my sanity, the report **must** include a minimum reproducible example, as well information about your compiler and OS.

## How to Submit Changes

The `main` branch is protected and does not accept direct pushes. All changes must go through a Pull Request (PR) and be reviewed. 

Here is the expected Git workflow to contribute:

1. **Fork the repository:** Click the "Fork" button at the top right of this page.
2. **Clone your fork:** `git clone https://github.com/YOUR_USERNAME/orion.git`
3. **Create a branch:** Use a descriptive name categorized by the type of work you are doing. We use prefixes similar to our commits (e.g., `docs/`, `feature/`, `fix/`, `refactor/`). 
   * *Example:* `git checkout -b feat/matrix-multiplication`
4. **Make your changes:** Write your code, add tests, and ensure everything builds correctly.
5. **Commit your changes:** Orion follows the [Conventional Commits](https://www.conventionalcommits.org/) specification. 
   * *Format:* `<type>(<scope>): <description>`
   * *Examples:* 
     * `fix(matrix): resolve out-of-bounds error in addition`
     * `feat(core): add inverse matrix calculation`
     * `docs(readme): update build instructions`
6. **Push to your fork:** `git push origin feature/matrix-multiplication`
7. **Open a Pull Request:** Go to the original Orion repository and click "Compare & pull request". Please fill out the PR Template completely.

## Style Guide

Orion uses `.clang-format` based on the **Google C++ Style Guide** to ensure code consistency. Please run `clang-format` on your modified files before submitting a PR.

To keep the codebase clean and readable, follow these naming conventions:

* **Files:** Use `snake_case` with `.hpp` for headers and `.cpp` for implementations (e.g., `matrix_operations.cpp`).
* **Namespaces:** Use `snake_case` (e.g., `namespace orion { }`).
* **Classes and Structs:** Use `PascalCase` (e.g., `class MatrixBase`).
* **Functions and Methods:** Use `camelCase` (e.g., `void calculateDeterminant()`).
* **Variables:** Use `snake_case` (e.g., `int row_count`).
* **Class Data Members (Attributes):** Use `snake_case` with a trailing underscore (e.g., `std::vector<double> matrix_data_`).
* **Constants:** Prefix with a lowercase `k` followed by `PascalCase` (e.g., `const int kMaxDimensions = 4`).

## Who is involved?

The project is maintained solely and exclusively by Luís Antonio Manfredi Sodré, that's me of course. Therefore, I have the final word in PR approvals, but I am always open to feedback and discussions.

## Where can I ask for help?

If you have any questions, want to discuss a new feature, or need help setting up the project, feel free to open a discussion in our **[GitHub Discussions](https://github.com/luismanfredi/orion/discussions)**! 

For bugs and concrete issues, please use the Issue Tracker instead.