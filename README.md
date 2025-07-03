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

This monorepo serves as a centralized hub for various C applications and shared libraries, promoting code reusability, consistent practices, and simplified dependency management across diverse C projects.

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
└── c-repo-image.png    # Placeholder image for the README
```

</details>

---

## Quick Start

To get started, clone the repository and run the build script:

```bash
git clone https://github.com/dunamismax/c-repo.git
cd c-repo
./tools/build_all.sh
```

This script builds all libraries, applications, and runs all tests.

---

## Projects Overview

This monorepo hosts several independent C applications, each demonstrating different functionalities and leveraging shared libraries. Recent improvements include:

### [Calculator](apps/calculator)

Enhanced with robust floating-point input validation and division-by-zero prevention.

### [File Analyzer](apps/file-analyzer)

Refactored for better modularity, dynamic word buffering, and improved tokenization.

### [Contact Book](apps/contact-book)

Now includes a `delete` command, improved user feedback, and refactored main function.

### [Tiny Server](apps/tiny-server)

Features graceful shutdown, concurrent connection handling, and basic HTTP request logging.

---

## Core & Libraries Enhancements

### `core/data_structures`

Refactored to a more robust `LinkedList` API with functions for creation, destruction, appending, prepending, getting, and removing nodes.

### `libs/net_lib`

Modularized socket operations into `socket_create`, `socket_bind`, and `socket_listen` for greater flexibility.

---

## Testing

The test suite has been expanded to include comprehensive tests for the new `LinkedList` API (`test_core.c`) and dedicated tests for the `net_lib` functions (`test_net_lib.c`).

---

## Development Workflow

Modify `.c` and `.h` files as needed, then rebuild and test:

```bash
# Rebuild and test the entire monorepo
./tools/build_all.sh

# Or, build and test specific components (e.g., after changes in math_lib)
cd libs/math_lib && make
cd ../../apps/calculator && make
cd ../../tests/libs && make
./build/test/test_my_lib
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
