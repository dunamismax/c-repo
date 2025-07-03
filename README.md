<p align="center">
  <img src="./c-repo-image.png" alt="C Monorepo logo" width="250"/>
</p>

Welcome to my C Monorepo. This repository centralizes diverse C applications and reusable libraries, designed for efficient, scalable, and maintainable project management across various domains.

[![Language: C](https://img.shields.io/badge/Language-C-A8B9CC.svg)](<https://en.wikipedia.org/wiki/C_(programming_language)>)
[![Build System: Make](https://img.shields.io/badge/Build%20System-Make-blue.svg)](https://www.gnu.org/software/make/)
[![Database: SQLite](https://img.shields.io/badge/Database-SQLite-336791.svg)](https://www.sqlite.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/dunamismax/python-workspace/blob/main/LICENSE)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square)](https://github.com/dunamismax/python-workspace/pulls)
[![GitHub Stars](https://img.shields.io/github/stars/dunamismax/python-workspace?style=social)](https://github.com/dunamismax/python-workspace/stargazers)

---

## Introduction

This monorepo serves as a centralized hub for various C applications and shared libraries. Each project within this repository is designed to be independent and self-contained, ensuring maximum isolation and flexibility for deployment, while benefiting from a unified development environment and shared tooling. This structure promotes code reusability, consistent practices, and simplified dependency management across diverse C projects.

---

## Repository Structure

The repository is organized to support a scalable and maintainable monorepo architecture. Below is a detailed look at the directory structure.

<details>
<summary><strong>Click to expand repository layout</strong></summary>

```sh
c-repo/
├── apps/                         # Directory for independent C applications
│   ├── calculator/               # A command-line calculator
│   │   ├── src/
│   │   │   └── main.c
│   │   └── Makefile
│   ├── file-analyzer/            # A text file analyzer
│   │   ├── src/
│   │   │   └── main.c
│   │   └── Makefile
│   ├── contact-book/             # A command-line contact management system
│   │   ├── src/
│   │   │   └── main.c
│   │   └── Makefile
│   └── tiny-server/              # A simple HTTP web server
│       ├── src/
│       │   └── main.c
│       └── Makefile
│
├── libs/                         # Directory for shared libraries and packages
│   ├── math_lib/                 # Library for basic mathematical operations
│   │   ├── src/
│   │   │   └── math_lib.c
│   │   ├── include/
│   │   │   └── math_lib.h
│   │   └── Makefile
│   └── net_lib/                  # Library for networking operations
│       ├── src/
│       │   └── net_lib.c
│       ├── include/
│       │   └── net_lib.h
│       └── Makefile
│
├── core/                         # Fundamental code central to many projects
│   ├── src/
│   │   ├── utils.c               # Utility functions (e.g., prime checking)
│   │   └── data_structures.c     # Common data structures (e.g., linked list)
│   └── include/
│       ├── utils.h
│       └── data_structures.h
│   └── Makefile
│
├── tests/                        # Dedicated place for all test files
│   ├── libs/
│   │   └── test_my_lib.c         # Test for math_lib
│   │   └── Makefile
│   └── core/
│       └── test_core.c           # Test for core utilities and data structures
│       └── Makefile
│
├── build/                        # Stores compiled output (object files, executables)
│   └── .gitkeep
├── docs/                         # Documentation, notes, etc.
│   └── .gitkeep
├── tools/                        # Helper scripts or development tools
│   └── build_all.sh              # Script to build and test the entire monorepo
├── .gitignore                    # Git ignore file
├── LICENSE                       # Project license
├── README.md                     # Monorepo root README
└── python-workspace-image.png    # Placeholder image for the README
```

</details>

---

## Quick Start

Get up and running with the monorepo:

```bash
# Clone the repository
git clone https://github.com/dunamismax/c-repo.git
cd c-repo

# Build and test the entire monorepo
./tools/build_all.sh

# Alternatively, build components individually:
# Build all libraries
make -C libs/math_lib
make -C libs/net_lib
make -C core

# Build all applications
make -C apps/calculator
make -C apps/file-analyzer
make -C apps/contact-book
make -C apps/tiny-server

# Run tests
make -C tests/libs
./tests/libs/test_my_lib
make -C tests/core
./tests/core/test_core
```

---

## Getting Started

### Prerequisites

Ensure you have the following installed:

- **GCC (GNU Compiler Collection)** - [Install GCC](https://gcc.gnu.org/install/)
- **GNU Make** - [Install Make](https://www.gnu.org/software/make/manual/html_node/Installing-Make.html)
- **Git** - [Download Git](https://git-scm.com/downloads)

### Detailed Setup

1.  **Clone the Repository**

    ```bash
    git clone https://github.com/dunamismax/c-repo.git
    cd c-repo
    ```

2.  **Build Process**

    The monorepo uses `Makefiles` for building. You can build the entire project using the `build_all.sh` script, or build components individually.

    **Build All (Recommended):**

    ```bash
    ./tools/build_all.sh
    ```

    **Build Libraries Individually:**

    ```bash
    cd libs/math_lib
    make
    cd ../../libs/net_lib
    make
    cd ../../core
    make
    ```

    **Build Applications Individually:**

    ```bash
    cd apps/calculator
    make
    cd ../../apps/file-analyzer
    make
    cd ../../apps/contact-book
    make
    cd ../../apps/tiny-server
    make
    ```

3.  **Running Applications**

    ### Calculator

    ```bash
    cd apps/calculator
    ./calculator 10 + 5
    ./calculator 20 / 4
    ```

    ### File Analyzer

    First, create a sample text file (e.g., `sample.txt`) in the `apps/file-analyzer` directory:

    ```bash
    echo "Hello world!\nThis is a test file." > apps/file-analyzer/sample.txt
    ```

    Then run the analyzer:

    ```bash
    cd apps/file-analyzer
    ./file-analyzer sample.txt
    ```

    ### Contact Book

    ```bash
    # Add a new contact
    cd apps/contact-book
    ./contact-book add "John Doe" "555-1234" "john.doe@email.com"

    # List all contacts
    ./contact-book list

    # Search for a contact
    ./contact-book find "John"
    ```

    ### Tiny Server

    ```bash
    # Run the server (it will listen on port 8080)
    cd apps/tiny-server
    ./tiny-server

    # Then, in a web browser, you could navigate to:
    # http://localhost:8080/
    ```

---

## Projects Overview

This monorepo hosts several independent C applications, each demonstrating different functionalities and leveraging shared libraries.

### [Calculator](apps/calculator) - Command-Line Calculator

A simple command-line calculator application that performs basic arithmetic operations (addition, subtraction, multiplication, division). It demonstrates the use of the `libs/math_lib` for mathematical functions.

**Example Usage:**
`./calculator <num1> <operator> <num2>` (e.g., `./calculator 10 + 5`)

### [File Analyzer](apps/file-analyzer) - Text File Analysis Tool

A utility that analyzes a given text file, providing statistics such as character count, word count, and line count. It also demonstrates the usage of `core/utils` for prime number checking and `core/data_structures` for linked list operations.

**Example Usage:**
`./file-analyzer <filename>` (e.g., `./file-analyzer sample.txt`)

### [Contact Book](apps/contact-book) - Command-Line Contact Management System

A command-line interface (CLI) application for managing contacts. Users can add, list, search for, and delete contacts, which are persisted to a CSV file. It leverages the `core/data_structures` for in-memory contact management.

**Example Usage:**
`./contact-book add "John Doe" "555-1234" "john.doe@email.com"`
`./contact-book list`
`./contact-book find "John"`

### [Tiny Server](apps/tiny-server) - A Simple HTTP Web Server

A basic web server that listens for incoming TCP connections on a specified port (default 8080) and serves a simple "Hello, World!" response. It demonstrates fundamental networking concepts and utilizes the new `libs/net_lib` for socket operations.

**Example Usage:**
`./tiny-server` (then access via `http://localhost:8080/` in a browser)

---

## Development Workflow

### Daily Development

1.  **Build Components**

    When making changes, rebuild the specific library or application:

    ```bash
    # Example: Rebuild math_lib
    cd libs/math_lib
    make
    # Example: Rebuild calculator (after math_lib changes)
    cd ../../apps/calculator
    make
    ```

2.  **Run Applications**

    Execute the compiled binaries from their respective directories.

### Making Changes

1.  **Update Source Files**

    Modify `.c` and `.h` files as needed.

2.  **Rebuild**

    Run `make` in the relevant directory to recompile, or run `./tools/build_all.sh` to rebuild the entire project.

3.  **Testing**

    Run tests for all components:

    ```bash
    ./tools/build_all.sh # This also runs tests
    ```

    Or run tests for a specific component:

    ```bash
    cd tests/libs
    make
    ./test_my_lib
    ```

---

## Scripts & Automation

The monorepo includes several automation scripts to streamline development:

-   **`Makefile`** - Each component (libraries, applications, tests) has its own `Makefile` for building and cleaning.
-   **`tools/build_all.sh`** - A convenience script to build all libraries, applications, and run all tests in the correct order.

---

## Contributing

Contributions are welcome! Please feel free to fork the repository, create a feature branch, and open a pull request. For major changes, please open an issue first to discuss what you would like to change.

1.  Fork the Project
2.  Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3.  Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4.  Push to the Branch (`git push origin feature/AmazingFeature`)
5.  Open a Pull Request

---

## Connect

Connect with the author, **dunamismax**, on:

-   **Twitter:** [@dunamismax](https://twitter.com/dunamismax)
-   **Bluesky:** [@dunamismax.bsky.social](https://bsky.app/profile/dunamismax.bsky.social)
-   **Reddit:** [u/dunamismax](https://www.reddit.com/user/dunamismax)
-   **Discord:** `dunamismax`
-   **Signal:** `dunamismax.66`

---

## License

This repository is licensed under the **MIT License**. See the `LICENSE` file for more details.