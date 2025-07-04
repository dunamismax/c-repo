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

This monorepo serves as a centralized hub for various C applications. Each application is self-contained and can be compiled and run independently.

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
├── .gitignore
├── LICENSE
└── c-repo-image.png
```

---

## Quick Start

To get started, clone the repository and navigate to the application you want to use.

```bash
# 1. Clone the repository
git clone https://github.com/dunamismax/c-repo.git
cd c-repo/apps
```

---

## Projects Overview

This monorepo hosts several independent C applications.

### [Calculator](apps/calculator/src/main.c)

A command-line calculator that performs basic arithmetic (`+`, `-`, `*`, `/`). It handles floating-point inputs and includes error checking for invalid input and division-by-zero.

### [File Analyzer](apps/file-analyzer/src/main.c)

A utility that provides statistics for a given text file, including character, word, and line counts. It uses a robust tokenizer to correctly identify words separated by various delimiters.

### [Contact Book](apps/contact-book/src/main.c)

A command-line application for managing a list of contacts. It supports adding, listing, finding (with case-insensitive search), and deleting contacts. The contact list is persisted to a local `contacts.csv` file.

### [Tiny Server](apps/tiny-server/src/main.c)

A simple, multi-threaded HTTP server that handles concurrent connections gracefully. It demonstrates socket programming by serving a basic HTML page and logging requests to the console.

---

## How to Compile and Run

To compile and run an application, navigate to its directory and use a C compiler like `gcc`.

### Calculator

```bash
# Navigate to the calculator app directory
cd apps/calculator/src

# Compile the C file
gcc main.c -o calculator

# Run the executable
./calculator 10 + 5
```

### Contact Book

```bash
# Navigate to the contact book app directory
cd apps/contact-book/src

# Compile the C file
gcc main.c -o contact_book

# Run the executable
./contact_book add "John Doe" "555-1234" "john.doe@example.com"
./contact_book list
```

### File Analyzer

```bash
# Navigate to the file analyzer app directory
cd apps/file-analyzer/src

# Create a sample file to analyze
echo "hello world" > test.txt

# Compile the C file
gcc main.c -o file_analyzer

# Run the executable
./file_analyzer test.txt
```

### Tiny Server

```bash
# Navigate to the tiny server app directory
cd apps/tiny-server/src

# Compile the C file
gcc main.c -o tiny_server -lpthread

# Run the executable
./tiny_server
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
