#!/bin/bash

# Exit on any error
set -e

# Function to print a formatted header
print_header() {
    echo "========================================================================"
    echo "$1"
    echo "========================================================================"
}

# Change to the project root directory
cd "$(dirname "$0")"/..

# Clean previous builds
print_header "Cleaning previous builds..."
make -C core clean
make -C libs/math_lib clean
make -C libs/net_lib clean
make -C apps/calculator clean
make -C apps/file-analyzer clean
make -C apps/contact-book clean
make -C apps/tiny-server clean
make -C tests/core clean
make -C tests/libs clean

# Build libraries
print_header "Building libraries..."
make -C libs/math_lib
make -C libs/net_lib
make -C core

# Build all applications
print_header "Building applications..."
make -C apps/calculator
make -C apps/file-analyzer
make -C apps/contact-book
make -C apps/tiny-server

# Build all tests
print_header "Building tests..."
make -C tests/libs
make -C tests/core

# Run tests
print_header "Running tests..."
./build/test/test_my_lib
./build/test/test_net_lib
./build/test/test_core

print_header "Build and test complete."
echo "All libraries, applications, and tests have been successfully built and executed."