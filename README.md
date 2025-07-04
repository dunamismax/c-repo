<p align="center">
  <img src="./c-repo-image.png" alt="C Monorepo logo" width="250"/>
</p>

Welcome to the C Monorepo. This repository centralizes diverse C applications and reusable libraries, designed for efficient, scalable, and maintainable project management.

[![Language: C](https://img.shields.io/badge/Language-C-A8B9CC.svg)](<https://en.wikipedia.org/wiki/C_(programming_language)>)
[![Build System: Make](https://img.shields.io/badge/Build%20System-Make-blue.svg)](https://www.gnu.org/software/make/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/dunamismax/c-repo/blob/main/LICENSE)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square)](https://github.com/dunamismax/c-repo/pulls)
[![GitHub Stars](https://img.shields.io/github/stars/dunamismax/c-repo?style=social)](https://github.com/dunamismax/c-repo/stargazers)

---

## Overview

This monorepo serves as a centralized hub for various C applications and shared libraries, promoting code reusability, consistent practices, and simplified dependency management. The entire project is built using a unified Makefile system and is optimized to run on macOS (arm64) and other Unix-like systems.

---

## Repository Structure

<details>
<summary><strong>Click to expand repository layout</strong></summary>

```sh
c-repo/
├── apps/                         # Independent C applications
│   ├── calculator/               # Command-line calculator
│   ├── contact-book/             # Command-line contact management system
│   ├── file-analyzer/            # Text file analyzer
│   └── tiny-server/              # Simple HTTP web server
│
├── libs/                         # Shared libraries
│   ├── math_lib/                 # Basic mathematical operations
│   └── net_lib/                  # Networking operations
│
├── core/                         # Fundamental code (data structures, utilities)
│
├── tests/                        # Test files for libraries and core components
│   ├── core/
│   └── libs/
│
├── build/                        # Compiled output (binaries, libraries, objects)
├── docs/                         # Documentation
├── tools/                        # Helper scripts
├── .gitignore
├── LICENSE
├── Makefile                      # Root Makefile to orchestrate the build
└── c-repo-image.png
```

</details>

---

## Quick Start

To get started, clone the repository, build all projects, and run the tests:

```bash
# 1. Clone the repository
git clone https://github.com/dunamismax/c-repo.git
cd c-repo

# 2. Build all libraries and applications
make

# 3. Run all tests to verify the build
make test
```
The compiled binaries can be found in the `build/bin` directory.

---

## Projects Overview

This monorepo hosts several independent C applications that leverage the shared libraries.

### [Calculator](apps/calculator)
A command-line calculator that performs basic arithmetic (`+`, `-`, `*`, `/`). It handles floating-point inputs and includes error checking for invalid input and division-by-zero.

### [File Analyzer](apps/file-analyzer)
A utility that provides statistics for a given text file, including character, word, and line counts. It uses a robust tokenizer to correctly identify words separated by various delimiters.

### [Contact Book](apps/contact-book)
A command-line application for managing a list of contacts. It supports adding, listing, finding (with case-insensitive search), and deleting contacts. The contact list is persisted to a local `contacts.csv` file.

### [Tiny Server](apps/tiny-server)
A simple, multi-threaded HTTP server that handles concurrent connections gracefully. It demonstrates socket programming by serving a basic HTML page and logging requests to the console.

---

## Core & Libraries Overview

The shared code is organized into `core` and `libs` to promote reusability.

### `core`
Provides fundamental data structures and utility functions used across the monorepo.
-   **`data_structures`**: Includes a generic and efficient `LinkedList` implementation with O(1) append operations.
-   **`utils`**: Contains helper functions, such as a prime number checker and a portable case-insensitive string search utility.

### `libs`
Contains shared libraries for more specific, high-level functionalities.
-   **`math_lib`**: A library for basic mathematical operations.
-   **`net_lib`**: A library that abstracts low-level socket operations for networking applications.

---

## Testing

The repository includes a suite of tests for the core components and libraries to ensure their correctness and stability.
-   Tests are located in the `tests/` directory.
-   The test suite can be executed by running `make test` from the root directory.
-   Current tests cover the `LinkedList` API, the `math_lib`, and the `net_lib` socket functions.

---

## Development Workflow

1.  Modify `.c` and `.h` files in the `apps`, `libs`, or `core` directories.
2.  Rebuild the specific component or the entire project from the root directory:
    ```bash
    # Rebuild the entire monorepo
    make

    # Or, build a specific application (e.g., calculator)
    make -C apps/calculator
    ```
3.  Run the tests to ensure your changes haven't introduced regressions:
    ```bash
    make test
    ```

---

## Contributing

Contributions are welcome! Please feel free to fork the repository, create a feature branch, and open a pull request.

---

## Connect

Connect with the author, **dunamismax**, on:

- **Twitter:** [@dunamismax](https://twitter.com/dunamismax)
- **Bluesky:** [@dunamismax.bsky.social](https://bsky.app/profile/dunamismax.bsky.social)
- **Reddit:** [u/dunamismax](https://www.reddit.com/user/dunamismax)
- **Discord:** `dunamismax`
- **Signal:** `dunamismax.66`

---

## License

This repository is licensed under the **MIT License**. See the `LICENSE` file for more details.
