<p align="center">
  <img src="./c-repo-image.png" alt="C Monorepo logo" width="250"/>
</p>

Welcome to the C Monorepo. This repository centralizes diverse C applications, designed for efficient, scalable, and maintainable project management.

[![Language: C](https://img.shields.io/badge/Language-C-A8B9CC.svg)](<https://en.wikipedia.org/wiki/C_(programming_language)>)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/dunamismax/c-repo/blob/main/LICENSE)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square)](https://github.com/dunamismax/c-repo/pulls)
[![GitHub Stars](https://img.shields.io/github/stars/dunamismax/c-repo?style=social)](https://github.com/dunamismax/c-repo/stargazers)

---

## Overview

This monorepo serves as a centralized hub for various C applications. Each application is a self-contained, single-file program that can be easily compiled and run independently using the provided `Makefile`.

---

## Repository Structure

```sh
c-repo/
├── apps/                         # Independent C applications
│   ├── calculator/               # Command-line calculator
│   ├── contact-book/             # Command-line contact management system
│   ├── file-analyzer/            # Text file analyzer
│   └── tiny-server/              # Simple HTTP web server
│
├── bin/                          # Compiled application binaries
├── .gitignore
├── LICENSE
├── Makefile                      # Main build script for all applications
└── c-repo-image.png
```

---

## Quick Start

To get started, clone the repository, build the applications, and run them from the `bin` directory.

```bash
# 1. Clone the repository
git clone https://github.com/dunamismax/c-repo.git
cd c-repo

# 2. Build all applications
make

# 3. Run an application
./bin/calculator 10 + 5
```

---

## Projects Overview

This monorepo hosts several independent C applications, each contained within a single source file.

### [Calculator](apps/calculator/src/calculator.c)

A command-line calculator that performs basic arithmetic (`+`, `-`, `*`, `/`). It handles floating-point inputs and includes robust error checking for invalid input and division-by-zero.

### [File Analyzer](apps/file-analyzer/src/file-analyzer.c)

A utility that provides statistics for a given text file, including character, word, and line counts. It uses a robust tokenizer to correctly identify words separated by various delimiters.

### [Contact Book](apps/contact-book/src/contact-book.c)

A command-line application for managing a list of contacts. It supports adding, listing, finding (with case-insensitive search), and deleting contacts. The contact list is persisted to a local `contacts.csv` file.

### [Tiny Server](apps/tiny-server/src/tiny-server.c)

A simple, multi-threaded HTTP server that handles concurrent connections gracefully. It demonstrates socket programming by serving a basic HTML page and logging requests to the console.

---

## How to Compile and Run

This project uses a `Makefile` for easy compilation of all applications. The compiled binaries are placed in the `bin` directory.

### Build All Applications

To build all applications, run the `make` command from the root of the repository:

```bash
make
```

### Run Applications

Once compiled, you can run the applications from the `bin` directory:

```bash
# Run the calculator
./bin/calculator 25 / 4

# Add a contact to the contact book
./bin/contact-book add "Jane Doe" "555-5678" "jane.doe@example.com"

# Analyze a file
./bin/file-analyzer README.md

# Start the tiny server
./bin/tiny-server
```

### Clean Build Artifacts

To remove all compiled files, run:

```bash
make clean
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
