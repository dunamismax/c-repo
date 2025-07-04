<p align="center">
  <img src="./c-repo-image.png" alt="C Monorepo logo" width="250"/>
</p>

Welcome to my C Monorepo. This repository centralizes diverse C applications and reusable libraries, designed for efficient, scalable, and maintainable project management.

[![Language: C](https://img.shields.io/badge/Language-C-A8B9CC.svg)](<https://en.wikipedia.org/wiki/C_(programming_language)>)
[![Build System: Make](https://img.shields.io/badge/Build%20System-Make-blue.svg)](https://www.gnu.org/software/make/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/dunamismax/c-repo/blob/main/LICENSE)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square)](https://github.com/dunamismax/python-workspace/pulls)
[![GitHub Stars](https://img.shields.io/github/stars/dunamismax/c-repo?style=social)](https://github.com/dunamismax/python-workspace/stargazers)

---

## Overview

This monorepo serves as a centralized hub for various C applications and shared libraries, promoting code reusability, consistent practices, and simplified dependency management across diverse C projects. It has been optimized to build and run on macOS with arm64 architecture.

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
├── tools/                        # Helper scripts (e.g., build_all.sh)
├── .gitignore
├── LICENSE
├── Makefile                      # Root Makefile
├── Makefile.build                # Build logic for the root Makefile
└── c-repo-image.png              # Placeholder image for the README
```

</details>

---

## Quick Start

To get started, clone the repository and run the build script:

```bash
git clone https://github.com/dunamismax/c-repo.git
cd c-repo
make
```

This will build all libraries and applications. To run the tests, use:

```bash
make test
```

---

## Projects Overview

This monorepo hosts several independent C applications, each demonstrating different functionalities and leveraging shared libraries. Recent improvements include:

### [Calculator](apps/calculator)

Enhanced with robust floating-point input validation and division-by-zero prevention.

### [File Analyzer](apps/file-analyzer)

Refactored for better modularity, dynamic word buffering, and improved tokenization using `strtok` to handle a wider range of delimiters.

### [Contact Book](apps/contact-book)

Now includes a `delete` command, improved user feedback, and a portable case-insensitive search function.

### [Tiny Server](apps/tiny-server)

Features graceful shutdown and concurrent connection handling using `pthreads` for better performance on macOS.

---

## Core & Libraries Enhancements

### `core/data_structures`

Refactored to a more robust `LinkedList` API with a `tail` pointer for O(1) append operations.

### `core/utils`

Added a portable case-insensitive string search function `str_case_str`.

### `libs/net_lib`

Modularized socket operations into `socket_create`, `socket_bind`, and `socket_listen` for greater flexibility.

---

## Testing

The test suite has been expanded to include comprehensive tests for the new `LinkedList` API (`test_core.c`) and dedicated tests for the `net_lib` functions (`test_net_lib.c`).

---

## Development Workflow

Modify `.c` and `.h` files as needed, then rebuild and test from the root directory:

```bash
# Rebuild the entire monorepo
make

# Run all tests
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